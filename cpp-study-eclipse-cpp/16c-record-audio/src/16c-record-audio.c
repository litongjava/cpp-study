#include "main.h"


int main()
{
    pthread_t ntid;

    if(pthread_create(&ntid,NULL,(void *)ZJF_Audio_RecordPro_API,NULL))
    {
        printf("can't create thread !!! \n");
        return 1;
    }

    if(pthread_create(&ntid,NULL,(void *)ZJF_Audio_Ctrl_API,NULL))
    {
        printf("can't create thread !!! \n");
        return 1;
    }

    while(1)
    {
        sleep(10);
    }
    return 0;
}
