#ifndef TEACHER_H
#define TEACHER_H
#include "User.h"
#include<iostream>
using namespace std;
//Teacher class
class Teacher:public User
{
private:
    string course,course_id;
public:
    Teacher();
    ~Teacher();
    void setCourse(string);
    void setCourseId(string);
    string getCourse();
    string getCourseId();
};

#endif