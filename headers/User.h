#ifndef USER_H
#define USER_H

#include<iostream>
using namespace std;
//User class
class User{
private:
    
protected:
    string name,id,pass;
public:
    void setName(string);
    void setId(string);
    void setPass(string);
    string getName();
    string getId();
    string getPass();
};
#endif