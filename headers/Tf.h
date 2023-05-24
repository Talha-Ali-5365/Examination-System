#ifndef TF_H
#define TF_H

#include "Mcq.h"
#include<iostream>
using namespace std;
//True false class
class TF:public MCQ
{
public:
    TF();
    ~TF();
    void shuffle(string);
};
TF::TF(){}
TF::~TF(){}
void TF::shuffle(string)
{
    srand(time(0));
    int ln=(rand()%3);
    int lines=0;
    string temp="",l1,l2;
    for(int i=0;i<data.length();i++)
    {
        if(lines==0)
            temp+=data[i];
        if(lines==1)
            l1+=data[i];
        if(lines==2)
            l2+=data[i];
        if(data[i]=='\n')
        {
            lines++;
            if(lines==1)
                l1+=to_string(lines)+". ";
            if(lines==2)
                l2+=to_string(lines)+". ";
        }
    }
    data="";
    data+=temp;
    if(ln==1 || ln==0)
    {
        data+=l1;
        data+=l2;
    }
    if(ln==2)
    {
        l2[0]='1';
        data+=l2;
        l1[0]='2';
        data+=l1;
        if(answer==1)
            answer=2;
        else if(answer==2)
            answer=1;
    }
}

#endif