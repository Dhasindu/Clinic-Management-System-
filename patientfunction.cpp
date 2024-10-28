#include <iostream>
#include <cctype>//contains definitions for C++ for classifying characters
#include <fstream>
#include <string.h>
#include <sstream>
#include <conio.h>
#include <thread>
#include <vector>
#include <limits>
#include "authenticationfunc.h"
#include "colorheader.h"
#include <windows.h>

using namespace std;

const int numberofstruct =1000;
HANDLE j= GetStdHandle(STD_OUTPUT_HANDLE);
/**ADDITIONAL FUNCTION**/
struct appointmentstruct {

   string docname;
   string apptime;
   string days;
   string patientname;
   string status;
   string mobilenum;
   int patientno;
};

vector<appointmentstruct>docappointment;

int rowreadfile(const string& filename){
       ifstream inputFile(filename);
            if (inputFile.is_open()) {
            int rowCount = 0;
            string row;
            while (getline(inputFile, row)) {
                rowCount++;
            }
             return rowCount;
            inputFile.close();
            }
            else{
                cerr << "Unable to open the file." << endl;
                return 1;
            }
        }

string reverseusername(string name){
     string result;

    for (char c : name) {
        if (c=='*') {
            result +=' ';
        }
        else{
            result += c;
        }
    }

    return result;


}


/**PATIENT HOMEPAGE **/

int patienthomepg(string username){
    int patientnum;
        cout<<"\n\n\n\n";
    cout <<RED<<"\n\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout<<YELLOW<<"\n\t\t\t\t\t* * * * * * * * * *  Welcome "<<reverseusername(username)<<" * * * * * * * * * *"<<RESET<<endl;
    cout <<BLUE<<"\n\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout <<GREEN<<"\n\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<<YELLOW<<"* * * * *[PATIENT's MENU]* * * * *"<<RESET<<GREEN<<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" <<RESET<<endl;
    cout<<BrightWhite<<"\n\t\t\t\t\t\t\t        1.View Medical Records"<<RESET<<endl;
    cout<<BrightWhite<<"\n\n\t\t\t\t\t\t\t        2.Schedule Appointments"<<RESET<<endl;
    cout<<BrightWhite<<"\n\n\t\t\t\t\t\t\t        3.Cancel Appointments"<<RESET<<endl;
    cout<<BrightWhite<<"\n\n\t\t\t\t\t\t\t        4.Update Personal Information"<<RESET<<endl;
    cout<<BrightWhite<<"\n\n\t\t\t\t\t\t\t        5.Exit"<<RESET<<endl;
    cout<<GREEN<<Bold<< "\n\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET;
    cout<<BrightWhite<<"\n\t\t\tEnter the option Number(1-5)\t: "<<RESET;
     while (!(cin >>patientnum) || !(patientnum>0 && patientnum<=5) ||(isalpha(patientnum)))
        {
           cout<<RED<<Bold<< "\n\t\t\t-----------------------------------------------------------------------------------------------------"<<RESET;
                cout<<RED<<"\n\t\t\tInvalid option.Enter a valid option number[1-5]: "<<RESET;
            cin.clear();             // Clear the error flag
            cin.ignore(INT_MAX, '\n'); // Discard invalid input
                }

    cout <<RED<<"\n\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";

    return patientnum;

}


/**PERSONAL INFORMATION FUNCTION[FUNCTION 1]**/

vector<patientdetails> patientfile(string username,const string& filename){//This used Read data from [patientlogin txt] and transfer data to [personalinfo]func (COMPLETED)
    vector<patientdetails>logpatient;
    ifstream read(filename);//read the file
    if(read.is_open()){     //check whether the file is open
        string row;
        read.seekg(0,ios::beg);//read data from the being
        while(getline(read,row)){//get data store in file row wise and stored to [read]
            istringstream iss(row);//[iss] is a object of (istringstream) which read word by word.
            patientdetails patientdet;

            if(iss>>patientdet.username>>patientdet.mobile>>patientdet.email){//taken word stored to each of parts
               if(patientdet.username==username){//check taken username(string username) with name read from the file.
                    logpatient.push_back(patientdet);//pass the data to vector [logpatient] after condition success
               }
            }

        }
        read.close();
    return logpatient;
    }



}

int personalinfo(string username){//Display personal information.[COMPLETED]

    vector<patientdetails> patientdet=patientfile(username,"patientlogin_details");//Data Read from the Patientfile stored to vector[patientdet]
    int code;                                                                     //variable that store user given value
    cout<<"\n\n\n\n";
    cout <<BLUE<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    for(int i=0;i<1;i++){//Vector array
        cout<<YELLOW<<"\n\t\t\t\t\t* * * * * * * * * * * * *[View Personal Information] * * * * * * * * * * * *"<<RESET<<endl;
        cout<<RED<<"\n\t\t\t\t\t\t\t        Patient Name\t\t:"<<RESET<<BrightWhite<<reverseusername(patientdet[i].username)<<RESET;
        cout<<RED<<"\n\t\t\t\t\t\t\t        Patient Phone Number\t:"<<RESET<<BrightWhite<<patientdet[i].mobile<<RESET;
        cout<<RED<<"\n\t\t\t\t\t\t\t        Patient E-mail\t\t:"<<RESET<<BrightWhite<<patientdet[i].email<<RESET<<endl;
    }
    cout <<BLUE<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
   cout<<BrightWhite<<"\n\t\t\t\tEnter the option Number for Back(code-3)\t: "<<RESET;
     while (!(cin >> code) || !(code==3) ||(isalpha(code))) //Code variable validation
            {
                cout<<RED<<Bold<< "\n\t\t\t\t-----------------------------------------------------------------------------------------------------"<<RESET;
                 cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid option number[code-3]: "<<RESET;

                cin.clear();                // Clear the error flag
                cin.ignore(INT_MAX, '\n'); // Discard invalid input
            }
    return code;                          //return code (3)

}

/**UPDATE PERSONAL INFORMATION FUNCTION**/

void docappointmentfileupdatenum( const string &oldnumber, string newnumber,const string& filename){///this use to update the appointments user mobile number with new mobile number
    ifstream inputfile(filename);
    ofstream outputfile("temp.txt");

    if (!inputfile.is_open() || !outputfile.is_open()) {
        cerr << "Error opening files." ;
        return;
    }

    string row;
    while (getline(inputfile, row)) {
        istringstream read(row);
        string word;


        while (read >> word)  {
            // Replace the word if found
            if (word ==oldnumber) {
                outputfile <<newnumber;
                 outputfile<<" ";

            }
            else {
                outputfile <<word;
                outputfile<<" ";
            }


            }


        // Write the modified line to the output file
        outputfile <<std::endl;
    }

    inputfile.close();
    outputfile.close();

    // Replace the original file with the modified file
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
    }

void fileToupdataInfo(const string& mobile , const string& Eaddress,const string& filename, vector<patientdetails> &patient) {///this use to update the current data of the user to newly updated data
    ifstream inputfile(filename);///used to read the file
    ofstream outputfile("temp.txt");///used to write data to file call[temp.txt]

    if (!inputfile.is_open() || !outputfile.is_open()) {//check whether the file is open
        cerr << "Error opening files." ;
        return;
    }

    string row;///variable to store read data in file as a line
    while (getline(inputfile, row)) {
        istringstream read(row);//catch word by word from the row
        string word;


        while (read >> word)  {//assign catch up word to a variable call[word]
            // Replace the word if found
            if (word ==patient[0].mobile ) {
                outputfile << mobile;
                 outputfile<<" ";

            }else if(word ==patient[0].email){
                 outputfile << Eaddress;
                 outputfile<<" ";

                   }
            else {
                outputfile <<word;
                outputfile<<" ";
            }


            }


        // Write the modified line to the output file
        outputfile <<std::endl;
    }

    inputfile.close();
    outputfile.close();

    // Replace the original file with the modified file
    remove(filename.c_str());///removing the file that data stored currently
    rename("temp.txt", filename.c_str());///rename the file that stored data during the process[temp.txt] file with the previous file name.
}

int updatepersonalinfo(string username){
    vector<patientdetails> patientdet=patientfile(username,"patientlogin_details");///tranfer data read from[patientlogin_det]file to vector[patientdet]
    int backnum=0;
    string Eaddress,mobile;
    char authletter;
   const  string oldnumber=patientdet[0].mobile;
     cout<<"\n\n\n\n";
     cout <<MAGENTA<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
     cout<<YELLOW<<"\n\t\t\t\t\t* * * * * * * * * * * * *[Update Personal Information] * * * * * * * * * * * *"<<RESET<<endl;

    cout<<BrightWhite<<"\n\t\t\t\t(x). Patient Phone Number[Nullcode-0] : "<<RESET;///if user not willing change default enter value is [0]
    SetConsoleTextAttribute(j,15);
    while (cin >> mobile){
            if(mobile=="0"){///check if mobile no is empty, if so assign pervious number to it
                mobile=patientdet[0].mobile;
                break;
            }
            else{
                if("false"==validatePhoneNumber(mobile)){///check the number in correct format
                       cout<<RED<<Bold<< "\n\t\t\t\t---------------------------------------------------------------------------------------------------------------"<<RESET;
                        cout<<MAGENTA<<"\n\t\t\t\t\tInvalid input.Enter a valid Mobile no(format: XXX/XXX/XXXX):"<<RESET;
                        cin.clear();             // Clear the error flag
                        cin.ignore(INT_MAX, '\n'); // Discard invalid input
               }else{
                        mobile=validatePhoneNumber(mobile);
                        break;
                    }
           }
    }
    cout<<BrightWhite<<"\n\t\t\t\t(x). Patient E-mail[Nullcode-0]\t: "<<RESET;
    SetConsoleTextAttribute(j,15);
     while (cin >>Eaddress){
            if(Eaddress=="0"){
                Eaddress=patientdet[0].email;
                break;
            }
            else{
                if("false"==validateEmail(Eaddress)){///check the Email validation(whether its in right format)
                         cout<<RED<<Bold<< "\n\t\t\t\t---------------------------------------------------------------------------------------------------------------"<<RESET;
                         cout<<MAGENTA<<"\n\t\t\t\t\tInvalid input.Enter a valid E-mail:"<<RESET;
                        cin.clear();             // Clear the error flag
                        cin.ignore(INT_MAX, '\n'); // Discard invalid input
                    }else{
                        Eaddress=validateEmail(Eaddress);
                        break;
                    }
              }
        }
        cout<<MAGENTA<<Bold<< "\n\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET;
         cout<<MAGENTA<<"\n\t\t\t\t\tDo you Need Update your personal information[Y/N]? :"<<RESET;///check whether user confirms his/hers request
             while (!(cin >> authletter) || !(authletter=='n' || authletter=='y' || authletter=='M' || authletter=='Y') ||(isdigit(authletter))) //Code variable validation
            {
                 cout<<RED<<Bold<< "\n\t\t\t\t---------------------------------------------------------------------------------------------------------------"<<RESET;
                  cout<<MAGENTA<<"\n\t\t\t\tInvalid input.Enter a valid Option letter[Y/N]:"<<RESET;
                cin.clear();                // Clear the error flag
                cin.ignore(INT_MAX, '\n'); // Discard invalid input
            }
       cout <<GREEN<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
        if(authletter=='y' || authletter=='Y'){

                docappointmentfileupdatenum(oldnumber,mobile,"DoctorAppointment.txt");
                fileToupdataInfo(mobile,Eaddress,"patientlogin_details",patientdet);///file use to update the modified to file using file handling func[filetoupdateinfo]

                this_thread::sleep_for(chrono::seconds(2));
                cout<<YELLOW<<"\n\t\t\t\t\t  * * * * * * * * * * * * *[Data is updated to the system successful] * * * * * * * * * * * *"<<RESET<<endl;
                cout <<GREEN<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
                this_thread::sleep_for(chrono::seconds(6));///used delay excution
                backnum=3;//assign default value inorder to terminator the loop


        }
        else{
                cout<<BrightWhite<<"\n\t\t\t\t Back To Patient Menu[Code-3]\t:"<<RESET;
                  while (!(cin >>backnum) || !( backnum==3) ||(isalpha(backnum)))
                    {
                    cout<<RED<<Bold<< "\n\t\t\t\t---------------------------------------------------------------------------------------------------------------"<<RESET;
                    cout<<MAGENTA<<"\n\t\t\t\tInvalid input.Enter a valid Option number[code-3]:"<<RESET;
                        cin.clear();             // Clear the error flag
                        cin.ignore(INT_MAX, '\n'); // Discard invalid input
                            }


        }



     return backnum;


}


/**SCHEDULING THE APPOINTMENT[FUNCTION2]**/

vector<docdetails> doctorlistread(){///return data to[Doclist]COMPLETED
    vector<docdetails>doclist;//vector created called doclist
    ifstream read;
    read.open("Doctorlist.txt");//check whether [Doctorlist] file is open
    if(read.is_open()){
            string row;
            read.seekg(0,ios::beg);
            while(getline(read,row)){
                istringstream issreader(row);//read word from the row that taken from the file
                docdetails doc;//create variable using struct[docdetails]
                if(issreader>>doc.username){
                    doclist.push_back(doc);//stored it to vector [doclist]
                }
            }
            read.close();
           return doclist;

    }
    else{
        cerr<<"Unable to Read the file";
    }



}

vector<appointmentstruct> appointmentfileread(string username){///check for given username match with the file username and store matched username data to [appoint] vector.
    vector<appointmentstruct>appoint;
    ifstream read;
    read.open("patientAppointment.txt");
    if(read.is_open()){
            string row;
            read.seekg(0,ios::beg);
            while(getline(read,row)){
                istringstream issreader(row);
                appointmentstruct app;
                if(issreader>>app.patientno>>app.docname>>app.patientname>>app.days>>app.apptime>>app.status){
                        if(app.patientname==username){
                             appoint.push_back(app);
                             }

                }

            }
            read.close();
           return appoint;

    }
    else{
        cerr<<"Unable to Read the file";
    }



}

int AppointmentSchedulefile(const vector<appointmentstruct> &appointmentsch){///this function store patient scheduling data to the file
    ofstream writefilepatient;
    ofstream writefiledoc;
    writefilepatient.open("patientAppointment.txt",ios::app);
    writefiledoc.open("DoctorAppointment.txt",ios::app);
    if(writefiledoc.is_open() && writefilepatient.is_open()){
            for(const appointmentstruct& p:appointmentsch){
                          writefilepatient<<left<<p.patientno<<" "<<p.docname<<" "<<p.patientname<<" "<<p.days<<" "<<p.apptime<<" "<<p.status<<endl;
                          writefiledoc<<left<<p.patientno<<" "<<p.docname<<" "<<p.patientname<<" "<<p.mobilenum<<" "<<p.days<<" "<<p.apptime<<" "<<p.status<<endl;
                    }

                    //cout<<"\n\tData is updated to the system successful";


                    writefilepatient.close();
                    writefiledoc.close();
                    return 0;


    }
    else{
        //cerr<<"Unable to Open the file";

       return 1;
    }


}

void docandnewpatientlist(string doctornm,string patientnm){///this function stored doc and patient name
    ifstream read;
    ofstream write;
    read.open("DocNewAPatientList.txt");
    write.open("DocNewAPatientList.txt",ios::app);
    if(read.is_open()&&write.is_open()){
            int num,valu=0;
            string docname,patientname;
            if(valu==0){
            while(read>>docname>>patientname){
                    //cout<<docname<<" "<<patientname<<endl;
                if(docname==doctornm && patientname==patientnm){
                    //cout<<"1";
                    valu=0;
                    break;
                }
                else{
                    valu=1;
                }
            }
         }

         if(valu==1) {
                      write<<doctornm<<" "<<patientnm<<endl;

                    }

    }else{
            cerr<<"\nUnable to read the file";
            }

       write.close();
        read.close();
}

int appointment(string docname,string username){///COMPLETED
 vector<patientdetails> patientdet=patientfile(username,"patientlogin_details");///tranfer username and filename to function[patientfile]and get return
 vector<appointmentstruct>appdet=appointmentfileread(username);
    int rowcount=rowreadfile("DoctorAppointment.txt");///row count of the [doctorappointment file]


    appointmentstruct p[numberofstruct];///sturct created to store appointment requird varible
    int i,validnum,days;
    bool value;//bool used to check the condition true /false
   char validmsg;//character varable used to store character
    string app1="8.30am-10.00am";
    string app2="11.00am-3.00pm";
    string app3="4.30pm-6.00pm";
    string app4="8.00pm-11.00pm";
    char appcode;//allow user to enter the characters assign to hardcoded time
    string state,state1;
do{
    value=true;//default condition is true
    docappointment.clear();//clear the existing data in the  vector
    for(i=rowcount;i<rowcount+1;i++){
                cout<<"\n\n\n\n";
                cout <<RED<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
                cout<<YELLOW<<"\n\t\t\t\t\t  * * * * * * * * * * * * *"<<RESET<<MAGENTA<<"[Dr."<<docname<<" Appointment Schedule]"<<RESET<<YELLOW<<" * * * * * * * * * * * *"<<RESET<<endl;
                //out<<"\n\t****[Dr."<<docname<<" Appointment Schedule]****";
                cout<<BrightWhite<<"\n\t\t\t\t\t\t\t\t   "<<"     " <<"\t\t\t1-Monday"<<RESET<<endl;
                cout<<BrightWhite<<"\n\t\t\t\t\t\t\t\tA :"<<  app1  <<"\t\t2-Tuesday"<<RESET<<endl;
                cout<<BrightWhite<<"\n\t\t\t\t\t\t\t\tB :"<<  app2  <<"\t\t3-Wensday"<<RESET<<endl;
                cout<<BrightWhite<<"\n\t\t\t\t\t\t\t\tC :"<<  app3  <<"\t\t4-Thursday"<<RESET<<endl;
                cout<<BrightWhite<<"\n\t\t\t\t\t\t\t\tD :"<<  app4  <<"\t\t5-Friday"<<RESET<<endl;
                cout<<BrightWhite<<"\n\t\t\t\t\t\t\t\t   "<<"     " <<"\t\t\t6-Saturday"<<RESET<<endl;
                cout<<BrightWhite<<"\n\t\t\t\t\t\t\t\t   "<<"     " <<"\t\t\t7-Sunday"<<RESET<<endl;
                cout<<MAGENTA<<Bold<< "\n\t\t\t\t     **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET;
                 cout<<BrightWhite<<"\n\t\t\t\t\tEnter the day option Number(1-7)\t: "<<RESET;
                while (!(cin >> days) || !(days>=1 && days<=7) ||(isalpha(days))) ///Code variable validation
                 {
               cout<<RED<<Bold<< "\n\t\t\t\t------------------------------------------------------------------------------------------------------"<<RESET;
                cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid Option number(1-7):"<<RESET;
                cin.clear();                // Clear the error flag
                cin.ignore(INT_MAX, '\n'); // Discard invalid input
                 }

                switch(days){
                case 1:
                    state1="Monday";
                    break;
                case 2:
                    state1="Tuesday";
                    break;
                case 3:
                    state1="Wednesday";
                    break;
                case 4:
                    state1="Thursday";
                    break;
                case 5:
                    state1="Friday";
                    break;
                case 6:
                    state1="Saturday";
                    break;
                case 7:
                    state1="Sunday";
                    break;
                }
                p[i].days=state1;

               cout<<BrightWhite<<"\n\t\t\t\t\tEnter the Appointment Schedule time[A/B/C/D: "<<RESET;
                while (!(cin >> appcode) || !(appcode=='A' || appcode=='B'|| appcode=='C' || appcode=='D') ||(isdigit(appcode))) ///Code variable validation
                 {
               cout<<RED<<Bold<< "\n\t\t\t\t------------------------------------------------------------------------------------------------------"<<RESET;
                cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid Option number(A/B/C/D):"<<RESET;
                cin.clear();                // Clear the error flag
                cin.ignore(INT_MAX, '\n'); // Discard invalid input
                 }
                if(appcode=='a' || appcode=='A'){
                    state=app1;
                }
                else if(appcode=='b' || appcode=='B'){
                    state=app2;
                }
                else if(appcode=='c' || appcode=='C'){
                    state=app3;
                }
                else if(appcode=='d' || appcode=='D'){
                    state=app4;
                }
                else{
                    cout<<"Invalid operation";//Not relavent
                }

                p[i].status="uncompleted";
                p[i].apptime=state;
                p[i].patientname=removespace(patientdet[0].username);
                p[i].mobilenum=patientdet[0].mobile;
                p[i].docname=removespace(docname);
                p[i].patientno=rowcount;




                         for(size_t j=0;j<appdet.size();j++){
                         if((p[i].docname == appdet[j].docname) && (p[i].patientname== appdet[j].patientname) && (p[i].days == appdet[j].days) && (p[i].apptime == appdet[j].apptime)){//check condition
                                cout<<YELLOW<<"\n\t\t\t\t\t  * * * * * * * * * * * * *"<<RESET<<RED<<"[Already Appointment is Schedule]"<<RESET<<YELLOW<<" * * * * * * * * * * * *"<<RESET<<endl;
                                 cout <<GREEN<<"\n\t\t\t\t  =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
                                value=false;
                                break;
                                }
                         }
                         if(value){
                            docappointment.push_back(p[i]);
                           int value1=AppointmentSchedulefile(docappointment);///transfer the data to appointmentschedulingfile function

                           if(value1==0 ){
                                    cout<<removespace(docname)<<removespace(username);
                                      cout<<YELLOW<<"\n\t\t\t\t\t  * * * * * * * * * * * * *[Data is updated to the system successful] * * * * * * * * * * * *"<<RESET<<endl;
                                        cout <<GREEN<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
                                        this_thread::sleep_for(chrono::seconds(4));
                                        docandnewpatientlist(removespace(p[i].docname),removespace(p[i].patientname));///check whether this patient scheduling a new doctor
                                }
                                   else {
                                    cout<<YELLOW<<"\n\t\t\t\t\t  * * * * * * * * * * * * *"<<RESET<<RED<<"[Unable to Open the file]"<<RESET<<YELLOW<<" * * * * * * * * * * * *"<<RESET<<endl;

                                }

                            validmsg='n';///this assign to terminate the while loop if data being stored successfully

                         }
                         else{
                                    cout<<MAGENTA<<Bold<< "\n\t\t\t\t     **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET;
                                   cout<<BrightWhite<<"\n\t\t\t\tDo you need to Schedule Again[Y/N]\t: "<<RESET;///condition whether user need to try again if[value=false]
                                    cin>>validmsg;
                                    system("cls");
                         }

                            }
                } while(validmsg !='n');
                        this_thread::sleep_for(chrono::seconds(2));
                        return 4;///return value for to terminate the loop


}

int DoctorList(string username){///COMPELETED
    int i,num,backnum=0;
    string docname;
    vector<docdetails>doclist=doctorlistread();//read doctor name from[doctorlistread] func to [doclist] vector
    do{
            cout<<"\n\n\n\n";
            cout <<RED<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
            cout<<YELLOW<<"\n\t\t\t\t\t  * * * * * * * * * * * * *[Available Doctor List] * * * * * * * * * * * *"<<RESET<<endl;
            for(size_t i=0;i<doclist.size();i++){
                cout<<BrightWhite<<"\n\t\t\t\t\t\t\t        "<<BrightWhite<<i+1<<"- Dr."<<reverseusername(doclist[i].username)<<RESET<<endl;
            }
             cout<<MAGENTA<<Bold<< "\n\t\t\t\t     **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET;
             cout<<BrightWhite<<"\n\t\t\t\t\t\t\t\t 1.Scheduling Appointments"<<RESET<<endl;
             cout<<BrightWhite<<"\n\t\t\t\t\t\t\t\t 2.Back To Menus"<<RESET;

            cout <<MAGENTA<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
             cout<<BrightWhite<<"\n\t\t\t\tEnter the option Number(1-2)\t: "<<RESET;
            while (!(cin >>num) || !(num>0 && num<=2) ||(isalpha(num)))//i variable to take user input[Error validation completed]
                     {  cout<<RED<<Bold<< "\n\t\t\t\t------------------------------------------------------------------------------------------------------"<<RESET;
                        cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid Option number[1-2]:"<<RESET;
                        cin.clear();             // Clear the error flag
                        cin.ignore(INT_MAX, '\n'); // Discard invalid input
                     }

            if(num==1){
                     cout<<YELLOW<<Bold<< "\n\t\t\t\t--------------------------------------------------------------------------------------------------------"<<RESET;
                     cout<<BrightWhite<<"\n\t\t\t\tEnter the doctor's Number(1/2/3...)/[Back-0]: "<<RESET;
                     while (!(cin >>i) || !(i>=0 && i<doclist.size()) ||(isalpha(i)))//i variable to take user input[Error validation completed]
                         {  cout<<RED<<Bold<< "\n\t\t\t\t------------------------------------------------------------------------------------------------------"<<RESET;
                            cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid Option number(1/2/3...)/[Back-0]:"<<RESET;
                            cin.clear();             // Clear the error flag
                            cin.ignore(INT_MAX, '\n'); // Discard invalid input
                         }

                         if(i!=0){
                                docname=reverseusername(doclist[i-1].username);//Identify the position of the doctor in vector.
                                 cout <<GREEN<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<<RESET;
                                system("cls");
                                backnum=appointment(docname,username);//transfer data from [Doclist] to appointment function

                        }
                        else{
                          backnum=0;//Assign value to terminate the loop
                        }

            }
            else if(num==2){
                    backnum=3;//Assign value to terminate the loop

            }


             system("cls");//clear console screen
    }while(backnum != 3);
    return backnum;

}




/**VIEW PAIIENT APPOINTMENT[FUNCTION 1]**/

vector<appointmentstruct> appointmentview(const string &filename,int subnum,string username){///this read data from file() transfer to viewrecord2 func
    vector<appointmentstruct>appoint;//create a vector.
    ifstream read;
    read.open(filename);//open the file
        string row;
        read.seekg(0,ios::beg);
        while(getline(read,row)){
            istringstream issreader(row);
            appointmentstruct app;
          if(subnum==1){
            if(issreader>>app.patientno>>app.docname>>app.patientname>>app.days>>app.apptime>>app.status){
               if(app.patientname==username && app.status=="uncompleted"){//store all the data related to proper username and status.
                    appoint.push_back(app);
               }
            }
          }
          else if(subnum==2){
            if(issreader>>app.patientno>>app.docname>>app.patientname>>app.days>>app.apptime>>app.status){
               if(app.patientname==username && app.status=="Completed"){//cancel should be completed
                    appoint.push_back(app);
               }
            }
          }

        }
        read.close();
    return appoint;

    }

int viewrecords2(string username){///link with viewrecords[COMPLETED]
    int num,subnum;
    do{
                 subnum=0;
                 num=0;//varible store user inputs related to users choices
                 cout<<"\n\n\n\n";
                cout<<GREEN<<Bold<< "\n\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET<<MAGENTA<<"[View Appointment Record]"<<RESET<<GREEN<<"-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET<<endl;
                cout<<YELLOW<<"\n\t\t\t\t\t\t\t        1.Upcoming Appointment"<<RESET<<endl;//this link with [personalinfo] file[COMPLETED]
                cout<<YELLOW<<"\n\t\t\t\t\t\t\t        2.Previous Appointment"<<RESET<<endl;//this link with [viewrecords2]
                cout<<YELLOW<<"\n\t\t\t\t\t\t\t        3.Back To Menu"<<RESET<<endl;
                cout <<GREEN<<"\n\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<<RESET;
                cout<<BrightWhite<<"\n\t\t\tEnter the option Number(1-3)\t: "<<RESET;

                while (!(cin >> num) || !(num>0 && num<=3) ||(isalpha(num)))//DATA VALIDATION COMPLETED
                    {
                         cout<<RED<<Bold<< "\n\t\t\t---------------------------------------------------------------------------------------------------------------"<<RESET;
                        cout<<RED<<"\n\t\t\tInvalid option.Enter a valid Option[1/2/3]:"<<RESET;

                        cin.clear();             // Clear the error flag
                        cin.ignore(INT_MAX, '\n'); // Discard invalid input
                    }


                vector<appointmentstruct>appointrec=appointmentview("patientAppointment.txt",num,username);//this used store the completed/uncompleted appointment details
                if(num==1){
                        system("cls");
                    cout<<"\n\n\n\n";
                    cout <<RED<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
                    cout<<YELLOW<<"\n\t\t\t\t\t* * * * * * * * * * * *[Upcoming Appointment Record] * * * * * * * * * * * *"<<RESET<<endl;
                     cout<<"\n";

                    for(size_t j=0;j<appointrec.size();j++){//data stored to the  vector [appoint] from [appointmentview function] being displayed (Uncompleted appointment) to user
                        cout<<BrightWhite<<"\n\t\t\t\t\t\t\t        "<<j+1<<": [ Dr."<<reverseusername(appointrec[j].docname)<<"]:["<<appointrec[j].days<<"]:["<<appointrec[j].apptime<<"]"<<endl;
                    }
                     cout <<RED<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
                   cout<<BrightWhite<<"\n\t\t\t\tEnter the option Number for Back(code-3)\t: "<<RESET;
                    while (!(cin >> subnum) || (subnum !=3))//Allow user to return to the back menu & Validate Completed
                      {
                       cout<<RED<<Bold<< "\n\t\t\t\t-----------------------------------------------------------------------------------------------------"<<RESET;
                        cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid option number[code-3]: "<<RESET;

                        cin.clear();             // Clear the error flag
                        cin.ignore(INT_MAX, '\n'); // Discard invalid input
                    }
                     cout <<RED<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
                    }
                else if(num==2){
                    system("cls");
                    cout<<"\n\n\n\n";
                    cout <<RED<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
                    cout<<YELLOW<<"\n\t\t\t\t\t* * * * * * * * * * * * *[Previous Appointment Record] * * * * * * * * * * * *"<<RESET<<endl;
                     //cout<<"\n";
                    for(size_t j=0;j<appointrec.size();j++){//data stored to the  vector [appoint] from [appointmentview function] being displayed (completed appointment) to user
                        cout<<BrightWhite<<"\n\t\t\t\t\t\t"<<j+1<<": [ Dr."<<reverseusername(appointrec[j].docname)<<"]:["<<appointrec[j].days<<"]:["<<appointrec[j].apptime<<"]"<<endl;
                    }
                     cout <<RED<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
                     cout<<BrightWhite<<"\n\t\t\t\tEnter the option Number for Back(code-3)\t: "<<RESET;
                    while (!(cin >> subnum) || (subnum !=3))//Allow user to return to the back menu & Validate Completed
                    {
                       cout<<RED<<Bold<< "\n\t\t\t\t-----------------------------------------------------------------------------------------------------"<<RESET;
                        cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid option number[code-3]: "<<RESET;
                        cin.clear();             // Clear the error flag
                        cin.ignore(INT_MAX, '\n'); // Discard invalid input
                    }
                   cout <<RED<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
                    }
                else if(num==3) {//Back statement from current function .
                        subnum=0;//special code used terminator the loop
                    }
                system("cls");
      }while(subnum==3);
        subnum=3;//special assign
        return subnum;
}

int viewrecords(string name){///[COMPLETED]
    int authcode=0;//variable store user given inputs
    int authsubcode=0;//variable store data return from other function
    do{
                 cout<<"\n\n\n\n";
                cout<<GREEN<<Bold<< "\n\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET<<MAGENTA<<"[View Medical Records]"<<RESET<<GREEN<<"-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET<<endl;
                cout<<YELLOW<<"\n\t\t\t\t\t\t\t        1.View Personal Information"<<RESET<<endl;//this link with [personalinfo] file[COMPLETED]
                cout<<YELLOW<<"\n\t\t\t\t\t\t\t        2.View Appointment Details"<<RESET<<endl;//this link with [viewrecords2]
                cout<<YELLOW<<"\n\t\t\t\t\t\t\t        3.Back To Menu"<<RESET<<endl;
                cout <<GREEN<<"\n\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<<RESET;
                cout<<BrightWhite<<"\n\t\t\tEnter the option Number(1-3)\t: "<<RESET;

             while (!(cin >> authcode) || !(authcode>0 && authcode<=3) ||(isalpha(authcode)))//authcode variable to take user input[Error validation completed]
            {
                cout<<RED<<Bold<< "\n\t\t\t----------------------------------------------------------------------------------------------------------"<<RESET;
                cout<<RED<<"\n\t\t\tInvalid option.Enter a valid Option[1/2/3]:"<<RESET;

                cin.clear();             // Clear the error flag
                cin.ignore(INT_MAX, '\n'); // Discard invalid input
            }

            if(authcode==1){//COMPLETED
                system("cls");
                authsubcode=personalinfo(name);
            }
            else if(authcode==2){
                    system("cls");
                authsubcode=viewrecords2(name);

            }
            else{
                authsubcode=3;//special code used terminator the loop
            }
                system("cls");

    }while(authsubcode!=3 || authcode!=3);
     return authcode;

}


/**CANCEL APPOINTMENT**/

void fileToupdatacancelInfo( int cancelnum, const string &filename, vector<appointmentstruct> &appcancel) {///[COMPLETED]
    ifstream inputfile(filename);///reading the file
    ofstream outputfile("temp.txt");///outputing data to a file

    if (!inputfile.is_open() || !outputfile.is_open()) {///check whether file is open or not.
        cerr << "Error opening files." ;

    }

    string row;///variable used to store rows
    while (getline(inputfile, row)) {///read line of the file and storing to[row]
        istringstream read(row);///catch up word by word in the file.
        string word;///variable which store the word pick in line[709]
        while (read >> word)  {
          if(word==to_string(appcancel[cancelnum].patientno)) {///check the data store in [word] equals to the[cancelnum]
                istringstream read(row);///if condition is true check the row with other data in the file
                string word1;
                while (read>>word1) {


                        if (word1==appcancel[cancelnum].status) {
                            outputfile <<"Cancel";///if the condition true the replace the word[cancel] to that position
                             outputfile<<" ";
                             }
                         else {
                              outputfile <<word1;
                              outputfile<<" ";///else replace the same word
                            }
                       }

                       break;

                   }
            else {
                outputfile <<word;
                outputfile<<" ";
            }
        }
            ///Write the modified line to the output file
             outputfile <<endl;


        }




    inputfile.close();
    outputfile.close();

    /// Replace the original file with the modified file
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
}

int appointmentcancel(string username){///COMPLETED
    vector<appointmentstruct>appoint;
    char letter;
    int subname=1;
    int cancelnum=0;
    do{
            appoint.clear();
            cout<<"\n\n\n\n";
            cout <<MAGENTA<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
            cout<<YELLOW<<"\n\t\t\t\t\t* * * * * * * * * * * * *[Appointment Cancellation] * * * * * * * * * * * *"<<RESET<<endl;
            appoint=appointmentview("patientAppointment.txt",subname,username);//returning[uncompleted] appointment to vector[appoint]
            for(size_t j=0;j<appoint.size();j++){
                 cout<<BrightWhite<<"\n\t\t\t\t\t\t\t        "<<j+1<<": [ Dr."<<reverseusername(appoint[j].docname)<<"] : ["<<appoint[j].days<<"] : ["<<appoint[j].apptime<<"]"<<RESET<<endl;
            }


            cout<<GREEN<<Bold<< "\n\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET;
            cout<<BrightWhite<<"\n\t\t\t\tEnter option number for [Cancelling Appointment]/[backcode-0]: "<<RESET;
             while (!(cin >> cancelnum) || !(cancelnum>=0 && cancelnum<appoint.size()+1) ||(isalpha(cancelnum)))//cancelnum variable to take user input[Error validation completed]
                {
                cout<<RED<<Bold<< "\n\t\t\t\t------------------------------------------------------------------------------------------------------"<<RESET;
                 cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid Option number(1/2/3...)/[Back-0]:"<<RESET;
                cin.clear();             // Clear the error flag
                cin.ignore(INT_MAX, '\n'); // Discard invalid input
                }
               // cout<<"\n\t-----------------------------------------------";
            if(cancelnum!=0){

                 cout<<BrightWhite<<"\n\t\t\t\tDo you need to Cancel this appointment[Y/N]\t: "<<RESET;
                 while (!(cin >> letter) || !(letter=='y' ||letter=='Y' || letter=='n'|| letter=='N') ||(isdigit(letter)))//letter variable to take user input[Error validation completed]
                    {
                    cout<<RED<<Bold<< "\n\t\t\t\t------------------------------------------------------------------------------------------------------"<<RESET;
                    cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid Option letter[Y/N]:"<<RESET;

                    cin.clear();             // Clear the error flag
                    cin.ignore(INT_MAX, '\n'); // Discard invalid input
                   }
                   cout <<MAGENTA<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
                if(letter=='y' || letter=='Y'){
                        cancelnum=cancelnum-1;
                        cout<<cancelnum;
                        fileToupdatacancelInfo(cancelnum,"patientAppointment.txt",appoint);
                        this_thread::sleep_for(chrono::seconds(1));
                        fileToupdatacancelInfo(cancelnum,"DoctorAppointment.txt",appoint);
                          cout<<YELLOW<<"\n\t\t\t\t\t  * * * * * * * * * * * * *[Appointment is Successfully Cancel] * * * * * * * * * * * *"<<RESET<<endl;
                          cout <<GREEN<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
                          this_thread::sleep_for(chrono::seconds(4));
                          cout<<BrightWhite<<"\n\t\t\t\tDo you need to Continue[Y/N]: "<<RESET;
                        while (!(cin >> letter) || !(letter=='y' ||letter=='Y' || letter=='n'|| letter=='N') ||(isdigit(letter)))//letter variable to take user input[Error validation completed]
                            {
                            cout<<RED<<Bold<< "\n\t\t\t\t------------------------------------------------------------------------------------------------------"<<RESET;
                            cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid Option letter[Y/N]:"<<RESET;

                            cin.clear();             // Clear the error flag
                            cin.ignore(INT_MAX, '\n'); // Discard invalid input
                           }
                            cout<<BLUE<<Bold<< "\n\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET;
                }

                else{
                    letter='y';

                }
        }else{
             letter='n';

            }


            system("cls");
    }while(letter!='n' );
    return 3;
    this_thread::sleep_for(chrono::seconds(2));

}






