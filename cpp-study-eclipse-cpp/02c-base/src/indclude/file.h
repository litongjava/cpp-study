/*
 * file.h
 *
 *  Created on: 2019Äê10ÔÂ17ÈÕ
 *      Author: Administrator
 */

#ifndef INDCLUDE_FILE_H_
#define INDCLUDE_FILE_H_

#include <stdio.h>

void wirteFile01() {
  FILE *fp = NULL;

  fp = fopen("tmp/test.txt", "w+");
  fprintf(fp, "This is testing for fprintf...\n");
  fputs("This is testing for fputs...\n", fp);
  fclose(fp);
}

#endif /* INDCLUDE_FILE_H_ */
