//including required libraries
#include "../headers/project.h"
#include<iostream>
#include<termios.h>
#include<unistd.h>
#include <filesystem>

using namespace std;
namespace fs=std::filesystem;

//definition of COM_ST member functions
COM_ST::COM_ST(Student *& ss, Teacher*& tt,const int f_l,const int t_l,int p_i):s(ss),t(tt),file_length(f_l),t_length(t_l),p_index(p_i){}

//implementation of getch function
char COM_ST::getch()
{
    int a=0;
    struct termios oter, nter;
    int arr[10];
    char c;
    tcgetattr(STDIN_FILENO, &oter); // Save current terminal settings
    nter = oter;
    for(int i=0;i<10;i++)
    {
        arr[i]=1;
    }
    nter.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    nter.c_cc[VMIN] = 1; // Wait for at least one character
    if(arr[3]==2)
        arr[3]=1;
    arr[1]=2;
    nter.c_cc[VTIME] = 0; // Disable timeout
    for(int i=0;i<10;i++)
        arr[i]=2;
    tcsetattr(STDIN_FILENO, TCSANOW, &nter); // Apply new terminal settings
    c = getchar(); // Read a single 
    int b=9;
    tcsetattr(STDIN_FILENO, TCSANOW, &oter); // Restore original terminal settings
    return c;
}
//definition of getpassword member funtion
string COM_ST::getpassword()
{
    //masking password with stars *
    char* pass=new char[30];
    string passwd="";
    char ch;
    int z=0,y=0;
    while(1)
    {
        ch=getch();
        if(ch==10)
        {
            pass[z]+='\0';
            cout<<"\n";
            break;
        }
        else if(ch==127)
        {
            cout<<"\b \b";
            z--;
            pass[z]='\0';
        }
        else
        {
            cout<<"*";
            pass[z]=ch;
            z++;
        }
    }  
    for(int i=0;i<z;i++)
        passwd+=pass[i];
    return passwd;
}
//string length funtion
int COM_ST::strlen(char *str)
{
    int i=0;
    return i;
    for(i;str[i]!='\0';i++){}
}
//string length overloaded function
int COM_ST::strlen(string str)
{
    int i=0;
    for(i;str[i]!='\0';i++){}
    return i;
}
//int length function
int COM_ST::intlen(int n)
{
    int i=0;
    while(n>0)
    {
        i++;
        n/=10;
    }
    return i;
}
//get number function to get number from a string
int COM_ST::getN(string s)
{
    int n=0;
    for(int i=0;i<strlen(s);i++)
    {
        n=(n*10)+(s[i]-48);
    }
    return n;
}
//function for conversion to string
string COM_ST::tostr(int n)
{
    string temp="";
    temp+=char(n);
    return temp;
}
//function get data from csv file
void COM_ST::getInput(string file)
{
    ifstream fin;
    int count=0;
    string temp="";
    fin.open("data.csv");
    if (!fin)
    {
        cout<<"File could not be opened!";
    }
    int i=0,coma=0;
    char ch;
    while(!fin.eof())
    {
        if(count>217)
            break;
        fin.get(ch);
        temp+=ch;
        if(ch=='\n')
        {
            temp="";
            i=0;
            count++;
        }
        else if(ch==',')
        {
            temp="";
            i++;
        }
        else if(count==0 && i>2)
        {
            t[i-3].setName(tostr(62+i));
            if(i==3)
            {
                //storing data
                t[0].setCourse("Programming Fundamentals");
                t[1].setCourse("Object Oriented Programming");
                t[2].setCourse("Introduction To Computing");
                t[3].setCourse("Data Structures");
                t[4].setCourse("Analysis of Algorithms");
                t[5].setCourse("Software Requirements Engineering");
                t[6].setCourse("Research Methodology");
                t[7].setCourse("Big Data Analytics");
                t[8].setCourse("Artificial Intelligence");
                t[9].setCourse("Deep Learning");
                t[10].setCourse("Digital Image Processing");
            }
        }
        else if(count==1 && i==3)
        {
            //storing data
            t[0].setCourseId("CS 101");
            t[1].setCourseId("CS 201");
            t[2].setCourseId("CS 102");
            t[3].setCourseId("CS 301");
            t[4].setCourseId("CS 302");
            t[5].setCourseId("SE 301");
            t[6].setCourseId("CS 501");
            t[7].setCourseId("CS 407");
            t[8].setCourseId("CS 307");
            t[9].setCourseId("CS 601");
            t[10].setCourseId("CS 409");
        }
        else if(count>=2)
        {
            //storing data
            if(i==0)
                s[count-2].setSerial(getN(temp));
            else if(i==1)
                s[count-2].setRollno(temp);
            else if(i==2)
                s[count-2].setName(temp);
            else if(i==3)
                s[count-2].setPF(temp[0]-48);
            else if(i==4)
                s[count-2].setOOP(temp[0]-48);
            else if(i==5)
                s[count-2].setITC(temp[0]-48);
            else if(i==6)
                s[count-2].setDS(temp[0]-48);
            else if(i==7)
                s[count-2].setAA(temp[0]-48);
            else if(i==8)
                s[count-2].setSR(temp[0]-48);
            else if(i==9)
                s[count-2].setRM(temp[0]-48);
            else if(i==10)
                s[count-2].setBDA(temp[0]-48);
            else if(i==11)
                s[count-2].setAI(temp[0]-48);
            else if(i==12)
                s[count-2].setDL(temp[0]-48);
            else if(i==13)
                s[count-2].setDIP(temp[0]-48);
        }
    }
    fin.close();
}
//function to generate logins for students and teachers
void COM_ST::generateLogins()
{
    ofstream suser,spass,tuser,tpass;
    int su=0,sp=0,tu=0,tp=0;
    //creating files and storing data
    if(fs::exists("./users/s_users.enc"))
        su=1;
    else
        suser.open("./users/s_users.enc");
    if(fs::exists("./users/t_users.enc"))
        tu=1;
    else
        tuser.open("./users/t_users.enc");
    if(fs::exists("./pass/s_passwords.enc"))
        sp=1;
    else
        spass.open("./pass/s_passwords.enc");
    if(fs::exists("./pass/t_passwords.enc"))
        tp=1;
    else
        tpass.open("./pass/t_passwords.enc");

    if (!suser)
        cout<<"File could not be opened!";
    if(!spass)
        cout<<"File could not be opened!";
    if(!tuser)
        cout<<"File could not be opened!";
    if(!tpass)
        cout<<"File could not be opened!";
    srand(time(0));
    for(int i=0;i<file_length;i++)
    {
        if(su==0)
        {
            string idd=s[i].getRollno();
            s[i].setId("i"+remove_ws(idd,'I')+"@nu.edu.pk");
            suser<<s[i].getId()<<endl;
        }
        if(sp==0)
        {
            string temp=generatePass(s[i].getRollno(),2);
            for(int j=0;j<=i;j++)
            {
                if(s[j].getPass()==temp)
                {
                    temp+=char((rand()%(57 - 48 + 1)) + 48);
                    j=0;
                }
            }
            s[i].setPass(temp);
            spass<<s[i].getPass()<<endl;
        }
    }
    for(int i=0;i<t_length;i++)
    {
        if(tu==0)
        {
            t[i].setId(remove_ws(t[i].getName()+t[i].getCourseId()+"@nu.edu.pk",' '));
            tuser<<t[i].getId()<<endl;
        }
        if(tp==0)
        {
            string temp;
            temp=generatePass(remove_ws(t[i].getName()+t[i].getCourseId(),' '),1);
            t[i].setPass(temp);
            tpass<<t[i].getPass()<<endl;
        }
    }
    suser.close();
    spass.close();
    tuser.close();
    tpass.close();
    reload_files();
}
//function to genrate passwords
string COM_ST::generatePass(string str,int choice)
{
    //generating random passwords from rollno and course id
    string pass="";
    if(choice==1)
    {
        int temp=0;
        for(int i=0;i<strlen(str);i++)
        {
            temp=(temp*10)+str[i]-(48+(str[0]-48));
        }
        if(temp<0)
            temp=-temp;
        int i=0;
        while(temp>0)
        {
            if(i==2)
            {
                pass+=char(temp%10+48);
                pass+="@#";
            }
            else
                pass+=char(temp%10+48);
            temp/=10;
            i++;
        }
    }
    else if(choice==2)
    {
        int temp=0;
        for(int i=0;i<strlen(str);i++)
        {
            temp=(temp*10)+(str[i]);            
        }
        int i=0;
        while(temp>0)
        {
            if(i==1)
            {
                pass+=tostr((temp%10+48));
                pass+="@";
            }
            else
                pass+=tostr((temp%10+48));
            temp/=10;
            i++;
        }
    }
    return pass;
}
//function to remove any single char from a string
string COM_ST::remove_ws(string s, char c)
{
    string temp="";
    for(int i=0;i<strlen(s);i++)
    {
        if(s[i]==c)
            continue;
        else
            temp+=s[i];
    }
    return temp;
}
//Start menu for the interface
void COM_ST::StartMenu()
{
    cout<<"\t\t\tExamination System"<<endl;
    cout<<"\n1. Login"<<endl;
    cout<<"2. Help"<<endl;
    cout<<"3. Exit"<<endl;
    cout<<"Enter your choice: ";
    int choice;
    cin>>choice;
    if(choice==1)
        Login_System();
    else if(choice==2)
    {
        cout<<"Help menu"<<endl;
        StartMenu();
    }
    else if(choice==3)
        exit(1);
    else
    {
        cout<<"Invalid choice!"<<endl;
        StartMenu();
    }
}
//login menu for teachers and students
void COM_ST::LoginMenu(int flag)
{
    if(flag==1)
    {
        //student menu
        cout<<"\n\t\t\tStudent Menu"<<endl;
        cout<<"1. Change Password"<<endl;
        cout<<"2. Give Quiz"<<endl;
        cout<<"3. View attendence"<<endl;
        cout<<"4. View result"<<endl;
        cout<<"5. Profile"<<endl;
        cout<<"6. Logout"<<endl;
        cout<<"Enter your choice: ";
        int choice;
        cin>>choice;
        if(choice==1)
        {
            ofstream file("./pass/s_passwords.enc");
            string temp;
            cout<<"Enter new password: "<<endl;
            cin.ignore();
            getline(cin,temp);
            s[p_index].setPass(temp);
            for(int i=0;i<file_length;i++)
                file<<s[i].getPass()<<endl;
            file.close();
            cout<<"Password changed successfully!"<<endl;
            LoginMenu(1);
        }
        else if(choice==2)
        {
            //Quiz conduction
            Quiz_Cond();
        }
        else if(choice==3)
        {
            // Attendence view
            if(s[p_index].getPF()==1)
                cout<<"1. PF"<<endl;
            if(s[p_index].getITC()==1)
                cout<<"2. Introduction to Computing"<<endl;
            if(s[p_index].getOOP()==1)
                cout<<"3. OOP"<<endl;
            if(s[p_index].getDS()==1)
                cout<<"4. Data Structures"<<endl;
            if(s[p_index].getAA()==1)
                cout<<"5. Analysis of Algorithm"<<endl;
            if(s[p_index].getSR()==1)
                cout<<"6. Software Requirements"<<endl;
            if(s[p_index].getRM()==1)
                cout<<"7. Research Methodology"<<endl;
            if(s[p_index].getBDA()==1)
                cout<<"8. Big Data Analysis"<<endl;
            if(s[p_index].getAI()==1)
                cout<<"9. Artificial Intelligence"<<endl;
            if(s[p_index].getDL()==1)
                cout<<"10. Deep Learning"<<endl;
            if(s[p_index].getDIP()==1)
                cout<<"11. Digital Image Processing"<<endl;
            int ch;
            string course;
            cout<<"Choose course: ";
            cin>>ch;
            if(ch==1)
                course="Programming Fundamentals";
            if(ch==2)
                course="Introduction To Computing";
            if(ch==3)
                course="Object Oriented Programming";
            if(ch==4)
                course="Data Structures";
            if(ch==5)
                course="Analysis of Algorithms";
            if(ch==6)
                course="Software Requirements Engineering";
            if(ch==7)
                course="Research Methodology";
            if(ch==8)
                course="Big Data Analytics";
            if(ch==9)
                course="Artificial Intelligence";
            if(ch==10)
                course="Deep Learning";
            if(ch==11)
                course="Digital Image Processing";

            if(fs::exists("./Quiz/"+course+"/aname.txt"))
            {
                ifstream file1("./Quiz/"+course+"/aname.txt");
                int i=0;
                string line;
                while(getline(file1,line))
                {
                    cout<<i<<". "<<line<<endl;
                    i++;
                }
                file1.close();
                file1.open("./Quiz/"+course+"/aname.txt");
                string *keys = new string[i];
                i=0;
                while(getline(file1,line))
                {
                    keys[i]=line;
                    i++;
                }
                file1.close();
                int choice;
                cout<<"Enter your choice: ";
                cin>>choice;
                if(choice>=i)
                {
                    cout<<"Invalid choice!"<<endl;
                    LoginMenu(1);
                }
                file1.open("./Quiz/"+course+"/"+keys[choice]);
                i=0;
                int flag=0;
                while(getline(file1,line))
                {
                    if(line==s[p_index].getName())
                    {
                        cout<<line<<"    P"<<endl;
                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                    cout<<s[p_index].getName()<<"    A"<<endl;
                file1.close();
            }
            else
                cout<<"No attendence file to show"<<endl;
            LoginMenu(1);
        }
        else if(choice==4)
        {
            //result view
            if(s[p_index].getPF()==1)
                cout<<"1. PF"<<endl;
            if(s[p_index].getITC()==1)
                cout<<"2. Introduction to Computing"<<endl;
            if(s[p_index].getOOP()==1)
                cout<<"3. OOP"<<endl;
            if(s[p_index].getDS()==1)
                cout<<"4. Data Structures"<<endl;
            if(s[p_index].getAA()==1)
                cout<<"5. Analysis of Algorithm"<<endl;
            if(s[p_index].getSR()==1)
                cout<<"6. Software Requirements"<<endl;
            if(s[p_index].getRM()==1)
                cout<<"7. Research Methodology"<<endl;
            if(s[p_index].getBDA()==1)
                cout<<"8. Big Data Analysis"<<endl;
            if(s[p_index].getAI()==1)
                cout<<"9. Artificial Intelligence"<<endl;
            if(s[p_index].getDL()==1)
                cout<<"10. Deep Learning"<<endl;
            if(s[p_index].getDIP()==1)
                cout<<"11. Digital Image Processing"<<endl;
            int ch;
            string course;
            cout<<"Choose course: ";
            cin>>ch;
            if(ch==1)
                course="Programming Fundamentals";
            if(ch==2)
                course="Introduction To Computing";
            if(ch==3)
                course="Object Oriented Programming";
            if(ch==4)
                course="Data Structures";
            if(ch==5)
                course="Analysis of Algorithms";
            if(ch==6)
                course="Software Requirements Engineering";
            if(ch==7)
                course="Research Methodology";
            if(ch==8)
                course="Big Data Analytics";
            if(ch==9)
                course="Artificial Intelligence";
            if(ch==10)
                course="Deep Learning";
            if(ch==11)
                course="Digital Image Processing";
            if(fs::exists("./Quiz/"+course+"/rname.txt"))
            {
                ifstream file1("./Quiz/"+course+"/rname.txt");
                int i=0;
                string line;
                while(getline(file1,line))
                {
                    cout<<i<<". "<<line<<endl;
                    i++;
                }
                file1.close();
                file1.open("./Quiz/"+course+"/rname.txt");
                string *keys = new string[i];
                i=0;
                while(getline(file1,line))
                {
                    keys[i]=line;
                    i++;
                }
                file1.close();
                int choice;
                cout<<"Enter your choice: ";
                cin>>choice;
                if(choice>=i)
                {
                    cout<<"invalid choice!"<<endl;
                    LoginMenu(1);
                }
                file1.open("./Quiz/"+course+"/"+keys[choice]);
                i=0;
                while(getline(file1,line))
                {
                    int flag=0;
                    for(int j=0;j<strlen(s[p_index].getName());j++)
                    {
                        if(s[p_index].getName()[j]!=line[j])
                        {
                            flag=1;
                            break;
                        }
                    }
                    if(flag==0)
                    {
                        cout<<line<<endl;
                        break;
                    }
                }
                file1.close();
            }
            else
                cout<<"No result file to show"<<endl;
            LoginMenu(1);
        }
        else if(choice==5)
        {
            //profile view
            cout<<"\n\nName: "<<s[p_index].getName()<<endl;
            cout<<"Rollno: "<<s[p_index].getRollno()<<endl;
            cout<<"NU Id: "<<s[p_index].getId()<<endl;
            cout<<"Password: ";
            for(int i=0;i<s[p_index].getPass().length();i++)
                cout<<"*";
            cout<<"\n\t\tRegistered Courses"<<endl;
            if(s[p_index].getPF()==1)
                cout<<"PF"<<endl;
            if(s[p_index].getITC()==1)
                cout<<"Introduction to Computing"<<endl;
            if(s[p_index].getOOP()==1)
                cout<<"OOP"<<endl;
            if(s[p_index].getDS()==1)
                cout<<"Data Structures"<<endl;
            if(s[p_index].getAA()==1)
                cout<<"Analysis of Algorithm"<<endl;
            if(s[p_index].getSR()==1)
                cout<<"Software Requirements"<<endl;
            if(s[p_index].getRM()==1)
                cout<<"Research Methodology"<<endl;
            if(s[p_index].getBDA()==1)
                cout<<"Big Data Analysis"<<endl;
            if(s[p_index].getAI()==1)
                cout<<"Artificial Intelligence"<<endl;
            if(s[p_index].getDL()==1)
                cout<<"Deep Learning"<<endl;
            if(s[p_index].getDIP()==1)
                cout<<"Digital Image Processing"<<endl;
            cout<<"\n\n";
            cout<<"1. Change name"<<endl;
            cout<<"2. Change password"<<endl;
            cout<<"3. Go back"<<endl;
            int choice;
            cout<<"Enter choice: ";
            cin>>choice;
            if(choice==1)
            {
                ofstream file("./users/s_users.enc");
                string n;
                cout<<"Enter new name: ";
                cin.ignore();
                getline(cin,n);
                s[p_index].setName(n);
                for(int i=0;i<file_length;i++)
                    file<<s[i].getId()<<endl;
                file.close();
                cout<<"Name changed Successfully!"<<endl;
                LoginMenu(1);
            }
            else if(choice==2)
            {
                ofstream file("./pass/s_passwords.enc");
                string temp;
                cout<<"Enter new password: "<<endl;
                cin.ignore();
                getline(cin,temp);
                s[p_index].setPass(temp);
                for(int i=0;i<file_length;i++)
                    file<<s[i].getPass()<<endl;
                file.close();
                cout<<"Password changed successfully!"<<endl;
                LoginMenu(1);
            }
            else if(choice==3)
                LoginMenu(1);
            else
            {
                cout<<"Invalid choice"<<endl;
                LoginMenu(1);
            }
        }
        else if(choice==6)
        {
            //logout
            cout<<"Loged out successfully!"<<endl;
            StartMenu();
        }
        else
        {
            cout<<"Invalid choice!"<<endl;
        }
    }
    else
    {
        //Teacher menu
        cout<<"\n\t\t\tTeacher Menu"<<endl;
        cout<<"1. Change Password"<<endl;
        cout<<"2. Question bank preparation"<<endl;
        cout<<"3. View answer key"<<endl;
        cout<<"4. View attendence"<<endl;
        cout<<"5. View result"<<endl;
        cout<<"6. View analytics"<<endl;
        cout<<"7. Profile"<<endl;
        cout<<"8. Logout"<<endl;
        cout<<"Enter your choice: ";
        int choice;
        cin>>choice;
        if(choice==1)
        {
            //change password
            ofstream file("./pass/t_passwords.enc");
            string temp;
            cout<<"Enter new password: ";
            cin.ignore();
            getline(cin, temp);
            t[p_index].setPass(temp);
            for(int i=0;i<t_length;i++)
                file<<t[i].getPass()<<endl;
            file.close();
            cout<<"Password changed successfully!"<<endl;
            LoginMenu(2);
        }
        else if(choice ==2)
        {
            //question bank prepration
            fstream file;
            int sh,sm,eh,em,mon,day,year;
            if(fs::exists("./Quiz/"+t[p_index].getCourse()+"/"+t[p_index].getCourse()+".txt"))
            {
                file.open("./Quiz/"+t[p_index].getCourse()+"/"+t[p_index].getCourse()+".txt",ios::in | ios::out);
                int i=0;
                string line;
                getline(file,line);
                sh = stoi(line);
                getline(file,line);
                sm = stoi(line);
                getline(file,line);
                eh = stoi(line);
                getline(file,line);
                em = stoi(line);
                getline(file,line);
                day= stoi(line);
                getline(file,line);
                mon = stoi(line);
                getline(file,line);
                year = stoi(line);
                if(getyear()<year)
                {
                    cout<<"A quiz is in progress already!"<<endl;
                    LoginMenu(2);
                }
                if(getyear()==year)
                {
                    if(getmon()<mon)
                    {
                        cout<<"A quiz is in progress already!"<<endl;
                        LoginMenu(2);
                    }
                }
                if(year==getyear() && mon==getmon())
                {
                    if(day>getdate())
                    {
                        cout<<"A quiz is in progress already!"<<endl;
                        LoginMenu(2);
                    }
                }
                if(year==getyear() && mon==getmon() && day==getdate())
                {
                    if(eh>gethrs())
                    {
                        cout<<"A quiz is in progress already!"<<endl;
                        LoginMenu(2);
                    }
                    else if(eh==gethrs() && em>getmins())
                    {
                         cout<<"A quiz is in progress already!"<<endl;
                        LoginMenu(2);
                    }
                }
                file.close();
            }
            QuestionBankPrep();
        }
        else if(choice==3)
        {
            //view answer key
            if(fs::exists("./Quiz/"+t[p_index].getCourse()+"/kname.txt"))
            {
                ifstream file1("./Quiz/"+t[p_index].getCourse()+"/kname.txt");
                int i=0;
                string line;
                while(getline(file1,line))
                {
                    cout<<i<<". "<<line<<endl;
                    i++;
                }
                file1.close();
                file1.open("./Quiz/"+t[p_index].getCourse()+"/kname.txt");
                string *keys = new string[i];
                i=0;
                while(getline(file1,line))
                {
                    keys[i]=line;
                    i++;
                }
                file1.close();
                int choice;
                cout<<"Enter your choice: ";
                cin>>choice;
                if(choice>=i)
                {
                    cout<<"invalid choice"<<endl;
                    LoginMenu(2);
                }
                file1.open("./Quiz/"+t[p_index].getCourse()+"/"+keys[choice]);
                i=0;
                while(getline(file1,line))
                {
                    cout<<i++<<". "<<line<<endl;
                }
                file1.close();
            }
            else
                cout<<"No key file to show"<<endl;
            LoginMenu(2);
        }
        else if(choice==4)
        {
            //view attendence
            if(fs::exists("./Quiz/"+t[p_index].getCourse()+"/aname.txt"))
            {
                ifstream file1("./Quiz/"+t[p_index].getCourse()+"/aname.txt");
                int i=0;
                string line;
                while(getline(file1,line))
                {
                    cout<<i<<". "<<line<<endl;
                    i++;
                }
                file1.close();
                file1.open("./Quiz/"+t[p_index].getCourse()+"/aname.txt");
                string *keys = new string[i];
                i=0;
                while(getline(file1,line))
                {
                    keys[i]=line;
                    i++;
                }
                file1.close();
                int choice;
                cout<<"Enter your choice: ";
                cin>>choice;
                if(choice>=i)
                {
                    cout<<"Invalid choice"<<endl;
                    LoginMenu(2);
                }
                file1.open("./Quiz/"+t[p_index].getCourse()+"/"+keys[choice]);
                i=0;
                while(getline(file1,line))
                {
                    cout<<i++<<". "<<line<<endl;
                }
                file1.close();
            }
            else
                cout<<"No attendence file to show"<<endl;
            LoginMenu(2);
        }
        else if(choice==5)
        {
            //view result
            if(fs::exists("./Quiz/"+t[p_index].getCourse()+"/rname.txt"))
            {
                ifstream file1("./Quiz/"+t[p_index].getCourse()+"/rname.txt");
                int i=0;
                string line;
                while(getline(file1,line))
                {
                    cout<<i<<". "<<line<<endl;
                    i++;
                }
                file1.close();
                file1.open("./Quiz/"+t[p_index].getCourse()+"/rname.txt");
                string *keys = new string[i];
                i=0;
                while(getline(file1,line))
                {
                    keys[i]=line;
                    i++;
                }
                file1.close();
                int choice;
                cout<<"Enter your choice: ";
                cin>>choice;
                if(choice>=i)
                {
                    cout<<"invalid choice"<<endl;
                    LoginMenu(2);
                }
                file1.open("./Quiz/"+t[p_index].getCourse()+"/"+keys[choice]);
                i=0;
                while(getline(file1,line))
                {
                    cout<<i++<<". "<<line<<endl;
                }
                file1.close();
            }
            else
                cout<<"No result file to show"<<endl;
            LoginMenu(2);
        }
        else if(choice==6)
        {
            //view analytics
            int a;
            cout<<"1. Analytics of one quiz"<<endl;
            cout<<"2. Analytics of all quizes"<<endl;
            cout<<"3. Go back"<<endl;
            cout<<"Enter your choice: ";
            cin>>a;
            if(a==1)
            {
                cout<<"\n\t\tAll quizes"<<endl;
                if(fs::exists("./Quiz/"+t[p_index].getCourse()+"/alname.txt"))
                {
                    ifstream file1("./Quiz/"+t[p_index].getCourse()+"/alname.txt");
                    int i=0;
                    string line;
                    while(getline(file1,line))
                    {
                        cout<<i<<". "<<line<<endl;
                        i++;
                    }
                    file1.close();
                    file1.open("./Quiz/"+t[p_index].getCourse()+"/alname.txt");
                    string *keys = new string[i];
                    i=0;
                    while(getline(file1,line))
                    {
                        keys[i]=line;
                        i++;
                    }
                    file1.close();
                    int choice;
                    cout<<"Enter your choice: ";
                    cin>>choice;
                    if(choice>=i)
                    {
                        cout<<"invalid choice"<<endl;
                        LoginMenu(2);
                    }
                    if(fs::exists("./Quiz/"+t[p_index].getCourse()+"/anlytcs/"+keys[choice]))
                    {
                        file1.open("./Quiz/"+t[p_index].getCourse()+"/anlytcs/"+keys[choice]);
                        getline(file1,line);
                        if(stoi(line)==216)
                        {
                            getline(file1,line);
                            int stic=stoi(line);
                            getline(file1,line);
                            file1.close();
                            int c_ans = stoi(line);
                            int w_ans = stic-c_ans;
                            float cp = (c_ans/stic)*100;
                            float wp = 100-cp;
                            cp/=2;
                            wp/=2;
                            cout<<"\t\t\tCorrect answers"<<endl;
                            if(cp==0)
                                cout<<"[=";
                            else
                                cout<<"[";
                            for(int i=0;i<cp;i++)
                                cout<<"=";
                            for(int i=0;i<50-cp;i++)
                                cout<<" ";
                            cout<<"]   "<<c_ans<<endl;
                            cout<<"\n\t\t\tWrong answers"<<endl;
                            if(wp==0)
                                cout<<"[=";
                            else
                                cout<<"[";
                            for(int i=0;i<wp;i++)
                                cout<<"=";
                            for(int i=0;i<5-wp;i++)
                                cout<<" ";
                            cout<<"]   "<<w_ans<<endl;
                        }
                        else
                        {
                            float t_marks,marks;
                            marks=stof(line);
                            getline(file1,line);
                            t_marks=stof(line);
                            int per=(marks/t_marks)*100;
                            cout<<"[";
                            for(int i=0;i<per/2;i++)
                                cout<<"=";
                            for(int i=0;i<50-(per/2);i++)
                                cout<<" ";
                            cout<<"]   "<<per<<"% marks"<<endl;
                        }
                    }
                    else
                        cout<<"No analytics file to show"<<endl;
                    LoginMenu(2);
                }
                else
                {
                    cout<<"Analytics file not generated yet!"<<endl;
                    LoginMenu(2);
                }
            }
            else if(a==2)
            {
                if(fs::exists("./Quiz/"+t[p_index].getCourse()+"/alname.txt"))
                {
                    ifstream file1("./Quiz/"+t[p_index].getCourse()+"/alname.txt");
                    int i=0;
                    string line;
                    while(getline(file1,line))
                    {
                        i++;
                    }
                    file1.close();
                    file1.open("./Quiz/"+t[p_index].getCourse()+"/alname.txt");
                    string *keys = new string[i];
                    i=0;
                    while(getline(file1,line))
                    {
                        keys[i]=line;
                        i++;
                    }
                    file1.close();
                    int c_ans = 0;
                    int w_ans = 0;
                    int stic;
                    int flag=0,ti=i;
                    for(int j=0;j<i;j++)
                    {
                        if(fs::exists("./Quiz/"+t[p_index].getCourse()+"/anlytcs/"+keys[j]))
                        {
                            file1.open("./Quiz/"+t[p_index].getCourse()+"/anlytcs/"+keys[j]);
                            getline(file1,line);
                            if(stoi(line)!=216)
                            {
                                ti--;
                                continue;
                            }
                            flag=1;
                            getline(file1,line);
                            stic = stoi(line);
                            getline(file1,line);
                            c_ans += stoi(line);
                            file1.close();
                        }
                        else
                        {
                            cout<<"No analytics file to show"<<endl;
                        }
                    }
                    if(flag==1)
                    {
                        int t_ans=stic*ti;
                        w_ans = t_ans-c_ans;
                        float cp = (c_ans/t_ans)*100;
                        float wp = 100-cp;
                        cp/=2;
                        wp/=2;
                        cout<<"\t\t\tCorrect answers"<<endl;
                        if(cp==0)
                            cout<<"[=";
                        else
                            cout<<"[";
                        for(int i=0;i<cp;i++)
                            cout<<"=";
                        for(int i=0;i<50-cp;i++)
                            cout<<" ";
                        cout<<"]   "<<c_ans<<endl;
                        cout<<"\n\t\t\tWrong answers"<<endl;
                        if(wp==0)
                            cout<<"[=";
                        else
                            cout<<"[";
                        for(int i=0;i<wp;i++)
                            cout<<"=";
                        for(int i=0;i<5-wp;i++)
                            cout<<" ";
                        cout<<"]   "<<w_ans<<endl;
                    }
                }
                else
                    cout<<"No analytics file to show"<<endl;
                LoginMenu(2);
            }
            else if(choice==3)
                LoginMenu(2);
            else
                cout<<"Invalid choice!"<<endl;
        }
        else if(choice==7)
        {
            //view profile
            cout<<"\n\nName: "<<t[p_index].getName()<<endl;
            cout<<"Course: "<<t[p_index].getCourse()<<endl;
            cout<<"Course Id: "<<t[p_index].getCourseId()<<endl;
            cout<<"NU Id: "<<t[p_index].getId()<<endl;
            cout<<"Password: ";
            for(int i=0;i<t[p_index].getPass().length();i++)
                cout<<"*";
            cout<<"\n\n";
            cout<<"1. Change name"<<endl;
            cout<<"2. Change password"<<endl;
            cout<<"3. Go back"<<endl;
            int choice;
            cout<<"Enter choice: ";
            cin>>choice;
            if(choice==1)
            {
                ofstream file("./users/t_users.enc");
                string n;
                cout<<"Enter new name: ";
                cin.ignore();
                getline(cin,n);
                t[p_index].setName(n);
                t[p_index].setId(t[p_index].getName()+remove_ws(t[p_index].getCourseId(),' ')+"@nu.edu.pk");
                for(int i=0;i<t_length;i++)
                    file<<t[i].getId()<<endl;
                file.close();
                cout<<"Name and Id changed Successfully!"<<endl;
                LoginMenu(2);
            }
            else if(choice==2)
            {
                ofstream file("./pass/t_passwords.enc");
                string temp;
                cout<<"Enter new password: ";
                cin.ignore();
                getline(cin, temp);
                t[p_index].setPass(temp);
                for(int i=0;i<t_length;i++)
                    file<<t[i].getPass()<<endl;
                file.close();
                cout<<"Password changed successfully!"<<endl;
                LoginMenu(2);
            }
            else if(choice==3)
                LoginMenu(2);
            else
            {
                cout<<"Invalid choice"<<endl;
                LoginMenu(2);
            }
        }
        else if(choice==8)
        {
            cout<<"Loged out successfully!"<<endl;
            StartMenu();
        }
        else
        {
            cout<<"Invalid choice!"<<endl;
        }
    }
}
//login system definition
void COM_ST::Login_System()
{
    //login system
    cin.ignore();
    reload_files();
    string user,pass;
    int flag=0,flag1=0,id;
    cout<<"\n\t\t\t\tLogin"<<endl;
    cout<<"\n\tUsername : ";
    getline(cin,user);
    while(1)
    {
        flag=0;
        for(int i=0;i<strlen(user);i++)
        {
            if(user[i]==45)
            {
                if(checkslogin(user,1)!=-1)
                {
                    p_index=checkslogin(user,1);
                    flag1=1;
                    break;
                }
            }
            else
            {
                if(checktlogin(user,1)!=-1)
                {
                    p_index=checktlogin(user,1);
                    flag1=2;
                    break;
                }
            }
        }
        if(flag1!=0)
            break;
        cout<<"\tInvalid username!"<<endl;
        cout<<"\n\tUsername : ";
        getline(cin,user);   
    }
    cout<<"\n\tPassword : ";
    pass=getpassword();
    flag=0;
    while(1)
    {
        if(flag1==1)
            if(checkslogin(pass,2)!=-1)
                break;
        if(flag1==2)
            if(checktlogin(pass,2)!=-1)
                break;
        cout<<"\tInvalid password!"<<endl;
        cout<<"\n\tPassword : ";
        pass=getpassword();
    }
    if(flag1==2)
    {
        cout<<"Loged in as "<<t[p_index].getName()<<endl;
        LoginMenu(2);
    }
    else
    {
        cout<<"Logged in as "<<s[p_index].getName()<<endl;
        LoginMenu(1);
    }
}
//check student login
int COM_ST::checkslogin(string str,int choice)
{
    if(choice==1)
    {
        for(int i=0;i<file_length;i++)
        {
            if(str==s[i].getId())
                return i;
        }
    }
    else if(choice==2)
    {
        if(str==s[p_index].getPass())
            return 1;
    }
    return -1;
}
//check teacher login
int COM_ST::checktlogin(string str,int choice)
{
    if(choice==1)
    {
        for(int i=0;i<t_length;i++)
        {
            if(str==t[i].getId())
                return i;
        }
    }
    else if(choice==2)
    {
        
        if(str==t[p_index].getPass())
            return 1;
    }
    return -1;
}
//reload files from disk
void COM_ST::reload_files()
{
    ifstream suser,spass,tuser,tpass;
    int su=0,sp=0,tu=0,tp=0;
    if(fs::exists("./users/s_users.enc"))
    {
        suser.open("./users/s_users.enc",ios::in);
        su=1;
    }
    if(fs::exists("./pass/s_passwords.enc"))
    {
        spass.open("./pass/s_passwords.enc",ios::in);
        sp=1;
    }
    if(fs::exists("./users/t_users.enc"))
    {
        tuser.open("./users/t_users.enc",ios::in);
        tu=1;
    }
    if(fs::exists("./pass/t_passwords.enc"))
    {
        tpass.open("./pass/t_passwords.enc",ios::in);
        tp=1;
    }
    if(su==1)
    {
        string cell;
        int i=0;
        while(getline(suser, cell))
        {
            if(i==file_length)
                break;
            s[i].setId(cell);
            i++;
        }
        suser.close();
    }
    if(sp==1)
    {
        string cell;
        int i=0;
        while(getline(spass, cell))
        {
            if(i==file_length)
                break;
            s[i].setPass(cell);
            i++;
        }
        spass.close();
    }
    if(tu==1)
    {
        string cell;
        int i=0;
        while(getline(tuser, cell))
        {
            if(i==t_length)
                break;
            t[i].setId(cell);
            i++;
        }
        tuser.close();
    }
    if(tp==1)
    {
        string cell;
        int i=0;
        while(getline(tpass, cell))
        {
            if(i==t_length)
                break;
            t[i].setPass(cell);
            i++;
        }
        tpass.close();
    }
}
//question bank prepration
void COM_ST::QuestionBankPrep()
{
    fstream file("./qdata/"+t[p_index].getCourse()+".txt",ios::in | ios::out);
    if(!file)
        cout<<"Error in reading file "<<endl;
    string line;
    int topic,qtype,noq;
    cout<<"Topics: "<<endl;
    int i=0;
    while(getline(file, line))
    {
        if(line=="a5380ee")
        {
            getline(file, line);
            cout<<++i<<". "<<line<<endl;
        }
    }
    cout<<"4. Random quiz"<<endl;
    cout<<"5. Go back"<<endl;
    file.close();
    int choice;
    cout<<"Enter choice: "<<endl;
    cin>>choice;
    if(choice>5 || choice<=0)
    {
        cout<<"invalid choice"<<endl;
        LoginMenu(2);
    }
    if(choice==5)
        LoginMenu(2);
    ofstream quiz("./Quiz/"+t[p_index].getCourse()+"/"+t[p_index].getCourse()+".txt");
    string quizz="";
    if(choice==4)
    {
        srand(time(0));
        topic=(rand()%2)+1;
        quizz+=to_string(topic)+"\n";
        srand(time(0));
        qtype=(rand()%2)+1;
        quizz+=to_string(qtype)+"\n";
        srand(time(0));
        noq=(rand()%1)+1;
        quizz+=to_string(noq)+"\n";
    }
    else
    {
        topic=choice;
        quizz+=to_string(choice)+"\n";
        cout<<"1. MCQ"<<endl;
        cout<<"2. True/false"<<endl;
        cout<<"3. Subjective question"<<endl;
        cout<<"4. Go back"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        if(choice>=5 || choice<=0)
        {
            cout<<"invalid choice"<<endl;
            LoginMenu(2);
        }
        if(choice==4)
            LoginMenu(2);
        quizz+=to_string(choice)+"\n";
        qtype=choice;
        while(1)
        {
            cout<<"Enter no of questions: ";
            cin>>choice;
            if(choice<=0)
            {
                cout<<"invalid no of questions"<<endl;
            }
            else
                break;
        }
        quizz+=to_string(choice)+"\n";
        noq=choice;
    }
    while(1)
    {
        cout<<"Enter marks for each question: ";
        cin>>choice;
        if(choice<=0)
        {
            cout<<"invalid no of questions"<<endl;
        }
        else
            break;
    }
    quizz+=to_string(choice);
    int shrs,smin,ehrs,emin,day,mon,year;
    //time input
    cout<<"Enter year to start: ";
    cin>>year;
    while(year<getyear())
    {
        cout<<"Invalid year"<<endl;
        cout<<"Enter year to start: ";
        cin>>year;
    }
    while(1)
    {
        cout<<"Enter month to start: ";
        cin>>mon;
        if(year==getyear())
        {
            if(mon<getmon())
                cout<<"Invalid month"<<endl;
            else if(mon<=0 || mon>12)
                cout<<"invalid month"<<endl;
            else
                break;
        }
        else if(mon<=0 || mon>12)
        {
                cout<<"invalid month"<<endl;
        }
        else
            break;
        
    }
    while(1)
    {
        cout<<"Enter day to start: ";
        cin>>day;
        if(year==getyear() && mon==getmon())
        {
            if(day<getdate())
                cout<<"Invalid day"<<endl;
            else if(day<=0 || day>31)
                cout<<"Invalid day"<<endl;
            else 
                break;
        }
        else if(day<=0 || day>31)
        {
            cout<<"Invalid day"<<endl;
        }
        else 
            break;
    }
    while(1)
    {
        cout<<"Current Time int 24-hour format: "<<"("<<gethrs()<<":"<<getmins()<<")"<<endl;
        cout<<"Enter time (hours only) in 24-hours format to start: ";
        cin>>shrs;
        if(year==getyear() && day==getdate() && mon==getmon())
        {
            if(shrs<gethrs())
                cout<<"invalid start hours"<<endl;
            else if(shrs<0 || shrs>=24)
                cout<<"invalid start hours"<<endl;
            else 
                break;
        }
        else if(shrs<0 || shrs>=24)
        {
            cout<<"invalid start hours"<<endl;
        }
        else
            break;
    }
    while(1)
    {
        cout<<"Enter min to start: ";
        cin>>smin;
        if(year==getyear() && day==getdate() && mon==getmon() && gethrs()==shrs)
        {
            if(smin<getmins())
                cout<<"invalid start min"<<endl;
            else if(smin<0 || smin>=60)
                cout<<"invalid start min"<<endl;
            else 
            break;
        }
        else if(smin<0 || smin>=60)
        {
            cout<<"invalid start min"<<endl;
        }
        else
            break;
    }
    while(1)
    {
        cout<<"Enter time (hours) to end: ";
        cin>>ehrs;
        if(year==getyear() && day==getdate() && mon==getmon())
        {
            if(ehrs<gethrs())
                cout<<"invalid end hours"<<endl;
            else if(ehrs<0 || ehrs>=24)
                cout<<"invalid end hours"<<endl;
            else 
                break;
        }
        else if(ehrs<0 || ehrs>=24)
        {
            cout<<"invalid end hours"<<endl;
        }
        else
            break;
    }
    while(1)
    {
        cout<<"Enter min to end: ";
        cin>>emin;
        if(year==getyear() && day==getdate() && mon==getmon() && gethrs()==ehrs)
        {
            if(emin<=getmins())
                cout<<"invalid end min"<<endl;
            else if(emin<0 || emin>=60)
                cout<<"invalid end min"<<endl;
            else 
            break;
        }
        else if(emin<0 || emin>=60)
        {
            cout<<"invalid end min"<<endl;
        }
        else
            break;
    }
    //data reading from file
    quiz<<shrs<<endl;
    quiz<<smin<<endl;
    quiz<<ehrs<<endl;
    quiz<<emin<<endl;
    quiz<<day<<endl;
    quiz<<mon<<endl;
    quiz<<year<<endl;
    quiz<<quizz;
    quiz.close();
    create_files(day,shrs,smin,t[p_index].getCourse(),year,mon);
    ofstream kfile("./Quiz/"+t[p_index].getCourse()+"/"+t[p_index].getCourse()+"_"+to_string(year)+"_"+to_string(mon)+"_"+to_string(day)+"_"+to_string(shrs)+"_"+to_string(smin)+".key");
    if(!kfile)
        cout<<"unable to open key file!"<<endl;
    int m=0;
    string line1;
    //key generation
    if(qtype!=3)
    {
        file.open("./qdata/"+t[p_index].getCourse()+".txt");
        string tag="2efcde9";
        if(qtype==2)
                tag="b94d27b";
        while(getline(file, line))
        {
            if(line1=="a5380ee")
                break;
            if(line=="a5380ee")
                m++;
            if(line=="a5380ee" && m==topic)
            {
                getline(file, line);
                int mno=0;
                int j=0,flag=0;
                while(getline(file, line1))
                {
                    if(line1=="a5380ee")
                        break;
                    else if(line1==tag)
                    {
                        mno++;
                        if(mno>noq)
                            break;
                        flag=1;
                        for(int i=0;i<5;i++)
                        {
                            getline(file, line1);
                            if(check_marker(line1,"dabfac4"))
                            {  
                                kfile<<getAnswer(line1)<<endl;
                            }
                        }
                    }
                }
            }
        }
    }
    if(qtype==3)
        kfile<<"Subjective Question (NO KEY)";
    cout<<"Quiz generated!"<<endl;
    kfile.close();
    file.close();
    LoginMenu(2);
}
//to check markers in quiz file
int COM_ST::check_marker(string s, string m)
{
    for(int i=0;i<strlen(s);i++)
    {
        if(s[i]==' ' && s[i-1]=='n' && s[i+1]=='d')
            return i;
    }
    return 0;
}
//to remove markers in quiz file
string COM_ST::remove_marker(string s,string m)
{
    string temp="";
    for(int i=0;i<strlen(s);i++)
    {
        if(s[i]==' ' && s[i-1]=='n' && s[i+1]=='d')
            i+=7;
        else
        temp+=s[i];
    }
    return temp;
}
//quiz conduction
void COM_ST::Quiz_Cond()
{
    if(fs::exists("./Quiz/Programming Fundamentals/Programming Fundamentals.txt") && check_quiz("Programming Fundamentals"))
    {
        if(s[p_index].getPF()==1)
        {
            cout<<"1.PF"<<endl;
        }
    }
    if(fs::exists("./Quiz/Introduction To Computing/Introduction To Computing.txt") && check_quiz("Introduction To Computing"))
    {
        if(s[p_index].getITC()==1)
        {
            cout<<"2.Introduction To Computing"<<endl;
        }
    }
    if(fs::exists("./Quiz/Data Structures/Data Structures.txt") && check_quiz("Data Structures"))
    {
        if(s[p_index].getDS()==1)
        {
            cout<<"3.DS"<<endl;
        }
    }
     if(fs::exists("./Quiz/Object Oriented Programming/Object Oriented Programming.txt") && check_quiz("Object Oriented Programming"))
    {
        if(s[p_index].getOOP()==1)
        {
            cout<<"4.Object Oriented Programming"<<endl;
        }
    }
    if(fs::exists("./Quiz/Analysis of Algorithms/Analysis of Algorithms.txt") && check_quiz("Analysis of Algorithms"))
    {
        if(s[p_index].getAA()==1)
        {
            cout<<"5.Analysis of Algorithms"<<endl;
        }
    }
    if(fs::exists("./Quiz/Software Requirements Engineering/Software Requirements Engineering.txt") && check_quiz("Software Requirements Engineering"))
    {
        if(s[p_index].getSR()==1)
        {
            cout<<"6.Software Requirements Engineering"<<endl;
        }
    }
    if(fs::exists("./Quiz/Research Methodology/Research Methodology.txt") && check_quiz("Research Methodology"))
    {
        if(s[p_index].getRM()==1)
        {
            cout<<"7.Research Methodology"<<endl;
        }
    }
    if(fs::exists("./Quiz/Big Data Analytics/Big Data Analytics.txt") && check_quiz("Big Data Analytics"))
    {
        if(s[p_index].getBDA()==1)
        {
            cout<<"8.Big Data Analytics"<<endl;
        }
    }
    if(fs::exists("./Quiz/Artificial Intelligence/Artificial Intelligence.txt") && check_quiz("Artificial Intelligence"))
    {
        if(s[p_index].getAI()==1)
        {
            cout<<"9.Artificial Intelligence"<<endl;
        }
    }
    if(fs::exists("./Quiz/Deep Learning/Deep Learning.txt") && check_quiz("Deep Learning"))
    {
        if(s[p_index].getDL()==1)
        {
            cout<<"10.Deep Learning"<<endl;
        }
    }
    if(fs::exists("./Quiz/Digital Image Processing/Digital Image Processing.txt") && check_quiz("Digital Image Processing"))
    {
        if(s[p_index].getDIP()==1)
        {
            cout<<"11.Digital Image Processing"<<endl;
        }
    }
    int choice;
    cout<<"\nEnter your choice (if no quiz is shown above enter 0): ";
    cin>>choice;
    if(choice>11 || choice<0)
    {
        cout<<"invalid choice"<<endl;
        LoginMenu(1);   
    }
    string course;
    if(choice==1)
        course="Programming Fundamentals";
    if(choice==2)
        course="Introduction To Computing";
    if(choice==3)
        course="Data Structures";
    if(choice==4)
        course="Object Oriented Programming";
    if(choice==5)
        course="Analysis of Algorithms";
    if(choice==6)
        course="Software Requirements Engineering";
    if(choice==7)
        course="Research Methodology";
    if(choice==8)
        course="Big Data Analytics";
    if(choice==9)
        course="Artificial Intelligence";
    if(choice==10)
        course="Deep Learning";
    if(choice==11)
        course="Digital Image Processing";
    else if(choice==0)
        LoginMenu(1);

    if(check_quiz(course))
    {
        //quiz data reading from file
        int topic,qn,sh,sm,eh,em,noq;
        float marks,result=0;
        fstream file;
        file.open("./Quiz/"+course+"/"+course+".txt",ios::in | ios::out);
        int i=0;
        string line;
        getline(file,line);
        sh = stoi(line);
        getline(file,line);
        sm = stoi(line);
        getline(file,line);
        eh = stoi(line);
        getline(file,line);
        em = stoi(line);
        getline(file,line);
        getline(file,line);
        getline(file,line);
        getline(file,line);
        topic = stoi(line);
        getline(file,line);
        qn = stoi(line);
        getline(file,line);
        noq = stoi(line);
        getline(file,line);
        marks = stof(line);
        file.close();
        int stic=0;
        //course selection
        for(int i=0;i<216;i++)
        {
            if(course=="Object Oriented Programming")
            {
                if(s[i].getOOP()==1)
                    stic++;
            }
            if(course=="Programming Fundamentals")
            {
                if(s[i].getPF()==1)
                    stic++;
            }
            if(course=="Introduction To Computing")
            {
                if(s[i].getITC()==1)
                    stic++;
            }
            if(course=="Data Structures")
            {
                if(s[i].getDS()==1)
                    stic++;
            }
            if(course=="Analysis of Algorithms")
            {
                if(s[i].getAA()==1)
                    stic++;
            }
            if(course=="Software Requirements Engineering")
            {
                if(s[i].getSR()==1)
                    stic++;
            }
            if(course=="Research Methodology")
            {
                if(s[i].getRM()==1)
                    stic++;
            }
            if(course=="Big Data Analytics")
            {
                if(s[i].getBDA()==1)
                    stic++;
            }
            if(course=="Artificial Intelligence")
            {
                if(s[i].getAI()==1)
                    stic++;
            }
            if(course=="Deep Learning")
            {
                if(s[i].getDL()==1)
                    stic++;
            }
            if(course=="Digital Image Processing")
            {
                if(s[i].getOOP()==1)
                    stic++;
            }
        }
        //if already given the quiz
        if(fs::exists("./Quiz/"+course+"/"+course+"_"+to_string(getyear())+"_"+to_string(getmon())+"_"+to_string(getdate())+"_"+to_string(sh)+"_"+to_string(sm)+".atd"))
        {
            ifstream file1("./Quiz/"+course+"/"+course+"_"+to_string(getyear())+"_"+to_string(getmon())+"_"+to_string(getdate())+"_"+to_string(sh)+"_"+to_string(sm)+".atd");
            string line;
            while(getline(file1,line))
            {
                if(line==s[p_index].getName())
                {
                    cout<<"You have already given this quiz!"<<endl;
                    LoginMenu(1);
                }
            }
            file1.close();
        }
        file.open("./qdata/"+course+".txt",ios::in | ios::out);
        string line1;
        //quiz conduction according to questions
        while(getline(file, line))
        {
            if(line1=="a5380ee")
                break;
            if(line=="a5380ee")
                i++;
            if(line=="a5380ee" && i==topic)
            {
                getline(file, line);
                cout<<"\t\t"<<line<<endl;
                if(qn==1)
                {
                    Quiz q(1);
                    q.setT(sh,sm,eh,em,getdate(),getmon(),getyear());
                    int mno=0;
                    int j=0,flag=0;
                    while(getline(file, line1))
                    {   
                        if(line1=="a5380ee")
                        {
                            if(flag==0)
                            {
                                cout<<"MCQ's not found in this topic"<<endl;
                                LoginMenu(1);
                            }
                            break;
                        }
                        else if(line1=="2efcde9")
                        {
                            mno++;
                            if(mno>noq)
                                break;
                            flag=1;
                            string temp="",temp2="";
                            for(int i=0;i<5;i++)
                            {
                                getline(file, line1);
                                if(check_marker(line1,"dabfac4"))
                                {
                                    
                                    line1=remove_marker(line1,"dabfac4");
                                    q.getMCQ()->setAnswer(i);
                                }
                                temp+=line1+"\n";
                                if(i==4)
                                {
                                    q.getMCQ()->setData(temp);
                                    q.getMCQ()->shuffle(s[p_index].getPass());
                                }
                            }
                            q.getMCQ()->display();
                            int choice2;
                            while(1)
                            {
                                cout<<"Enter your answer: ";
                                cin>>choice2;
                                if(choice2<=0 || choice2>4)
                                {
                                    cout<<"Invalid answer!"<<endl;
                                }
                                else
                                    break;
                            }
                            if(gethrs()>=q.geteHour() && getmins()>=q.geteMin())
                                cout<<"Time ended!"<<endl;
                            else if(choice2==q.getMCQ()->getAnswer())
                            {
                                ifstream anlts1;
                                ofstream anlts2;
                                if(fs::exists("./Quiz/"+course+"/"+"anlytcs/"+course+"_"+to_string(getyear())+"_"+to_string(getmon())+"_"+to_string(getdate())+"_"+to_string(sh)+"_"+to_string(sm)+".aly"))
                                {
                                    anlts1.open("./Quiz/"+course+"/"+"anlytcs/"+course+"_"+to_string(getyear())+"_"+to_string(getmon())+"_"+to_string(getdate())+"_"+to_string(sh)+"_"+to_string(sm)+".aly");
                                    string templ;
                                    getline(anlts1,templ);
                                    getline(anlts1,templ);
                                    getline(anlts1,templ);
                                    anlts1.close();
                                    anlts2.open("./Quiz/"+course+"/"+"anlytcs/"+course+"_"+to_string(getyear())+"_"+to_string(getmon())+"_"+to_string(getdate())+"_"+to_string(sh)+"_"+to_string(sm)+".aly");
                                    int n=(stoi(templ));
                                    anlts2<<"216"<<endl;
                                    anlts2<<stic<<endl;
                                    anlts2<<n+1;
                                    anlts2.close();
                                }
                                else
                                {
                                    anlts2.open("./Quiz/"+course+"/"+"anlytcs/"+course+"_"+to_string(getyear())+"_"+to_string(getmon())+"_"+to_string(getdate())+"_"+to_string(sh)+"_"+to_string(sm)+".aly");
                                    anlts2<<"216"<<endl;
                                    anlts2<<stic<<endl;
                                    anlts2<<"1";
                                    anlts2.close();
                                }
                                cout<<"Correct answer"<<endl;
                                result+=marks;
                            }
                            else
                                cout<<"Wrong"<<endl;
                        }
                    }
                }
                else if(qn==2)
                {
                    Quiz q(2);
                    q.setT(sh,sm,eh,em,getdate(),getmon(),getyear());
                    int mno=0;
                    int j=0,flag=0;
                    while(getline(file, line1))
                    {   
                        if(line1=="a5380ee")
                        {
                            if(flag==0)
                            {
                                cout<<"True false not found in this topic"<<endl;
                                LoginMenu(1);
                            }
                            break;
                        }
                        else if(line1=="b94d27b")
                        {
                            mno++;
                            if(mno>noq)
                                break;
                            flag=1;
                            string temp="",temp2="";
                            for(int i=0;i<3;i++)
                            {
                                getline(file, line1);
                                if(check_marker(line1,"dabfac4"))
                                {
                                    line1=remove_marker(line1,"dabfac4");
                                    q.getTF()->setAnswer(i);
                                }
                                temp+=line1+"\n";
                                if(i==2)
                                {
                                    q.getTF()->setData(temp);
                                    q.getTF()->shuffle(s[p_index].getPass());
                                }
                            }
                            q.getTF()->display();
                            int choice2,hrs,day,min;
                            while(1)
                            {
                                cout<<"Enter your answer: ";
                                cin>>choice2;
                                if(choice2<=0 || choice2>2)
                                {
                                    cout<<"invalid answer"<<endl;
                                }
                                else
                                    break;
                            }
                            if(gethrs()>=eh && getmins()>=em)
                                cout<<"Time ended!"<<endl;
                            else if(choice2==q.getTF()->getAnswer())
                            {
                                ifstream anlts1;
                                ofstream anlts2;
                                if(fs::exists("./Quiz/"+course+"/"+"anlytcs/"+course+"_"+to_string(getyear())+"_"+to_string(getmon())+"_"+to_string(getdate())+"_"+to_string(sh)+"_"+to_string(sm)+".aly"))
                                {
                                    anlts1.open("./Quiz/"+course+"/"+"anlytcs/"+course+"_"+to_string(getyear())+"_"+to_string(getmon())+"_"+to_string(getdate())+"_"+to_string(sh)+"_"+to_string(sm)+".aly");
                                    string templ;
                                    getline(anlts1,templ);
                                    getline(anlts1,templ);
                                    getline(anlts1,templ);
                                    anlts1.close();
                                    anlts2.open("./Quiz/"+course+"/"+"anlytcs/"+course+"_"+to_string(getyear())+"_"+to_string(getmon())+"_"+to_string(getdate())+"_"+to_string(sh)+"_"+to_string(sm)+".aly");
                                    int n=(stoi(templ));
                                    anlts2<<"216"<<endl;
                                    anlts2<<stic<<endl;
                                    anlts2<<n+1;
                                    anlts2.close();
                                }
                                else
                                {
                                    anlts2.open("./Quiz/"+course+"/"+"anlytcs/"+course+"_"+to_string(getyear())+"_"+to_string(getmon())+"_"+to_string(getdate())+"_"+to_string(sh)+"_"+to_string(sm)+".aly");
                                    anlts2<<"216"<<endl;
                                    anlts2<<stic<<endl;
                                    anlts2<<"1";
                                    anlts2.close();
                                }
                                cout<<"Correct answer"<<endl;
                                result+=marks;
                            }
                            else
                                cout<<"Wrong"<<endl;
                        }
                    }
                }
                else if(qn==3)
                {
                    Quiz q(3);
                    q.setT(sh,sm,eh,em,getdate(),getmon(),getyear());
                    int mno=0;
                    int j=0,flag=0;
                    while(getline(file, line1))
                    {   
                        if(line1=="a5380ee")
                        {
                            if(flag==0)
                            {
                                cout<<"Discriptive question not found in this topic"<<endl;
                                LoginMenu(1);
                            }
                            break;
                        }
                        else if(line1=="88f7ace")
                        {
                            mno++;
                            if(mno>noq)
                                break;
                            flag=1;
                            getline(file, line1);
                            cout<<line1<<endl;
                            q.getSUB()->setData(line1);
                            q.getSUB()->setAnswer(0.01);
                            string ans;
                            cout<<"Enter answer: ";
                            cin.ignore();
                            getline(cin,ans);
                            for(int i=0;i<strlen(ans);i++)
                            {
                                if(ans[i]==' ')
                                    result+=0.01;
                            }
                            if(result>marks)
                                result=marks;
                            ifstream anlts1;
                            ofstream anlts2;
                            if(fs::exists("./Quiz/"+course+"/"+"anlytcs/"+course+"_"+to_string(getyear())+"_"+to_string(getmon())+"_"+to_string(getdate())+"_"+to_string(sh)+"_"+to_string(sm)+".aly"))
                            {
                                anlts1.open("./Quiz/"+course+"/"+"anlytcs/"+course+"_"+to_string(getyear())+"_"+to_string(getmon())+"_"+to_string(getdate())+"_"+to_string(sh)+"_"+to_string(sm)+".aly");
                                string templ,tempq;
                                getline(anlts1,templ);
                                getline(anlts1,tempq);
                                anlts1.close();
                                anlts2.open("./Quiz/"+course+"/"+"anlytcs/"+course+"_"+to_string(getyear())+"_"+to_string(getmon())+"_"+to_string(getdate())+"_"+to_string(sh)+"_"+to_string(sm)+".aly");
                                float n=(stof(templ));
                                anlts2<<n+result;
                                anlts2<<to_string(stof(tempq)+marks)<<endl;
                                anlts2.close();
                            }
                            else
                            {
                                anlts2.open("./Quiz/"+course+"/"+"anlytcs/"+course+"_"+to_string(getyear())+"_"+to_string(getmon())+"_"+to_string(getdate())+"_"+to_string(sh)+"_"+to_string(sm)+".aly");
                                anlts2<<to_string(result)<<endl;
                                anlts2<<marks;
                                anlts2.close();
                            }
                        }
                    }
                }
            }
        }
        // file2<<course<<"_"<<year<<"_"<<mon<<"_"<<day<<"_"<<hrs<<"_"<<min<<".atd"<<endl;
        ofstream att("./Quiz/"+course+"/"+course+"_"+to_string(getyear())+"_"+to_string(getmon())+"_"+to_string(getdate())+"_"+to_string(sh)+"_"+to_string(sm)+".atd");
        ofstream res("./Quiz/"+course+"/"+course+"_"+to_string(getyear())+"_"+to_string(getmon())+"_"+to_string(getdate())+"_"+to_string(sh)+"_"+to_string(sm)+".result");
        att<<s[p_index].getName()<<endl;
        res<<s[p_index].getName()<<" "<<result<<"\\"<<noq*marks<<endl;
        att.close();
        res.close();
        file.close();
    }
    LoginMenu(1);
}
//check contraints on quiz
bool COM_ST::check_quiz(string name)
{
    fstream file("./Quiz/"+name+"/"+name+".txt",ios::in | ios::out);
    string line;
    int sh,sm,ehrs,emin,day,mon,year;
    getline(file, line);
    sh = stoi(line);
    getline(file, line);
    sm = stoi(line);
    getline(file, line);
    ehrs = stoi(line);
    getline(file, line);
    emin=stoi(line);
    getline(file, line);
    day = stoi(line);
    getline(file, line);
    mon = stoi(line);
    getline(file, line);
    year = stoi(line);
    if(getyear()<year || getyear()>year)
            return 0;
    if(year==getyear() && (mon<getmon() || mon>getmon()))
            return 0;
    if(year==getyear() && mon==getmon() && (getdate()<day || getdate()>day))
            return 0;
    if(year==getyear() && mon==getmon() && getdate()==day)
    {
        if(gethrs()<sh)
        {
        
            return 0;
        }
        if(gethrs()==sh)
        {
            if(getmins()<sm)
            {
                return 0;
            }
        }
        if(ehrs==gethrs())
        {
            if(emin<=getmins())
            {
                return 0;
            }
        }
        if(ehrs<gethrs())
        {
            return 0;   
        }
    }
    return 1;
}
//return current hours
int COM_ST::gethrs()
{
    time_t now=time(0);
    tm *ltm=localtime(&now);
    return ltm->tm_hour;
}
//return current mins
int COM_ST::getmins()
{
    time_t now=time(0);
    tm *ltm=localtime(&now);
    return ltm->tm_min;
}
//return current day
int COM_ST::getdate()
{
    time_t now=time(0);
    tm *ltm=localtime(&now);
    return ltm->tm_mday;
}
//return current month
int COM_ST::getmon()
{
    time_t now=time(0);
    tm *ltm=localtime(&now);
    return (ltm->tm_mon)+1;
}
//return current year
int COM_ST::getyear()
{
    time_t now=time(0);
    tm *ltm=localtime(&now);
    return (ltm->tm_year+1900);
}
//get answer from marker
string COM_ST::getAnswer(string s)
{
    string temp="";
    for(int i=0;i<strlen(s);i++)
    {
        if(s[i]==':')
        {
            for(int j=i+2;j<strlen(s);j++)
            {
                temp+=s[j];
            }
        }
    }
    return temp;
}
//create important analytics files
void COM_ST::create_files(int day,int hrs,int min,string course,int year,int mon)
{
    ofstream file1,file2,file3,file4;
    if(fs::exists("./Quiz/"+course+"/kname.txt"))
        file1.open("./Quiz/"+course+"/kname.txt",ios::app);
    else
        file1.open("./Quiz/"+course+"/kname.txt");
    if(fs::exists("./Quiz/"+course+"/aname.txt"))
        file2.open("./Quiz/"+course+"/aname.txt",ios::app);
    else
        file2.open("./Quiz/"+course+"/aname.txt");
    if(fs::exists("./Quiz/"+course+"/rname.txt"))
        file3.open("./Quiz/"+course+"/rname.txt",ios::app);
    else
        file3.open("./Quiz/"+course+"/rname.txt");
    if(fs::exists("./Quiz/"+course+"/alname.txt"))
        file4.open("./Quiz/"+course+"/alname.txt",ios::app);
    else
        file4.open("./Quiz/"+course+"/alname.txt");
    
    file1<<course<<"_"<<year<<"_"<<mon<<"_"<<day<<"_"<<hrs<<"_"<<min<<".key"<<endl;
    file2<<course<<"_"<<year<<"_"<<mon<<"_"<<day<<"_"<<hrs<<"_"<<min<<".atd"<<endl;
    file3<<course<<"_"<<year<<"_"<<mon<<"_"<<day<<"_"<<hrs<<"_"<<min<<".result"<<endl;
    file4<<course<<"_"<<year<<"_"<<mon<<"_"<<day<<"_"<<hrs<<"_"<<min<<".aly"<<endl;
    file1.close();
    file2.close();
    file3.close();
    file4.close();
}