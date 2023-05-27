#include "main.h"

void ZJF_Audio_Ctrl_API() {
  int type = 0;

  while (1) {
    printf("1: 录音 \n2: 停止 \n3: 播放\n当前状态是:%d\n", type);

    scanf("%d", &type);

    ZJF_Audio_SetStatus_API(type);
    if (ZJF_AUDIO_STOP == type) {
      break;
    }
  }

  return;
}

