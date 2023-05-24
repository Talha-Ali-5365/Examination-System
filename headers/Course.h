#ifndef COURSE_H
#define COURSE_H
#include<iostream>
using namespace std;
//Course Class
class Course
{
private:
    int reg;
public:
    Course(int);
    ~Course();
    void setReg(int r);
    int getReg();
    friend ostream& operator<<(ostream&, const Course&);
    friend istream& operator>>(istream&, Course&);  
};
#endif