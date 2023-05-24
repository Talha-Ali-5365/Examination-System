#include "../headers/Student.h"
#include<iostream>
#include<fstream>
using namespace std;
//definition of student class
Student::Student():pf(0),oop(0),itc(0),ds(0),aa(0),sr(0),rm(0),bda(0),ai(0),dl(0),dip(0){serialno=0;name="";rollno="";id="",pass="";}
Student::~Student(){}
void Student::setSerial(int s){
    if(s<=0)
        cout<<"Invalid serial!"<<endl;
    else
        serialno=s;
}
//definition of all student class member functions
void Student::setRollno(string r){rollno=r;}
void Student::setPF(int i){pf.setReg(i);}
void Student::setOOP(int i){oop.setReg(i);}
void Student::setITC(int i){itc.setReg(i);}
void Student::setDS(int i){ds.setReg(i);}
void Student::setAA(int i){aa.setReg(i);}
void Student::setSR(int i){sr.setReg(i);}
void Student::setRM(int i){rm.setReg(i);}
void Student::setBDA(int i){bda.setReg(i);}
void Student::setAI(int i){ai.setReg(i);}
void Student::setDL(int i){dl.setReg(i);}
void Student::setDIP(int i){dip.setReg(i);}
int Student::getSerial(){return serialno;}
string Student::getRollno(){return rollno;}
int Student::getPF(){return pf.getReg();}
int Student::getOOP(){return oop.getReg();}
int Student::getITC(){return itc.getReg();}
int Student::getDS(){return ds.getReg();}
int Student::getAA(){return aa.getReg();}
int Student::getSR(){return sr.getReg();}
int Student::getRM(){return rm.getReg();}
int Student::getBDA(){return bda.getReg();}
int Student::getAI(){return ai.getReg();}
int Student::getDL(){return dl.getReg();}
int Student::getDIP(){return dip.getReg();}
