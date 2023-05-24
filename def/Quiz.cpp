#include "../headers/Quiz.h"

#include<iostream>
using namespace std;
//definition of Quiz class
Quiz::Quiz(int a):t(){
    if(a==1)
    {
        q1=new MCQ();
        q2=nullptr;
        q3=nullptr;
    }
    else if(a==2)
    {
        q2=new TF();
        q1=nullptr;
        q3=nullptr;
    }
    else if(a==3)
    {
        q3=new SUB();
        q1=nullptr;
        q2=nullptr;
    }
}
Quiz::Quiz(string d, int a):t()
{
    if(a<=0)
        cout<<"Invalid arguments!"<<endl;
    else
    {
        if(q1!=nullptr)
        {
            q1->setData(d);
            q1->setAnswer(a);
        }
        else if(q2!=nullptr)
        {
            q2->setData(d);
            q2->setAnswer(a);
        }
        else if(q3!=nullptr)
        {
            q3->setData(d);
            q3->setAnswer(a);
        }
    }
}
Quiz::Quiz(MCQ m,TF t, SUB s,Time tt):t(tt)
{
    *q1=m;
    *q2=t;
    *q3=s;
}
//definition of all member functions
void Quiz::setMCQ(string d,int a){q1->setData(d);q1->setAnswer(a);}
void Quiz::setTF(string d,int a){q2->setData(d);q2->setAnswer(a);}
void Quiz::setSUB(string d,int a){q3->setData(d);q3->setAnswer(a);}
void Quiz::setT(int sh,int sm,int eh,int em,int d,int mo,int y){t.setsHour(sh);t.setsMin(sm);t.seteHour(eh);t.seteMin(em),t.setDay(d),t.setMon(mo),t.setYear(y);}
int Quiz::getsHour(){return t.getsHour();}
int Quiz::getsMin(){return t.getsMin();}
int Quiz::geteHour(){return t.geteHour();}
int Quiz::geteMin(){return t.geteMin();}
int Quiz::getDay(){return t.getDay();}
int Quiz::getMon(){return t.getMon();}
int Quiz::getYear(){return t.getYear();}
MCQ*& Quiz::getMCQ(){return q1;}
TF*& Quiz::getTF(){return q2;}
SUB*& Quiz::getSUB(){return q3;}
Quiz::~Quiz(){
    if(q1!=nullptr)
        delete q1;
    if(q2!=nullptr)
        delete q2;
    if(q3!=nullptr)
        delete q3;
}