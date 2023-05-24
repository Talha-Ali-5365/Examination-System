#include "../headers/Mcq.h"
#include<iostream>
using namespace std;

//MCQ cpp file
//definitions of MCQ member functions
MCQ::MCQ(string d, int a):data(d), answer(a){}
MCQ::~MCQ(){}
//to set data
void MCQ::setData(string d){data=d;}
//to set answer of mcq
void MCQ::setAnswer(int a){
    if(a<0)
        cout<<"Invalid answer set!"<<endl;
    else
        answer=a;}
string MCQ::getData(){return data;}
double MCQ::getAnswer(){return answer;}
//to shuffle mcq options
void MCQ::shuffle(string s)
{
    srand(time(0));
    int ln=(rand()%5);
    int lines=0;
    string temp="",l1,l2,l3,l4;
    for(int i=0;i<data.length();i++)
    {
        if(lines==0)
            temp+=data[i];
        if(lines==1)
            l1+=data[i];
        if(lines==2)
            l2+=data[i];
        if(lines==3)
            l3+=data[i];
        if(lines==4)
            l4+=data[i];
        if(data[i]=='\n')
        {
            lines++;
            if(lines==1)
                l1+=to_string(lines)+". ";
            if(lines==2)
                l2+=to_string(lines)+". ";
            if(lines==3)
                l3+=to_string(lines)+". ";
            if(lines==4)
                l4+=to_string(lines)+". ";
        }
    }
    data="";
    data+=temp;
    if(ln==1 || ln==0)
    {
        data+=l1;
        data+=l2;
        l4[0]='3';
        data+=l4;
        l3[0]='4';
        data+=l3;
        if(answer==3)
            answer=4;
        else if(answer==4)
            answer=3;
    }
    if(ln==2)
    {
        l2[0]='1';
        data+=l2;
        l3[0]='2';
        data+=l3;
        l1[0]='3';
        data+=l1;
        l4[0]='4';
        data+=l4;
        if(answer==1)
            answer=3;
        else if(answer==2)
            answer=1;
        else if(answer==3)
            answer=2;
    }
    if(ln==3)
    {
        l3[0]='1';
        data+=l3;
        l4[0]='2';
        data+=l4;
        l2[0]='3';
        data+=l2;
        l1[0]='4';
        data+=l1;
        if(answer==1)
            answer=4;
        else if(answer==2)
            answer=3;
        else if(answer==3)
            answer=1;
        else if(answer==4)
            answer=2;
    }
    if(ln==4)
    {
        l4[0]='1';
        data+=l4;
        l1[0]='2';
        data+=l1;
        l3[0]='3';
        data+=l3;
        l2[0]='4';
        data+=l2;
        if(answer==1)
            answer=2;
        else if(answer==2)
            answer=4;
        else if(answer==4)
            answer=1;
    }
}
void MCQ::display(){cout<<data;};