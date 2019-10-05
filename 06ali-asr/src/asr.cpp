/*
 * Copyright 2015 Alibaba Group Holding Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if defined(_WIN32)
#include <windows.h>
#include "pthread.h"
#else
#include <unistd.h>
#include <pthread.h>
#endif

#include <ctime>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "nlsClient.h"
#include "nlsEvent.h"
#include "speechRecognizerRequest.h"

#include "nlsCommonSdk/Token.h"

#define FRAME_SIZE 3200
#define SAMPLE_RATE 16000

using std::map;
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;

using namespace AlibabaNlsCommon;

using AlibabaNls::NlsClient;
using AlibabaNls::NlsEvent;
using AlibabaNls::LogDebug;
using AlibabaNls::LogInfo;
using AlibabaNls::SpeechRecognizerCallback;
using AlibabaNls::SpeechRecognizerRequest;


/**
* ȫ��ά��һ�������Ȩtoken�����Ӧ����Ч��ʱ�����
* ÿ�ε��÷���֮ǰ�������ж�token�Ƿ��Ѿ����ڣ�
* ����Ѿ����ڣ������AccessKey ID��AccessKey Secret��������һ��token�����������ȫ�ֵ�token������Ч��ʱ�����
*
* ע�⣺��Ҫÿ�ε��÷���֮ǰ������������token��ֻ����token��������ʱ�������ɼ��ɡ����еķ��񲢷��ɹ���һ��token��
*/
string g_akId = "";
string g_akSecret = "";
string g_token = "";
long g_expireTime = -1;


// �Զ����̲߳���
struct ParamStruct {
  string fileName;
    string appkey;
  string token;
};

// �Զ����¼��ص�����
struct ParamCallBack {
    int iExg;
    string sExg;

    pthread_mutex_t mtx;
    bool bSend;
};

/**
* ����AccessKey ID��AccessKey Secret��������һ��token������ȡ����Ч��ʱ���
*/
int generateToken(string akId, string akSecret, string* token, long* expireTime) {
    NlsToken nlsTokenRequest;
    nlsTokenRequest.setAccessKeyId(akId);
    nlsTokenRequest.setKeySecret(akSecret);

    if (-1 == nlsTokenRequest.applyNlsToken()) {
        cout << "Failed: " << nlsTokenRequest.getErrorMsg() << endl; /*��ȡʧ��ԭ��*/

        return -1;
    }

    *token = nlsTokenRequest.getToken();
    *expireTime = nlsTokenRequest.getExpireTime();

    return 0;
}

/**
    * @brief ��ȡsendAudio������ʱʱ��
    * @param dataSize ���������ݴ�С
    * @param sampleRate ������ 16k/8K
    * @param compressRate ����ѹ���ʣ�����ѹ����Ϊ10:1��16k opus���룬��ʱΪ10����ѹ��������Ϊ1
    * @return ����sendAudio֮����Ҫsleep��ʱ��
    * @note ����8k pcm ��������, 16λ����������ÿ����1600�ֽ� sleep 100 ms.
            ����16k pcm ��������, 16λ����������ÿ����3200�ֽ� sleep 100 ms.
            �������������ʽ������, �û�����ѹ����, ���й���, ����ѹ����Ϊ10:1�� 16k opus,
            ��Ҫÿ����3200/10=320 sleep 100ms.
*/
unsigned int getSendAudioSleepTime(const int dataSize,
                                   const int sampleRate,
                                   const int compressRate) {
    // ��֧��16λ����
    const int sampleBytes = 16;
    // ��֧�ֵ�ͨ��
    const int soundChannel = 1;

    // ��ǰ�����ʣ�����λ����ÿ��������ݵĴ�С
    int bytes = (sampleRate * sampleBytes * soundChannel) / 8;

    // ��ǰ�����ʣ�����λ����ÿ����������ݵĴ�С
    int bytesMs = bytes / 1000;

    // ���������ݴ�С����ÿ����������ݴ�С���Ի�ȡsleepʱ��
    int sleepMs = (dataSize * compressRate) / bytesMs;

    return sleepMs;
}

/**
    * @brief ����start(), �ɹ����ƶ˽�������, sdk�ڲ��߳��ϱ�started�¼�
    * @note �������ڻص������ڲ�����stop(), releaseRecognizerRequest()�������, ������쳣
    * @param cbEvent �ص��¼��ṹ, ���nlsEvent.h
    * @param cbParam �ص��Զ��������Ĭ��ΪNULL, ���Ը��������Զ������
    * @return
*/
void OnRecognitionStarted(NlsEvent* cbEvent, void* cbParam) {
  ParamCallBack* tmpParam = (ParamCallBack*)cbParam;
  cout << "CbParam: " << tmpParam->iExg << " " << tmpParam->sExg << endl; // ����ʾ�Զ������ʾ��

  cout << "OnRecognitionStarted: "
    << "status code: " << cbEvent->getStausCode()  // ��ȡ��Ϣ��״̬�룬�ɹ�Ϊ0����20000000��ʧ��ʱ��Ӧʧ�ܵĴ�����
    << ", task id: " << cbEvent->getTaskId()   // ��ǰ�����task id�����㶨λ���⣬�������
    << endl;
  // cout << "OnRecognitionStarted: All response:" << cbEvent->getAllResponse() << endl; // ��ȡ����˷��ص�ȫ����Ϣ
}

/**
    * @brief �����������м�������, sdk�ڽ��յ��ƶ˷��ص��м���ʱ, sdk�ڲ��߳��ϱ�ResultChanged�¼�
    * @note �������ڻص������ڲ�����stop(), releaseRecognizerRequest()�������, ������쳣
    * @param cbEvent �ص��¼��ṹ, ���nlsEvent.h
    * @param cbParam �ص��Զ��������Ĭ��ΪNULL, ���Ը��������Զ������
    * @return
*/
void OnRecognitionResultChanged(NlsEvent* cbEvent, void* cbParam) {
  ParamCallBack* tmpParam = (ParamCallBack*)cbParam;
  cout << "CbParam: " << tmpParam->iExg << " " << tmpParam->sExg << endl; // ����ʾ�Զ������ʾ��

  cout << "OnRecognitionResultChanged: "
    << "status code: " << cbEvent->getStausCode()  // ��ȡ��Ϣ��״̬�룬�ɹ�Ϊ0����20000000��ʧ��ʱ��Ӧʧ�ܵĴ�����
    << ", task id: " << cbEvent->getTaskId()    // ��ǰ�����task id�����㶨λ���⣬�������
    << ", result: " << cbEvent->getResult()     // ��ȡ�м�ʶ����
    << endl;
  // cout << "OnRecognitionResultChanged: All response:" << cbEvent->getAllResponse() << endl; // ��ȡ����˷��ص�ȫ����Ϣ
}

/**
    * @brief sdk�ڽ��յ��ƶ˷���ʶ�������Ϣʱ, sdk�ڲ��߳��ϱ�Completed�¼�
    * @note �ϱ�Completed�¼�֮��, SDK�ڲ���ر�ʶ������ͨ��. ��ʱ����sendAudio�᷵��-1, ��ֹͣ����.
    *       �������ڻص������ڲ�����stop(), releaseRecognizerRequest()�������, ������쳣.
    * @param cbEvent �ص��¼��ṹ, ���nlsEvent.h
    * @param cbParam �ص��Զ��������Ĭ��ΪNULL, ���Ը��������Զ������
    * @return
*/
void OnRecognitionCompleted(NlsEvent* cbEvent, void* cbParam) {
  ParamCallBack* tmpParam = (ParamCallBack*)cbParam;
  cout << "CbParam: " << tmpParam->iExg << " " << tmpParam->sExg << endl; // ����ʾ�Զ������ʾ��

  cout << "OnRecognitionCompleted: "
    << "status code: " << cbEvent->getStausCode()  // ��ȡ��Ϣ��״̬�룬�ɹ�Ϊ0����20000000��ʧ��ʱ��Ӧʧ�ܵĴ�����
    << ", task id: " << cbEvent->getTaskId()    // ��ǰ�����task id�����㶨λ���⣬�������
    << ", result: " << cbEvent->getResult()  // ��ȡ�м�ʶ����
    << endl;
  // cout << "OnRecognitionCompleted: All response:" << cbEvent->getAllResponse() << endl; // ��ȡ����˷��ص�ȫ����Ϣ
}

/**
    * @brief ʶ�����(����start(), send(), stop())�����쳣ʱ, sdk�ڲ��߳��ϱ�TaskFailed�¼�
    * @note �ϱ�TaskFailed�¼�֮��, SDK�ڲ���ر�ʶ������ͨ��. ��ʱ����sendAudio�᷵��-1, ��ֹͣ����.
    *       �������ڻص������ڲ�����stop(), releaseRecognizerRequest()�������, ������쳣
    * @param cbEvent �ص��¼��ṹ, ���nlsEvent.h
    * @param cbParam �ص��Զ��������Ĭ��ΪNULL, ���Ը��������Զ������
    * @return
*/
void OnRecognitionTaskFailed(NlsEvent* cbEvent, void* cbParam) {
  ParamCallBack* tmpParam = (ParamCallBack*)cbParam;
  cout << "CbParam: " << tmpParam->iExg << " " << tmpParam->sExg << endl; // ����ʾ�Զ������ʾ��

  cout << "OnRecognitionTaskFailed: "
    << "status code: " << cbEvent->getStausCode() // ��ȡ��Ϣ��״̬�룬�ɹ�Ϊ0����20000000��ʧ��ʱ��Ӧʧ�ܵĴ�����
    << ", task id: " << cbEvent->getTaskId()    // ��ǰ�����task id�����㶨λ���⣬�������
    << ", error message: " << cbEvent->getErrorMessage()
    << endl;
  // cout << "OnRecognitionTaskFailed: All response:" << cbEvent->getAllResponse() << endl; // ��ȡ����˷��ص�ȫ����Ϣ

    /*���÷���״̬λ, ֹͣ���ݷ���. */
    pthread_mutex_lock(&(tmpParam->mtx));
    tmpParam->bSend = false;
    pthread_mutex_unlock(&(tmpParam->mtx));
}

/**
    * @brief ʶ����������쳣ʱ����ر�����ͨ��, sdk�ڲ��߳��ϱ�ChannelCloseed�¼�
    * @note �������ڻص������ڲ�����stop(), releaseRecognizerRequest()�������, ������쳣
    * @param cbEvent �ص��¼��ṹ, ���nlsEvent.h
    * @param cbParam �ص��Զ��������Ĭ��ΪNULL, ���Ը��������Զ������
    * @return
*/
void OnRecognitionChannelCloseed(NlsEvent* cbEvent, void* cbParam) {
  ParamCallBack* tmpParam = (ParamCallBack*)cbParam;
  cout << "CbParam: " << tmpParam->iExg << " " << tmpParam->sExg << endl; // ����ʾ�Զ������ʾ��

  cout << "OnRecognitionChannelCloseed: All response:" << cbEvent->getAllResponse() << endl; // ��ȡ����˷��ص�ȫ����Ϣ
}

// �����߳�
void* pthreadFunc(void* arg) {
    bool tmpStatus = true;
    int sleepMs = 0;
    ParamCallBack cbParam;
    SpeechRecognizerCallback* callback = NULL;

    // ��ʼ���Զ���ص�����, ��������������Ϊʾ����ʾ��������, ��demo�в����κ�����
    cbParam.iExg = 1;
    cbParam.sExg = "exg.";

    //���Ʒ�������
    pthread_mutex_init(&(cbParam.mtx), NULL);
    cbParam.bSend = true;

    // 0: ���Զ����̲߳����л�ȡtoken, �����ļ��Ȳ���.
    ParamStruct *tst = (ParamStruct *) arg;
    if (tst == NULL) {
        cout << "arg is not valid." << endl;
        return NULL;
    }

    // ����Ƶ�ļ�, ��ȡ����
    ifstream fs;
    fs.open(tst->fileName.c_str(), ios::binary | ios::in);
    if (!fs) {
        cout << tst->fileName << " isn't exist.." << endl;

        return NULL;
    }

    /*
     * 1: ���������ûص�����
     */
    callback = new SpeechRecognizerCallback();
    callback->setOnRecognitionStarted(OnRecognitionStarted, &cbParam); // ����start()�ɹ��ص�����
    callback->setOnTaskFailed(OnRecognitionTaskFailed, &cbParam); // �����쳣ʶ��ص�����
    callback->setOnChannelClosed(OnRecognitionChannelCloseed, &cbParam); // ����ʶ��ͨ���رջص�����
    callback->setOnRecognitionResultChanged(OnRecognitionResultChanged, &cbParam); // �����м����ص�����
    callback->setOnRecognitionCompleted(OnRecognitionCompleted, &cbParam); // ����ʶ������ص�����

    /*
    * ����һ�仰ʶ��SpeechRecognizerRequest����, ����Ϊcallback����.
    * request������һ���Ự�����ڿ����ظ�ʹ��.
    * �Ự������һ���߼�����. ����Demo��, ָ��ȡ, ������������Ƶ�ļ����ݵ�ʱ��.
    * ��Ƶ�ļ����ݷ��ͽ���ʱ, ����releaseRecognizerRequest()�ͷŶ���.
    * createRecognizerRequest(), start(), sendAudio(), stop(), releaseRecognizerRequest()����
    * ͬһ�߳������, ���߳�ʹ�ÿ��ܻ������쳣����
  * �����Ҫʶ���Σ���ÿ�δ���һ��SpeechRecognizerRequest����ִ��start-sendAudio-stop,Ȼ���ͷ�SpeechRecognizerRequest����
    */
    /*
     * 2: ����һ�仰ʶ��SpeechRecognizerRequest����
     */
    SpeechRecognizerRequest *request = NlsClient::getInstance()->createRecognizerRequest(callback);
    if (request == NULL) {
        cout << "createRecognizerRequest failed." << endl;

        delete callback;
        callback = NULL;

        return NULL;
    }

    request->setAppKey(tst->appkey.c_str()); // ����AppKey, �������, ����չ�������

    request->setFormat("pcm"); // ������Ƶ���ݱ����ʽ, ��ѡ����, Ŀǰ֧��pcm, opus. Ĭ����pcm
    request->setSampleRate(SAMPLE_RATE); // ������Ƶ���ݲ�����, ��ѡ����, Ŀǰ֧��16000, 8000. Ĭ����16000
    request->setIntermediateResult(true); // �����Ƿ񷵻��м�ʶ����, ��ѡ����. Ĭ��false
    request->setPunctuationPrediction(true); // �����Ƿ��ں�������ӱ��, ��ѡ����. Ĭ��false
    request->setInverseTextNormalization(true); // �����Ƿ��ں�����ִ��ITN, ��ѡ����. Ĭ��false
//    request->setEnableVoiceDetection(true); //�Ƿ������������, ��ѡ, Ĭ����False
    //��������ʼ����, ��ѡ, ��λ�Ǻ���, ���������˽��ᷢ��RecognitionCompleted�¼�, ��������ʶ��.
    //ע��: ��Ҫ������enable_voice_detectionΪtrue
//    request->setMaxStartSilence(800);
    //���������������, ��ѡ, ��λ�Ǻ���, ���������˽��ᷢ��RecognitionCompleted�¼�, ��������ʶ��.
    //ע��: ��Ҫ������enable_voice_detectionΪtrue
//    request->setMaxEndSilence(800);
//    request->setCustomizationId("TestId_123"); //����ģ��id, ��ѡ.
//    request->setVocabularyId("TestId_456"); //���Ʒ��ȴ�id, ��ѡ.

    request->setToken(tst->token.c_str()); // �����˺�У��token, �������

    /*
    * 3: start()Ϊ��������, ����startָ��֮��, ��ȴ��������Ӧ, ��ʱ֮��ŷ���
    */
    if (request->start() < 0) {
        cout << "start() failed." << endl;
        NlsClient::getInstance()->releaseRecognizerRequest(request); // start()ʧ�ܣ��ͷ�request����

        delete callback;
        callback = NULL;

        return NULL;
    }

    // �ļ��Ƿ��ȡ���, ���߽��յ�TaskFailed, closed, completed�ص�, ��ֹsend
    while ((!fs.eof()) && (tmpStatus)) {
        char data[FRAME_SIZE] = {0};

        fs.read(data, sizeof(char) * FRAME_SIZE);
        int nlen = (int) fs.gcount();

        /*
        * 4: ������Ƶ����. sendAudio����-1��ʾ����ʧ��, ��Ҫֹͣ����. ���ڵ���������:
        * formatΪopu(����ԭʼ��Ƶ���ݱ���ΪPCM, FRAME_SIZE��С����Ϊ640)ʱ, ������Ϊtrue. ������ʽĬ��ʹ��false.
        */
        nlen = request->sendAudio(data, nlen, false);
        if (nlen < 0) {
            // ����ʧ��, �˳�ѭ�����ݷ���
            cout << "send data fail." << endl;
            break;
        }else {
            cout << "send len:" << nlen << " ." << endl;
        }

        /*
        *�������ݷ��Ϳ��ƣ�
        *����������ʵʱ��, ����sleep��������, ֱ�ӷ��ͼ���.
        *�������������ļ�, ����ʱ��Ҫ��������, ʹ��λʱ���ڷ��͵����ݴ�С�ӽ���λʱ��ԭʼ�������ݴ洢�Ĵ�С.
        */
        sleepMs = getSendAudioSleepTime(nlen, SAMPLE_RATE, 1); // ���� �������ݴ�С�������ʣ�����ѹ���� ����ȡsleepʱ��

        /*
        * 5: �������ݷ�����ʱ����
        */
#if defined(_WIN32)
        Sleep(sleepMs);
#else
        usleep(sleepMs * 1000);
#endif

        pthread_mutex_lock(&(cbParam.mtx));
        tmpStatus = cbParam.bSend;
        pthread_mutex_unlock(&(cbParam.mtx));
    }

    // �ر���Ƶ�ļ�
    fs.close();

    /*
    * 6: ���ݷ��ͽ������ر�ʶ������ͨ��.
    * stop()Ϊ��������, �ڽ��ܵ��������Ӧ, ���߳�ʱ֮��, �Ż᷵��.
    */
    request->stop();

    // 7: ʶ�����, �ͷ�request����
    NlsClient::getInstance()->releaseRecognizerRequest(request);

    // 8: �ͷ�callback����
    delete callback;
    callback = NULL;

  return NULL;
}

/**
  * �߳�ѭ��ʶ��
  * ��Ҫ����countֵ��ÿ��Ҫʶ����ļ���Demo��Ĭ��ÿ��ʶ��һ���ļ�
  */
void* multiRecognize(void* arg) {
  int count = 2;
  while (count > 0) {
    pthreadFunc(arg);
    count--;
  }

  return NULL;
}

/**
 * ʶ�𵥸���Ƶ����
 */
int speechRecognizerFile(const char* appkey) {
    /**
     * ��ȡ��ǰϵͳʱ������ж�token�Ƿ����
     */
    std::time_t curTime = std::time(0);
    if (g_expireTime - curTime < 10) {
        cout << "the token will be expired, please generate new token by AccessKey-ID and AccessKey-Secret." << endl;
        if (-1 == generateToken(g_akId, g_akSecret, &g_token, &g_expireTime)) {
            return -1;
        }
    }

    ParamStruct pa;
    pa.token = g_token;
    pa.appkey = appkey;
    pa.fileName = "test0.wav";

    pthread_t pthreadId;

    // ����һ�������߳�, ���ڵ���ʶ��
    pthread_create(&pthreadId, NULL, &pthreadFunc, (void *)&pa);

  // ����һ�������߳�, ����ѭ��ʶ��
  // pthread_create(&pthreadId, NULL, &multiRecognize, (void *)&pa);

    pthread_join(pthreadId, NULL);

  return 0;

}

/**
 * ʶ������Ƶ����;
 * sdk���߳�ָһ����Ƶ����Դ��Ӧһ���߳�, ��һ����Ƶ���ݶ�Ӧ����߳�.
 * ʾ������Ϊͬʱ����4���߳�ʶ��4���ļ�;
 * ����û��������Ӳ��ܳ���10��;
 */
#define AUDIO_FILE_NUMS 4
#define AUDIO_FILE_NAME_LENGTH 32
int speechRecognizerMultFile(const char* appkey) {
    /**
    * ��ȡ��ǰϵͳʱ������ж�token�Ƿ����
    */
    std::time_t curTime = std::time(0);
    if (g_expireTime - curTime < 10) {
        cout << "the token will be expired, please generate new token by AccessKey-ID and AccessKey-Secret." << endl;
        if (-1 == generateToken(g_akId, g_akSecret, &g_token, &g_expireTime)) {
            return -1;
        }
    }

    char audioFileNames[AUDIO_FILE_NUMS][AUDIO_FILE_NAME_LENGTH] = {"test0.wav", "test1.wav", "test2.wav", "test3.wav"};
    ParamStruct pa[AUDIO_FILE_NUMS];

    for (int i = 0; i < AUDIO_FILE_NUMS; i ++) {
        pa[i].token = g_token;
        pa[i].appkey = appkey;
        pa[i].fileName = audioFileNames[i];
    }

    vector<pthread_t> pthreadId(AUDIO_FILE_NUMS);
    // �����ĸ������߳�, ͬʱʶ���ĸ���Ƶ�ļ�
    for (int j = 0; j < AUDIO_FILE_NUMS; j++) {
        pthread_create(&pthreadId[j], NULL, &pthreadFunc, (void *)&(pa[j]));
    }

    for (int j = 0; j < AUDIO_FILE_NUMS; j++) {
        pthread_join(pthreadId[j], NULL);
    }

  return 0;
}

int main(int arc, char* argv[]) {
    if (arc < 4) {
        cout << "params is not valid. Usage: ./demo <your appkey> <your AccessKey ID> <your AccessKey Secret>" << endl;
        return -1;
    }

    string appkey = argv[1];
    g_akId = argv[2];
    g_akSecret = argv[3];

    // ������Ҫ����SDK�����־, ��ѡ. �˴���ʾSDK��־�����log-recognizer.txt�� LogDebug��ʾ������м�����־
    int ret = NlsClient::getInstance()->setLogConfig("log-recognizer.txt", LogInfo);
    if (-1 == ret) {
        cout << "set log failed." << endl;
        return -1;
    }

    // ʶ�𵥸���Ƶ����
    speechRecognizerFile(appkey.c_str());

    // ʶ������Ƶ����
    // speechRecognizerMultFile(appkey.c_str());

    // ���й�����ɣ������˳�ǰ���ͷ�nlsClient. ��ע��, releaseInstance()���̰߳�ȫ.
    NlsClient::releaseInstance();

  return 0;
}
