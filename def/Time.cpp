#include "../headers/Time.h"
#include<iostream>
using namespace std;
//definition of time class to store time day and year
//constructor and member functions
Time::Time(int sh=0,int sm=0,int eh=0,int em=0,int d=0,int mo=0,int y=0):shour(sh),smin(sm),ehour(eh),emin(em),day(d),mon(mo),year(y) {}
void Time::setsHour(int h){
    if(h<0 || h>=24)
        cout<<"Invalid hours"<<endl;
    else
        shour=h;}
void Time::setsMin(int m){
    if(m<0 || m>=60)
        cout<<"Invalid mins"<<endl;
    else
        smin=m;}
void Time::seteHour(int h){
    if(h<0 || h>=60)
        cout<<"Invalid mins"<<endl;
    else
        ehour=h;}
void Time::seteMin(int m){
    if(m<0 || m>=60)
        cout<<"Invalid mins"<<endl;
    else
        emin=m;}
void Time::setDay(int d){
    if(d<=0 || d>=32)
        cout<<"Invalid Day"<<endl;
    else
        day=d;}
void Time::setMon(int m){
    if(m<=0 || m>=13)
        cout<<"Invalid month"<<endl;
    else
        mon=m;}
void Time::setYear(int y){
    year=y;}
int Time::getsHour(){return shour;}
int Time::getsMin(){return smin;}
int Time::geteHour(){return ehour;}
int Time::geteMin(){return emin;}
int Time::getDay(){return day;}
int Time::getMon(){return mon;}
int Time::getYear(){return year;}