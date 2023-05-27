/*
 * jsoncpp_study_01.cpp
 *
 *  Created on: 2019年8月21日
 *      Author: litong
 */
#include <iostream>
#include <string>
#include <string.h>
#include <json/json.h>
#include "jsoncpp-study.h"
using namespace std;
using namespace Json;
void testReaderParse() {
  const char* jsonString = "{\"name\": \"litong\",\"age\": 20,}";
  Reader reader;
  Value root;
  reader.parse(jsonString, root); // reader将Json字符串解析到root，root将包含Json里所有子元素
  string name = root["name"].asString();  // 访问节点，upload_id = "UP000000"
  int age = root["age"].asInt();    // 访问节点，code = 100
  cout << root << endl;
  cout << "name:" << name << endl;
  cout << "age:" << age << endl;
}
//定义结构体
struct Student {
  char ID[20];
  char name[10];
  int age;
  int gender;
  char major[10];
};
string serializeToJson(const Student& student);
Student deserializeToObj(const string& strJson);

void testWrite() {
  Student student;
  strcpy(student.ID, "312822199204085698");
  strcpy(student.name, "dablelv");
  student.age = 18;
  student.gender = 0;
  strcpy(student.major, "math");

  string strJson = serializeToJson(student);
  cout << "strJson:" << strJson << endl;

  string strJsonNew =
      "{\"ID\":\"201421031059\",\"name\":\"lvlv\",\"age\":18,\"gender\":0}";
  Student resStudent = deserializeToObj(strJsonNew);
  cout << "resStudent:" << endl;
  cout << "ID:" << resStudent.ID << endl;
  cout << "name:" << resStudent.name << endl;
  cout << "age:" << resStudent.age << endl;
  cout << "gender:" << resStudent.gender << endl;
  cout << "major:" << resStudent.major << endl;
}
/**
 * 将给定的学生对象序列化为json字符串
 */
string serializeToJson(const Student& student) {
}
/**
 * 将给定的json字符串反序列化为学生对象
 */
Student deserializeToObj(const string& strJson) {
  Json::Reader reader;
  Json::Value value;
  Student student;
  memset(&student, 0, sizeof(Student));

  if (reader.parse(strJson, value)) {
    strcpy(student.ID, value["ID"].asString().c_str());
    strcpy(student.name, value["name"].asString().c_str());
    student.age = value["age"].asInt();
    student.gender = value["gender"].asInt();
    strcpy(student.major, value["major"].asString().c_str());
  }
  return student;
}
