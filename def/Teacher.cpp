#include "../headers/Teacher.h"
#include<iostream>
using namespace std;
//definition of teacher class
Teacher::Teacher(){name="";course="";course_id="",id="",pass="";}
Teacher::~Teacher(){}
void Teacher::setCourse(string c){course=c;}
void Teacher::setCourseId(string ci){course_id=ci;}
string Teacher::getCourse(){return course;}
string Teacher::getCourseId(){return course_id;}