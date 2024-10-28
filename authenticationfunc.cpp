#include <iostream>
#include <cctype>//contains definitions for C++ for classifying characters
#include <fstream>
#include<iomanip>
#include <string>
#include <conio.h>//getch
#include <thread>
#include <vector>
#include <windows.h>
#include <stdio.h>
#include <regex>//uesd for pattern
#include "patientfunctionheader.h"
#include "colorheader.h"

using namespace std;
HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
/**ADDITIONAL FUNCTIONS**/
const int numberofstruct=1000;

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

vector<patientdetails>patient;
vector<docdetails>doctor;

unsigned int Hashingfunc(const string &paswd){
    unsigned  int num2=4123;
    unsigned int paswdhash=1;
    for(int i=0;i<paswd.length();i++){
        paswdhash=paswdhash*(paswd[i]);
        paswdhash=paswdhash-num2;
        }
        return paswdhash;
}

string validatePhoneNumber(const string& phoneNumber) {
    regex pattern("\\d{3}\\d{3}\\d{4}");//[/d]matchs the digits from(0-9) &{3}-check how times a digit should occur
    if(std::regex_match(phoneNumber, pattern)){//return a boolean values(regex_match) function
        return phoneNumber;
    }
    else{
       string state="false";
        return state;
    }


}

string validateEmail(const string& email) {
    regex pattern("[a-zA-Z0-9._]+@[a-zA-Z0-9.]+\\.[a-zA-Z]{2,}");//[/d]matchs the digits from(0-9) &{3}-check how times a digit should occur
    if(regex_match(email, pattern)){//return a boolean values(regex_match) function
        return email;
    }
    else{
       string state="false";
        return state;
    }


}

string removespace(string name) {
    string result;

    for (char c : name) {
        if (!isspace(c)) {
            result += c;
        }
        else{
            result += '*';
        }
    }

    return result;
}

int filerowread(int authnum){
    if(authnum==1){
             ifstream inputFile("Doctorlogin_details");
            if (!inputFile.is_open()) {
                cerr << "Unable to open the file." << endl;
                return 1;
            }
            int rowCount = 0;
            string row;
            while (getline(inputFile, row)) {
                rowCount++;
            }
             return rowCount;
            inputFile.close();
    }
    else if(authnum==2){
             ifstream inputFile("patientlogin_details");
            if (!inputFile.is_open()) {
                cerr << "Unable to open the file." << endl;
                return 1;
            }
            int rowCount = 0;
            string row;
            while (getline(inputFile, row)) {
                rowCount++;
            }
            inputFile.close();
             return rowCount;

    }
}


int firstpage(){
    system("COLOR F");
    system("cls");
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int bar1=177,bar2=219;

cout<<"\n\n\n\n\n\n\n\n";
cout << "\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<< endl;
cout << "\t\t\t\t**                                                                                       **" << endl;
cout << "\t\t\t\t**                                                                                       **" << endl;
cout << "\t\t\t\t**                                                                                       **" << endl;
cout<<RED<<"\t\t\t\t**                      WELCOME TO Clinic MANAGEMENT SYSTEM                              **" <<RESET<< endl;
cout << "\t\t\t\t**                                                                                       **" << endl;
cout << "\t\t\t\t**                                                                                       **" << endl;
cout << "\t\t\t\t**                                                                                       **" << endl;
cout << "\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" <<endl;

           cout<<"\n\t\t\t\t"<<(char)1<<"!";
            system("Pause");
            cout<<"\n\n";
            for(int i=0;i<50;i++){
                cout<<WHITE<<(char)bar1<<RESET;
            }
            //cout<<"\n\t\t\t\t\tloading.......";
            cout<<"\r";
            cout<<"\t\t\t\t\t\t";
            for(int i=0;i<50;i++){
                cout<<GREEN<<(char)bar2<<RESET;
                Sleep(150);
            }
        return 1;
}


/**SIGNUP FUNCTION**/

void filehadling_sgnup(int auth_num,const vector<patientdetails>& patient,const vector<docdetails>& doctor){

        if(auth_num==1){
            ofstream writefile;
            writefile.open("Doctorlogin_details",ios::app);

            if(writefile.is_open()){

                    for(const docdetails& d:doctor){
                          writefile<<left<<d.username<<" "<<d.mobile<<" "<<d.gender<<" "<<d.email<<endl;
                    }
                    writefile.close();

                    cout<<YELLOW<<"\n\n\t\t\t\t* * * * * * * * * * * * * * * * "<<RESET<<MAGENTA<<"Doctor Data is updated to the system successful"<<RESET<<YELLOW<<" * * * * * * * * * * * * * * * *"<<RESET<<endl;


        }

   }
       else if(auth_num==2){
            ofstream writefile;
            writefile.open("patientlogin_details",ios::app);

            if(writefile.is_open()){
                    patientdetails p;
                    for(const patientdetails& p:patient){
                          writefile<<left<<p.username<<" "<<p.mobile<<" "<<p.email<<endl;
                    }
                    writefile.close();
                   cout<<YELLOW<<"\n\n\t\t\t\t* * * * * * * * * * * * * * * * "<<RESET<<MAGENTA<<"Patient Data is updated to the system successful"<<RESET<<YELLOW<<" * * * * * * * * * * * * * * * *"<<RESET<<endl;

      }

   }
   this_thread::sleep_for(chrono::seconds(2));

}

void filehadling_sgnupsecured(int auth_num,const vector<patientdetails>& patient,const vector<docdetails>& doctor){

            if(auth_num== 1){
                ofstream write;
                ofstream writefile;
                writefile.open("SecureDocInfo_details",ios::app);
                write.open("Doctorlist.txt",ios::app);

                if(writefile.is_open() && write.is_open()){
                        for(const docdetails& d:doctor){
                            writefile<<left<<d.username<<"  "<<d.userpswd<<endl;
                            write<<left<<d.username<<endl;
                }
                  writefile.close();
                      }
                else{

                    cout<<RED<<"\n\n\t\t\t\t* * * * * * * * * * * * * * * * * * * * * "<<RESET<<MAGENTA<<"Unable to open the file"<<RESET<<RED<<" * * * * * * * * * * * * * * * * * * * *"<<RESET<<endl;
                }



            }
            else if(auth_num==2){
                ofstream writefile;
                writefile.open("SecurePatientInfo_details",ios::app);

                if(writefile.is_open()){
                        for(const patientdetails& p:patient){
                              writefile<<left<<p.username<<"  "<<p.userpswd<<endl;
                        }
                        writefile.close();
                    }
                    else{
                    cout<<RED<<"\n\n\t\t\t\t* * * * * * * * * * * * * * * * * * * * * "<<RESET<<MAGENTA<<"Unable to open the file"<<RESET<<RED<<" * * * * * * * * * * * * * * * * * * * *"<<RESET<<endl;

                    }




            }




}

int Validationusername(int authnum,string usname){
    ifstream read;
    if(authnum==1){
        read.open("SecureDocInfo_details");
        if (read.is_open()) {

        string storedusername;

        while(read>>storedusername){
            if(storedusername==usname){
                return 0;
                read.close();
            }
        }
          return 1;
          read.close();
       }

    }
    else if(authnum==2)
    {
        read.open("SecurePatientInfo_details");
        if (read.is_open()) {

        string storedusername;
        read.seekg(0,ios::beg);
        while(read>>storedusername){
            if(storedusername==usname){
                return 0;
                read.close();
            }
        }

          read.close();
          return 1;
       }
    }
    else{
        return authnum;
    }



}


int readingfileforvalid(int authnum,string usnam,string paswd ,string *validuser){
    if(authnum==1){
        ifstream read;
        read.open("SecureDocInfo_details");
         if (read.is_open()) {

        string storedusername,storedpswd="";
        read.seekg(0,ios::beg);
        while(read>>storedusername>>storedpswd){
                //cout<<storedusername<<" "<<storedpswd;
            if(storedusername==usnam && storedpswd==paswd){
                *validuser=usnam;
                return 0;
                read.close();
            }

        }
          return 1;
          read.close();
       }
    }
     else if(authnum==2){
        ifstream read;
        read.open("SecurePatientInfo_details");
         if (read.is_open()) {

        string storedusername,storedpswd;
        read.seekg(0,ios::beg);
        while(read>>storedusername>>storedpswd){
            if(storedusername==usnam && storedpswd==paswd){
                *validuser=usnam;
                return 0;
                read.close();
            }


        }
          return 1;
          read.close();
       }
    }





}

void signuppage(int authnum){///COMPLETED
        char pass,authletter;//(varible[pass]-used to character user enter required to the password star printing)
        int validnum;//[validnum]-used to store number return from function[validationusername]
        patientdetails p[numberofstruct];//varible[p[i]] create with a struct(I represent number of struct allow to create)
            docdetails d[numberofstruct];

        int rowcount=filerowread(authnum);//count number row or number struct  create in the file

        if(authnum==1){///docators singup code
        for(int i=rowcount;i<rowcount+1;i++){
                    cout<<"\n\n\n\n";
                    cout<<YELLOW<< "\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<<RESET;
                    cout<<RED<<"\n\t\t\t\t\t\t\t\tSign_up(As Doctor):XYZ Clinic Centre"<<RESET;
                    cout<<GREEN<<"\n\n\t\t\t\t\t1.Enter the UserName\t:"<<RESET;
                    SetConsoleTextAttribute(h,15);///colorcode
                    cin.ignore();
                    while(getline(cin,d[i].username)){//string function use to get (single word/double word) username
                        d[i].username=removespace(d[i].username);///username stored in variable being transfer to a function [removespace] inorder remove space between word
                        validnum=Validationusername(authnum,d[i].username);///check whether user enter name already registerd
                        if(validnum!=1){
                              cout<<RED<<Bold<< "\n\t\t\t\t---------------------------------------------------------------------------------------------------------------"<<RESET;
                              cout<<MAGENTA<<"\n\t\t\t\t\tUsername is Already exist.Enter a valid Username:"<<RESET;
                              cin.clear();             // Clear the error flag
                              //cin.ignore(INT_MAX, '\n'); ///In this not being used because same thing will be repeated so[if we include this user have enter twice]
                          }
                          else{

                              break;//if condition is true the loop being break
                          }

                    }
                    cout<<GREEN<<"\n\t\t\t\t\t2.Enter the Mobile.No\t:"<<RESET;
                    SetConsoleTextAttribute(h,15);///colorcode
                     while (cin >> d[i].mobile){
                          if("false"==validatePhoneNumber(d[i].mobile)){///check the number in correct format
                                cout<<RED<<Bold<< "\n\t\t\t\t---------------------------------------------------------------------------------------------------------------"<<RESET;
                                cout<<MAGENTA<<"\n\t\t\t\t\tInvalid input.Enter a valid Mobile no(format: XXX/XXX/XXXX):"<<RESET;
                               cin.clear();             // Clear the error flag
                               cin.ignore(INT_MAX, '\n'); // Discard invalid input
                          }else{

                             d[i].mobile=validatePhoneNumber(d[i].mobile);
                             break;
                          }
                        }
                  cout<<GREEN<<"\n\t\t\t\t\t3.Enter the Password\t:"<<RESET;
                  SetConsoleTextAttribute(h,10);///colorcode
                     while (true)
                            {
                                pass =getch();//read password without typing

                                if (pass == 13) // Enter key
                                {
                                    break;
                                }
                                else if (pass == 8) // Backspace key
                                {
                                    if (!d[i].userpswd.empty())
                                    {
                                        cout << "\b \b";// Move the cursor back, output a space, and move the cursor back again
                                        d[i].userpswd.pop_back();
                                    }
                                }
                                else
                                {
                                    cout << '*';
                                    d[i].userpswd.push_back(pass);
                                }
                            }
                            d[i].userpswd=to_string(Hashingfunc(d[i].userpswd));///Hashing the User given password and store to file.
                    cout<<GREEN<<"\n\n\t\t\t\t\t4.Enter the Gender(M/F)\t:"<<RESET;///validation of the value
                    SetConsoleTextAttribute(h,15);///colorcode
                    while (!(cin >>d[i].gender) || !(d[i].gender=='m' || d[i].gender=='M' || d[i].gender=='f' || d[i].gender=='F') ||(isdigit(d[i].gender))){
                                cout<<RED<<Bold<< "\n\t\t\t\t---------------------------------------------------------------------------------------------------------------"<<RESET;
                                 cout<<MAGENTA<<"\n\t\t\t\t\tInvalid input.Enter a valid Input[M/F]:"<<RESET;
                                cin.clear();             // Clear the error flag
                                cin.ignore(INT_MAX, '\n'); // Discard invalid input
                        }

                    cout<<GREEN<<"\n\t\t\t\t\t5.Enter the E-mail)\t:"<<RESET;///validation of the value
                    SetConsoleTextAttribute(h,15);///colorcode
                     while (cin >> d[i].email){
                          if("false"==validateEmail(d[i].email)){///check the Email validation(whether its in right format)
                                cout<<RED<<Bold<< "\n\t\t\t\t---------------------------------------------------------------------------------------------------------------"<<RESET;
                              cout<<MAGENTA<<"\n\t\t\t\t\tInvalid input.Enter a valid E-mail:"<<RESET;

                               cin.clear();             // Clear the error flag
                               cin.ignore(INT_MAX, '\n'); // Discard invalid input
                          }else{
                             d[i].email=validateEmail(d[i].email);
                             break;
                          }
                        }
                    cout<<RED<<Bold<< "\n\t\t\t\t---------------------------------------------------------------------------------------------------------------"<<RESET;

                            doctor.push_back(d[i]);
                            filehadling_sgnup(authnum,patient,doctor);///file handle function to store above data in relevant file
                            filehadling_sgnupsecured(authnum,patient,doctor);///file handle function to store username and password in relevant file
                            //authletter='n';
                            this_thread::sleep_for(std::chrono::seconds(4));
                        cout<<YELLOW<< "\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<<RESET;


          }

       }

     else if(authnum==2){
            for(int i=rowcount;i<rowcount+1;i++){
                     cout<<"\n\n\n\n";
                    cout<<YELLOW<< "\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<<RESET;
                    cout<<RED<<"\n\t\t\t\t\t\t\t\tSign_up(As Patient):XYZ Clinic Centre"<<RESET;
                    cout<<GREEN<<"\n\n\t\t\t\t\t1.Enter the UserName\t:"<<RESET;
                    SetConsoleTextAttribute(h,15);///colorcode
                    cin.ignore();
                    while(getline(cin,p[i].username)){
                        p[i].username=removespace(p[i].username);
                        validnum=Validationusername(authnum,p[i].username);
                        if(validnum!=1){
                              cout<<RED<<Bold<< "\n\t\t\t\t---------------------------------------------------------------------------------------------------------------"<<RESET;

                              cout<<MAGENTA<<"\n\t\t\t\t\tUsername is Already exist.Enter a valid Username:"<<RESET;
                              cin.clear();             // Clear the error flag
                              //cin.ignore(INT_MAX, '\n'); // Discard invalid input
                          }
                          else{
                              break;
                          }

                    }
                    cout<<GREEN<<"\n\t\t\t\t\t2.Enter the Mobile.No\t:"<<RESET;
                    SetConsoleTextAttribute(h,15);///colorcode
                    while (cin >> p[i].mobile){
                          if("false"==validatePhoneNumber(p[i].mobile)){
                                cout<<RED<<Bold<< "\n\t\t\t\t---------------------------------------------------------------------------------------------------------------"<<RESET;

                               cout<<MAGENTA<<"\n\t\t\t\t\tInvalid input.Enter a valid Mobile no(format: XXX/XXX/XXXX):"<<RESET;
                               cin.clear();             // Clear the error flag
                               cin.ignore(INT_MAX, '\n'); // Discard invalid input
                          }else{
                             p[i].mobile=validatePhoneNumber(p[i].mobile);
                             break;
                          }
                        }
                            cout<<GREEN<<"\n\t\t\t\t\t3.Enter a Password\t:"<<RESET;
                            SetConsoleTextAttribute(h,10);///colorcode

                           while (true)
                            {
                                pass =getch();//read password without typing

                                if (pass == 13) // Enter key
                                {
                                    break;
                                }
                                else if (pass == 8) // Backspace key
                                {
                                    if (!p[i].userpswd.empty())
                                    {
                                        cout << "\b \b";// Move the cursor back, output a space, and move the cursor back again
                                        p[i].userpswd.pop_back();
                                    }
                                }
                                else
                                {
                                    cout << '*';
                                    p[i].userpswd.push_back(pass);
                                }
                            }
                            p[i].userpswd=to_string(Hashingfunc(p[i].userpswd));

                    cout<<GREEN<<"\n\n\t\t\t\t\t4.Enter the E-mail\t:"<<RESET;
                    SetConsoleTextAttribute(h,15);///colorcode
                    while (cin >> p[i].email){
                          if("false"==validateEmail(p[i].email)){
                                cout<<RED<<Bold<< "\n\t\t\t\t---------------------------------------------------------------------------------------------------------------"<<RESET;

                               cout<<MAGENTA<<"\n\t\t\t\t\tInvalid input.Enter a valid E-mail:"<<RESET;
                               cin.clear();             // Clear the error flag
                               cin.ignore(INT_MAX, '\n'); // Discard invalid input
                          }else{
                             p[i].email=validateEmail(p[i].email);
                             break;
                          }
                        }
                    cout<<RED<<Bold<< "\n\t\t\t\t---------------------------------------------------------------------------------------------------------------"<<RESET;

                            patient.push_back(p[i]);
                            filehadling_sgnup(authnum,patient,doctor);
                            filehadling_sgnupsecured(authnum,patient,doctor);
                            //authletter='n';
                            this_thread::sleep_for(std::chrono::seconds(3));


                    cout<<YELLOW<< "\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<<RESET;

          }

       }


}

/**SIGNIN FUNCTION**/

void signinpg(int num,int auth_num1,int *outnum,string *username){
    int outsgin;
    char pass;
    string usnam="";
    string paswd="";


    if((num==1 && auth_num1==2) ||( num==1 && auth_num1== 1)){


       cout<<"\n\n\n\n";
        cout<<GREEN<<Bold<< "\n\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET;
        cout<<BrightRed<<"\n\t\t\t\t\t\t\t\t XYZ Clinic Centre-[LOGIN]"<<RESET<<endl;
        cout<<BrightWhite<<"\n\t\t\t\t\t1.Enter the UserName\t:"<<RESET;
         SetConsoleTextAttribute(h,10);///username color change code
        cin.ignore();
        getline(cin,usnam);
        usnam=removespace(usnam);
        cout<<BrightWhite<<"\n\t\t\t\t\t2.Enter the Password\t:"<<RESET;
         SetConsoleTextAttribute(h,10);///password color change
        while (true)
        {
            pass =getch();//read password without typing

            if (pass == 13) // Enter key
            {
                break;
            }
            else if (pass == 8) // Backspace key
            {
                if (!paswd.empty())
                {
                    cout << "\b \b";// Move the cursor back, output a space, and move the cursor back again
                    paswd.pop_back();
                }
            }
            else
            {
                cout << '*';
                paswd.push_back(pass);
            }
        }
        paswd=to_string(Hashingfunc(paswd));///User given password is hashed

        cout<<GREEN<<Bold<< "\n\n\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET;
        cout<<YELLOW<<"\n\t\t\t\t\t\t\t\t\tPlease Wait "<<RESET;

        for(int i=1;i<=6;i++){
            cout<<YELLOW<<" . "<<RESET;
            this_thread::sleep_for(chrono::seconds(1));
          }
        cout<<"\n\t";
            if(auth_num1==1 || auth_num1==2){
                outsgin=readingfileforvalid(auth_num1,usnam,paswd,&usnam);///User given name and password check in the function[readingfileforvalid]
                *outnum=outsgin;//pointer use to return value from the above[550 line]
                *username=usnam;

             }


     }
      else if(num==1 && auth_num1==3){
                *outnum=3;//assign values to terminate loop
	      }
}


///Not relevant
int  athentication_homepg(int num){
      if (num>=1 && num<=2) {
            return num; // Name contains a digit or symbol, invalid
        }
        while(num>=3 || num<=0){
                cout<<"\t=================================================";
            cout<<"\n\tInvalid Operation";

           for(int i=1;i<=6;i++){
                    cout<<"-";
                    this_thread::sleep_for(chrono::seconds(1));
	      }
	        cout<<"\n\t______________________________________________";
            cout<<"\n\tEnter the number Again(1-2)\t:";
            cin>>num;
            //system("cls");
        }


}

int  athentication_num(int num){
      if(isalpha(num)){
            cout<<"\t=================================================";
            cout<<"\n\tInvalid Operation";

           for(int i=1;i<=6;i++){
                    cout<<"-";
                    this_thread::sleep_for(chrono::seconds(1));
	      }
	       cout<<"\n\t______________________________________________";
            cout<<"\n\tEnter the number Again(1-3)\t:";
            cin>>num;

      }
      else if (num>=1 && num<=3) {
            return num; // Name contains a digit or symbol, invalid
        }
     while(num>=4 || num<=0){
                cout<<"\t=================================================";
            cout<<"\n\tInvalid Operation";

           for(int i=1;i<=6;i++){
                    cout<<"-";
                    this_thread::sleep_for(chrono::seconds(1));
	      }
	       cout<<"\n\t______________________________________________";
            cout<<"\n\tEnter the number Again(1-3)\t:";
            cin>>num;
            //system("cls");
        }

}


/**HOMEPAGE FUNCTIONS**/

int homepg(){
    int num=0;
    cout<<"\n\n\n\n";
    cout<<BrightBlue<<Bold<< "\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<<RESET;
    cout<<BrightRed<<"\n\t\t\t\t\t\t\t\t XYZ Clinic Centre"<<RESET<<endl;
    cout<<YELLOW<<"\n\t\t\t\t\t\t\t\t  1.Sign in"<<RESET<<endl;
    cout<<YELLOW<<"\n\t\t\t\t\t\t\t\t  2.Sign up"<<RESET<<endl;
    cout<<BrightBlue<< "\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<<RESET<< endl;
    cout<<BrightWhite<<"\t\t\t\tEnter the Option Number\t: "<<RESET;

    while (!(cin >> num) || !(num>0 && num<=2) ||(isalpha(num)))
        {
             cout<<RED<< "\n\t\t\t\t-------------------------------------------------------------------------------------------"<<RESET;
             cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid Option[1/2]:"<<RESET;
            cin.clear();             // Clear the error flag
            cin.ignore(INT_MAX, '\n'); // Discard invalid input
                }

    return num;
}

int homepg1(){

    int num;
   cout<<"\n\n\n\n";
    cout<<BrightBlue<<Bold<< "\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<<RESET;
    cout<<BrightRed<<"\n\t\t\t\t\t\t\t\t XYZ Clinic Centre"<<RESET<<endl;
    cout<<YELLOW<<"\n\t\t\t\t\t\t\t\t    1.Doctor"<<RESET<<endl;
    cout<<YELLOW<<"\n\t\t\t\t\t\t\t\t    2.Patient"<<RESET<<endl;
    cout<<YELLOW<<"\n\t\t\t\t\t\t\t\t    3.Back To Home"<<RESET<<endl;
    cout<<BrightBlue<< "\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<<RESET<< endl;
    cout<<BrightWhite<<"\t\t\t\tEnter the Option Number\t: "<<RESET;
    while (!(cin >> num) || !(num>0 && num<=3) ||(isalpha(num)))
        {
             cout<<RED<< "\n\t\t\t\t-------------------------------------------------------------------------------------------"<<RESET;
             cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid Option[1/2/3]:"<<RESET;
            cin.clear();             // Clear the error flag
            cin.ignore(INT_MAX, '\n'); // Discard invalid input
                }

    return num;
}




