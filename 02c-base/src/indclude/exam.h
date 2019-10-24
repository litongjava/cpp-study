/*
 * exam.h
 *
 *  Created on: 2019Äê10ÔÂ18ÈÕ
 *      Author: Administrator
 */

#ifndef INDCLUDE_EXAM_H_
#define INDCLUDE_EXAM_H_

#include <stdio.h>

void prepareData() {
  FILE *fp = fopen("old.txt", "w");
  fputs("0,1,2,3,4,5,6,7,8,9,acb", fp);
  fclose(fp);
}
void sheji1() {
  FILE *oldfp = fopen("old.txt", "r");
  FILE *newfp = fopen("new.txt", "w");
  char oldchar;
  while ((oldchar = fgetc(oldfp)) != -1) {
    printf("%c", oldchar);
    if (oldchar >= '0' && oldchar <= '9') {
      oldchar = 'Z' - (oldchar - 48);
    }
    fputc(oldchar, newfp);
  }
  fclose(oldfp);
  fclose(newfp);
}

#endif /* INDCLUDE_EXAM_H_ */
