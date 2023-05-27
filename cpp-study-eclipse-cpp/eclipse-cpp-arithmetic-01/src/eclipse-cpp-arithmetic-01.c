/*
 ============================================================================
 Name        : eclipse-cpp-arithmetic-01.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * 源数据:B4 D4 B4 D4 D6|F1
 * 通过算法提取出B4B6D6|F1
 * 第一是B4开头,第二是D6结束
 */
int main(void) {
//  //B4
//  //uint8_t xx = ;
//  uint8_t RFID_DATE[] = { 0xB4, 0xD4, 0xB4, 0xD4, 0xD6 };
//  //获取
//  //srcData
  char src[]={'/','A','*','1'};
  printf(" %s \n",src);
  int length=sizeof(src);
  printf("length %d \n",length);
  //ASCII 0=48,9=57,A=65,z=90,a=97,z=122,

  for(int i=0;i<4;i++){
    if(src[i]>=48 && src[i]<=57){
      printf("%c \n",src[i]);
    }else if(src[i]>=65 && src[i]<=90){
      printf("%c \n",src[i]);
    }else if(src[i]>=97 && src[i]<=122){
      printf("%c \n",src[i]);
    }
  }
  puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
  return EXIT_SUCCESS;
}
