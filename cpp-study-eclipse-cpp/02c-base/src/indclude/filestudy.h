/*
 * filestudy.h
 *
 *  Created on: 2019年10月17日
 *      Author: Administrator
 */

#ifndef INDCLUDE_FILESTUDY_H_
#define INDCLUDE_FILESTUDY_H_

#include <stdio.h>

int study001() {
  FILE *fp = NULL;
  //打开文件
  fp = fopen("tmp/test.txt", "w+");
  if (fp == NULL) {
    printf("打开文件失败:\n");
    return 1;
  }
  int status = fputs("This is testing for fprintf...\n", fp);
  printf("写入文件结果:%d\n" + status);
  status = fprintf(fp, "This is testing for fputs...\n");
  printf("写入文件结果:%d\n", status);
  //关闭文件
  status = fclose(fp);
  if (status != 0) {
    printf("关闭文件失败\n");
  }
  return 0;
}

int study002() {
  FILE *fp = NULL;
  char buf[255];
  fp = fopen("tmp/test.txt", "r");
  fscanf(fp, "%s", buf);
  printf("1 %s\n", buf);
  fgets(buf, 255, (FILE*) fp);
  printf("2 %s\n", buf);
  fgets(buf, 255, (FILE*) fp);
  printf("3 %s\n", buf);
  fclose(fp);
  return 0;
}
#endif /* INDCLUDE_FILESTUDY_H_ */
