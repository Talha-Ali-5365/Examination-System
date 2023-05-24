#ifndef QUIZ_H
#define QUIZ_H

#include "Mcq.h"
#include "Mcq.h"
#include "Tf.h"
#include "Sub.h"
#include "../def/Time.cpp"
#include <iostream>
using namespace std;

//Quiz class
class Quiz
{
private:

private:
    MCQ *q1;
    TF *q2;
    SUB *q3;
    Time t;
public:
    Quiz(int);
    Quiz(string,int);
    Quiz(MCQ,TF,SUB,Time);
    void setMCQ(string,int);
    void setTF(string,int);
    void setSUB(string,int);
    MCQ*& getMCQ();
    TF*& getTF();
    SUB*& getSUB();
    void setT(int sh,int sm,int eh,int em,int,int,int);
    int getsHour();
    int getsMin();
    int geteHour();
    int geteMin();
    int getDay();
    int getMon();
    int getYear();
    ~Quiz();
};

#endif