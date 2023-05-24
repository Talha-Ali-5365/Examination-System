#include "../headers/User.h"
#include<iostream>
using namespace std;

//parent User class for Teacher and Student
//definitions of member functions
void User::setId(string i){id=i;}
void User::setPass(string p){pass=p;}
void User::setName(string n){name=n;}
string User::getId(){return id;}
string User::getPass(){return pass;}
string User::getName(){return name;}
