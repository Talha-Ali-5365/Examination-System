#ifndef PROJECT_H
#define PROJECT_H

#include "Sub.h"
#include "Tf.h"
#include "../def/Course.cpp"
#include "../def/Mcq.cpp"
#include "../def/Quiz.cpp"
#include "../def/Student.cpp"
#include "../def/Teacher.cpp"
#include "../def/User.cpp"

using namespace std;
//Communication class between teacher and students
class COM_ST
{
private:
    Student* s;
    Teacher* t;
    const int t_length,file_length;
    int p_index;
public:
    COM_ST(Student*& ss, Teacher*& tt,const int,const int, int);
    int strlen(char *str);
    int strlen(string str);
    int intlen(int n);
    int getN(string s);
    char getch();
    void getInput(string);
    void generateLogins();
    string generatePass(string,int);
    string tostr(int n);
    string remove_ws(string, char);
    void Login_System();
    int checkslogin(string str,int choice);
    int checktlogin(string str,int choice);
    void reload_files();
    void StartMenu();
    void LoginMenu(int flag);
    void QuestionBankPrep();
    string remove_marker(string s,string m);
    int check_marker(string , string m);
    void Quiz_Cond();
    int getmins();
    int gethrs();
    int getdate();
    int getmon();
    int getyear();
    bool check_quiz(string name);
    string getpassword();
    string getAnswer(string s);
    void create_files(int,int,int,string,int,int);
};

#endif // FUNCTIONS_H