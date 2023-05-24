#ifndef TIME_H
#define TIME_H

#include <iostream>
using namespace std;
//Time class
class Time{
private:
    int shour,smin,ehour,emin,day,mon,year;
public:
    Time(int,int,int,int,int,int,int);
    void setsHour(int);
    void setsMin(int);
    void seteHour(int);
    void seteMin(int);
    void setDay(int);
    void setMon(int);
    void setYear(int);
    int getsHour();
    int getsMin();
    int geteHour();
    int geteMin();
    int getDay();
    int getMon();
    int getYear();
};

#endif