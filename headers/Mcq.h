#ifndef MCQ_H
#define MCQ_H

#include<iostream>
using namespace std;
//MCQ class
class MCQ
{
private:
    
protected:
    string data;
    double answer;
public:
    MCQ(string=" ",int=0);
    void setData(string);
    void setAnswer(int);
    string getData();
    double getAnswer();
    void shuffle(string);
    void display();
    ~MCQ();
};
#endif