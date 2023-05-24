#ifndef STUDENT_H
#define STUDENT_H
#include "User.h"
#include<iostream>
using namespace std;

//Student class
class Student:public User
{
private:
    int serialno;
    Course pf,oop,itc,ds,aa,sr,rm,bda,ai,dl,dip;
    string rollno;
public:
    Student();
    ~Student();
    void setSerial(int);
    void setRollno(string);
    void setPF(int);
    void setOOP(int);
    void setITC(int);
    void setDS(int);
    void setAA(int);
    void setSR(int);
    void setRM(int);
    void setBDA(int);
    void setAI(int);
    void setDL(int);
    void setDIP(int);
    int getSerial();
    string getRollno();
    int getPF();
    int getOOP();
    int getITC();
    int getDS();
    int getAA();
    int getSR();
    int getRM();
    int getBDA();
    int getAI();
    int getDL();
    int getDIP();
};

#endif