#ifndef  _MAIN_H_
#define  _MAIN_H_

#include <sys/soundcard.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <linux/soundcard.h>
#include <pthread.h>

#define AUDIO_SAVE_PATH       ("/home/audio.txt")
#define AUDIO_PATH            ("/dev/dsp")


#define LENGTH            (3)        //录音时间
#define RATE              (8000)     //采样频率
#define SIZE              (16)       //量化位数
#define CHANNELS          (2)        //声道数目
#define MAX_BUFF_LEN      (LENGTH*RATE*SIZE*CHANNELS/8)         //保存录音的音频数据

enum
{
    ZJF_AUDIO_NULL = 0,
    ZJF_AUDIO_RECORD,
    ZJF_AUDIO_STOP,
    ZJF_AUDIO_PLAY
};

typedef struct Audio
{
    int Status;
}AudioStatus_t;

extern int ZJF_Audio_SetStatus_API(int status);
extern void ZJF_Audio_RecordPro_API( );
extern void ZJF_Audio_Ctrl_API( );
#endif
