#ifndef SUB_H
#define SUB_H

#include "Mcq.h"
#include<iostream>
using namespace std;
//Subjective question class
class SUB:public MCQ
{
public:
    SUB();
    ~SUB();
};
SUB::SUB(){}
SUB::~SUB(){}

#endif