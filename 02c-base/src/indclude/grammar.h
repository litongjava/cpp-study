/*
 * grammar.h
 *
 *  Created on: 2019年10月17日
 *      Author: Administrator
 */

#ifndef INDCLUDE_GRAMMAR_H_
#define INDCLUDE_GRAMMAR_H_
void studyIf(int i) {
  if (i) {
    printf("0\n");
  } else {
    printf("1\n");
  }
}

/**
 * if a=1,b=2,c=3,不能将c赋值给a,b的表达式是
 * A.(a=c) ||(b=c) B.(a=c)&&(b=c)
 */
void saaignment() {
  int a = 1, b = 2, c = 3;
  (a = c) || (b = 3);
  (a = c) && (b = 3);
  printf("%d,%d,%d\n", a, b, c);
}
//int a[3][4]={1,3,4,5,6},值为4的数组元素是:
//void array() {
//  int a[3][4] = { 1, 2, 3, 4, 5, 6 };
//  for (int i = 0; i < 3; i++) {
//    for (int j = 0; j < 4; i++) {
//      printf("%d\n", a[i][j]);
//    }
//  }
//}
#endif /* INDCLUDE_GRAMMAR_H_ */
