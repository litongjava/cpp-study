/*
 * study_struct.h
 *
 *  Created on: 2019Äê10ÔÂ18ÈÕ
 *      Author: Administrator
 */

#ifndef INDCLUDE_STUDY_STRUCT_H_
#define INDCLUDE_STUDY_STRUCT_H_

struct student {
  char * name;
  int age;
};
void study_01() {
  struct student s = { "litng", 18 };
  printf("name is %s,age is %d", s.name, s.age);
}

#endif /* INDCLUDE_STUDY_STRUCT_H_ */
