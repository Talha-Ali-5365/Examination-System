//including necessary libs
#include <iostream>
#include <fstream>
#include "./def/proj.cpp"
#include <time.h>
#include <sstream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <ctime>
using namespace std;
namespace fs=std::filesystem;
//main function
int main()
{
    string filename="data.csv";
    const int file_length=216;
    const int t_length=11;
    Student *s=new Student[file_length];
    Teacher *t=new Teacher[t_length];
    COM_ST st(s,t,file_length,t_length,0);
    st.getInput(filename);
    st.generateLogins();
    // for(int i=0;i<11;i++)
    //     cout<<t[i].getId()<<" "<<t[i].getPass()<<" "<<t[i].getCourse()<<endl;
    // cout<<s[8].getId()<<" "<<s[8].getPass()<<endl;
    // cout<<s[5].getId()<<" "<<s[5].getPass()<<endl;
    // cout<<s[13].getId()<<" "<<s[13].getPass()<<endl;
    // cout<<s[4].getId()<<" "<<s[4].getPass()<<endl;
    // cout<<s[3].getId()<<" "<<s[3].getPass()<<endl;
    // cout<<s[3].getId()<<" "<<s[3].getPass()<<endl;
    // cout<<s[5].getId()<<" "<<s[5].getPass()<<endl;
    // cout<<s[3].getId()<<" "<<s[3].getPass()<<endl;
    // cout<<s[9].getId()<<" "<<s[9].getPass()<<endl;
    // cout<<s[3].getId()<<" "<<s[3].getPass()<<endl;
    // cout<<s[3].getId()<<" "<<s[3].getPass()<<endl;
    st.StartMenu();
}

