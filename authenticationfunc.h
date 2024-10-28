#ifndef AUTHENTICATIONFUNC_H_INCLUDED
#define AUTHENTICATIONFUNC_H_INCLUDED
#include <cctype>//contains definitions for C++ for classifying characters
#include <fstream>
#include <string.h>
#include <conio.h>
#include <thread>
#include <vector>
using namespace std;
struct patientdetails{
    string username;
    string userpswd;
    string mobile;
    string email;
};

struct docdetails{
    string username;
    string userpswd;
    string mobile;
    char gender;
    string email;
};

int rowreadfile(const string& filename);

string removespace(string name);
string validatePhoneNumber(const string& phoneNumber);
int firstpage();
string validateEmail(const string& email);
void signinpg(int num,int auth_num1,int *outnum,string *username);
void signuppage(int authnum);
int homepg1();
int homepg();




#endif // AUTHENTICATIONFUNC_H_INCLUDED
