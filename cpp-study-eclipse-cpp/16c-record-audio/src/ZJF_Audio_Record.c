#include "main.h"

AudioStatus_t audio;


int ZJF_Audio_SetStatus_API(int status)
{
    printf("设置状态: %d \n",status);
    audio.Status = status;
    return 0;
}

void ZJF_Audio_RecordPro_API( )
{
    int wfd    = 0;
    int a_fd   = 0;
    int temp   = 0;
    int status = 0;
    int ret    = 0;
    int sret   = 0;
    char buf[MAX_BUFF_LEN] = { 0 };

    int len = MAX_BUFF_LEN;

    a_fd = open(AUDIO_PATH,O_RDWR);
    if(a_fd < 0)
    {
        printf("open file %s failed !!! \n",AUDIO_PATH);
        goto ERR;
    }
    wfd = open(AUDIO_SAVE_PATH,O_CREAT|O_RDWR);
    if(wfd < 0)
    {
        printf("open file %s failed !!! \n",AUDIO_SAVE_PATH);
        goto ERR;
    }

    //设置采样时的量化位数
    temp = SIZE;
    status = ioctl(a_fd,SOUND_PCM_WRITE_BITS,&temp);
    if(status==-1)
    {
      perror("Cannot set SOUND_PCM_WRITE_BITS ");
      goto ERR;
   }

   //设置采样声道数目
   temp = CHANNELS;
   status=ioctl(a_fd,SOUND_PCM_WRITE_CHANNELS,&temp);
   if(status==-1){
      perror("Cannot set SOUND_PCM_WRITE_CHANNELS");
      goto ERR;
   }

   //设置采样频率
   temp = RATE;
   status=ioctl(a_fd,SOUND_PCM_WRITE_RATE,&temp);
   if(status==-1)
   {
     perror("Cannot set SOUND_PCM_WRITE_RATE");
     goto ERR;
   }

   memset(&audio,0,sizeof(AudioStatus_t));
   while(1)
   {
       if(audio.Status == ZJF_AUDIO_NULL)
       {
           sleep(1);
           continue;
       }
       else if(audio.Status == ZJF_AUDIO_RECORD)
       {
           //printf("录音 \n");
           ret = read(a_fd,buf,len);
           if(ret < 0)
           {
               perror("read err:");
               goto ERR;
           }

           if(ret > 0)
           {
               if(write(wfd,buf,len) < 0)
               {
                   perror("write err:");
                   goto ERR;
               }
           }
       }
       else if(audio.Status == ZJF_AUDIO_STOP)
       {
           printf("audio stop !!! \n");
           goto ERR;
       }
       else if(audio.Status == ZJF_AUDIO_PLAY)
       {
           ret = read(wfd,buf,len);
           if(ret < 0)
           {
               perror("ZJF_AUDIO_PLAY read err:");
               goto ERR;
           }
           if(ret > 0)
           {
               if(write(a_fd,buf,len) < 0)
               {
                   perror("ZJF_AUDIO_PLAY write err:");
                   goto ERR;
               }
               //ioctl(a_fd,SOUND_PCM_SYNC,0);
           }
       }
   }

ERR:
    if(a_fd > 0)
    {
        close(a_fd);
        a_fd = -1;
    }
    if(wfd > 0)
    {
        close(wfd);
        wfd = -1;
    }
    return ;
}

