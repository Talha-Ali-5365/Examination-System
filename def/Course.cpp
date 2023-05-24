#include "../headers/Course.h"
#include<iostream>
using namespace std;
//Course cpp file
//definitions of Course member functions
Course::Course(int n=0):reg(n){}
Course::~Course(){}
void Course::setReg(int r){reg=r;}
int Course::getReg(){return reg;}

//Operator overloading
ostream& operator<<(ostream& os, const Course& c)
{
    os << c.reg;
    return os;
}
istream& operator>>(istream& is, Course& c)
{
    is >> c.reg;
    return is;
}