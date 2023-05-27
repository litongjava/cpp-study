/*
 * in.h
 *
 *  Created on: 2019年10月17日
 *      Author: Administrator
 */

#include <stdio.h>

void study_getchar() {
  char c = getchar();
  putchar(c);
}

void study_scanf_01() {
  int a, b, c;
  printf("请输入3个数字:\n");
  scanf("%d%d%d", &a, &b, &c);
  printf("%d,%d,%d\n", a, b, c);
}

void study_scanf_2() {
  char str1[20], str2[20];
  printf("请求输入用户名:\n");
  scanf("%s", str1);
  printf("请输入密码:\n");
  scanf("%s", str2);
  printf("获取到的用户名和密码:%s,%s", str1, str2);
}

void study_feof() {
  FILE *fp = NULL;
  char buf[255];
  fp = fopen("tmp/test.txt", "r");
  char *str = NULL;
  while ((str = fgets(buf, 255, fp)) != NULL) {
    int i = feof(fp);
    printf("feof:%d\n", i);
    printf("%s", str);
  }
  int i = feof(fp);
  printf("feof:%d\n", i);
  fclose(fp);
}
