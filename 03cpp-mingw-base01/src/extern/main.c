/*
 * main.c
 *
 *  Created on: 2019Äê7ÔÂ28ÈÕ
 *      Author: Administrator
 */
int count;
extern void writeExtern();
int main_extern(int argc,char* argv[]){
  count=5;
  writeExtern();
  return 0;
}
