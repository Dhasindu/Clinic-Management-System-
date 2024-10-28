#include <iostream>
#include <cctype>//contains definitions for C++ for classifying characters
#include <fstream>
#include <string.h>
#include <sstream>
#include <conio.h>
#include <thread>
#include <vector>
#include "colorheader.h"
#include "authenticationfunc.h"
#include "patientfunctionheader.h"

using namespace std;

const int numberofstruct=1000;

struct PatientMedicalRecord{
    string patientname;
    string diagnosis;
    string prescribed;
    string additionalRec;

};

struct docupdatelist{
    string docname;
    string patientname;

};

/**VIEW SCHEDULE FUNCTION**/

vector<appointmentstruct> viewdocschedul(string username){///this function store appointment to vector related to doctor that a incompleted
    vector<appointmentstruct>appoint;
    ifstream read;
    read.open("DoctorAppointment.txt");
    if(read.is_open()){
            string row;
            read.seekg(0,ios::beg);
            while(getline(read,row)){
                istringstream issreader(row);
                appointmentstruct app;
                if(issreader>>app.patientno>>app.docname>>app.patientname>>app.mobilenum>>app.days>>app.apptime>>app.status){
                        if(app.docname==username && app.status=="uncompleted"){
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

string removespacedocupdates(string name) {///remove space between words
    string result;

    for (char c : name) {
        if (!isspace(c)) {
            result += c;
        }
        else{
            result += '_';
        }
    }

    return result;
}

string reversedocupdates(string name){///remove  space between word
     string result;

    for (char c : name) {
        if (c=='_') {
            result +=' ';
        }
        else{
            result += c;
        }
    }

    return result;


}

int viewdoctorschedul(string username){///completed
     int backcode=0;
    cout<<"\n\n\n\n";
    cout <<MAGENTA<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout<<YELLOW<<"\n\t\t\t\t\t* * * * * * * * * * * * *[Upcoming Appointment ] * * * * * * * * * * * *"<<RESET<<endl;
    vector<appointmentstruct>appoint=viewdocschedul(username);///transfer data from [viewdocschedul] to vector appoint
    cout<<"\n";
    for(size_t j=0;j<appoint.size();j++){///display the appointment
        cout<<BrightWhite<<"\n\t\t\t\t\t\t        "<<j+1<<": [ "<<reverseusername(appoint[j].patientname)<<"]:["<<appoint[j].mobilenum<<"] : ["<<appoint[j].days<<"]:["<<appoint[j].apptime<<"]"<<RESET<<endl;
        }
         cout<<GREEN<<Bold<<"\n\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET;
         cout<<BrightWhite<<"\n\t\t\t\tBack To menu[Backcode:3]\t: "<<RESET;
         while (!(cin >> backcode) || !(backcode==3) ||(isalpha(backcode))) //Code variable validation
            {
                cout<<RED<<Bold<<"\n\t\t\t\t-----------------------------------------------------------------------------------------------------"<<RESET;
                cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid option number[Backcode:3]: "<<RESET;
                cin.clear();                // Clear the error flag
                cin.ignore(INT_MAX, '\n'); // Discard invalid input
            }
        return backcode;

}

/***DOCTOR HOMEPAGE FUNCTION**/

int doctorhomepg(string username){///COMPLETED
    int doctornum;
    cout<<"\n\n\n\n";
    cout <<RED<<"\n\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout<<YELLOW<<"\n\t\t\t\t\t* * * * * * * * * *  Welcome Dr."<<reverseusername(username)<<" * * * * * * * * * *"<<RESET<<endl;
    cout <<BLUE<<"\n\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout <<GREEN<<"\n\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<<YELLOW<<"* * * * *[DOCTOR's MENU]* * * * *"<<RESET<<GREEN<<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" <<RESET<<endl;
    cout<<BrightWhite<<"\n\t\t\t\t\t\t\t      1.View Schedule"<<RESET<<endl;
    cout<<BrightWhite<<"\n\n\t\t\t\t\t\t\t      2.Access Patient Records"<<RESET<<endl;
    cout<<BrightWhite<<"\n\n\t\t\t\t\t\t\t      3.Update Patient Records"<<RESET<<endl;
    cout<<BrightWhite<<"\n\n\t\t\t\t\t\t\t      4.Mark Appointment"<<RESET<<endl;
    cout<<BrightWhite<<"\n\n\t\t\t\t\t\t\t      5.Exit"<<RESET<<endl;
    cout<<GREEN<<Bold<< "\n\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET;
    cout<<BrightWhite<<"\n\t\t\tEnter the option Number(1-5)\t: "<<RESET;
    while (!(cin >> doctornum) || !(doctornum>0 && doctornum<=5) ||(isalpha(doctornum)))
        {
             cout<<RED<<Bold<<"\n\t\t\t-----------------------------------------------------------------------------------------------------"<<RESET;
                cout<<RED<<"\n\t\t\tInvalid option.Enter a valid option number[1-5]: "<<RESET;
            cin.clear();             // Clear the error flag
            cin.ignore(INT_MAX, '\n'); // Discard invalid input
                }

    cout <<RED<<"\n\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";

    return doctornum;

}


/**DOCTOR MARK APPOINTMENT FUNCTION**/

void DocUpdateappointmentfile( int updateappoint, const string &filename, vector<appointmentstruct> &updateapp) {///this used to replace[uncompleted word] with cancel
    ifstream inputfile(filename);
    ofstream outputfile("temp.txt");

    if (!inputfile.is_open() || !outputfile.is_open()) {
        cerr << "Error opening files." ;
        //return 1;
    }

    string row;
    while (getline(inputfile, row)) {
        istringstream read(row);
        string word;
        while (read >> word)  {
          if(word==to_string(updateapp[updateappoint].patientno)) {
                istringstream read(row);
                string word1;
                while (read>>word1) {


                        if (word1==updateapp[updateappoint].status) {
                            outputfile <<"Completed";
                             outputfile<<" ";
                             }
                         else {
                              outputfile <<word1;
                              outputfile<<" ";
                            }
                       }

                       break;

                   }
            else {
                outputfile <<word;
                outputfile<<" ";
            }
        }
            // Write the modified line to the output file
             outputfile <<endl;


        }




    inputfile.close();
    outputfile.close();


    // Replace the original file with the modified file
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
}


int docMarkAppointment(string username){///COMPLETED
    char authletter;
    vector<appointmentstruct>appoint;
    appoint.clear();///clear the vector so updates will be able to store

    int updateappoint=0;
    cout<<"\n\n\n\n";
     cout <<MAGENTA<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
     cout<<YELLOW<<"\n\t\t\t\t\t   * * * * * * * * * * * * *[Appointment  Update] * * * * * * * * * * * *"<<RESET<<endl;
    appoint=viewdocschedul(username);//transfer username to the func[viewdocschdul] and get appointment list
    for(size_t j=0;j<appoint.size();j++){//Loop is limited the size of the vector
        cout<<BrightWhite<<"\n\t\t\t\t\t\t        "<<j+1<<": [ "<<reverseusername(appoint[j].patientname)<<"]:["<<appoint[j].mobilenum<<"] : ["<<appoint[j].days<<"]:["<<appoint[j].apptime<<"]"<<endl;
        }

   cout<<GREEN<<Bold<< "\n\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET<<endl;
    cout<<BrightWhite<<"\n\t\t\t\tEnter the Option Number(1/2..)]/[Backcode-0]\t: "<<RESET;
    while (!(cin >>updateappoint) || !(updateappoint>=0 && updateappoint<appoint.size()+1) ||(isalpha(updateappoint)))
        {
            cout<<RED<<Bold<<"\n\t\t\t\t-----------------------------------------------------------------------------------------------------"<<RESET;
            cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid option number(1/2..)]/[Backcode-0]: "<<RESET;
            cin.clear();             // Clear the error flag
            cin.ignore(INT_MAX, '\n'); // Discard invalid input
        }
   if(updateappoint !=0){
          cout<<BrightWhite<<"\n\t\t\t\tDo you need to continue [Y/N]: "<<RESET;//check whether the user actually need to mark it.
          while (!(cin >> authletter) || !(authletter=='n' || authletter=='y' || authletter=='M' || authletter=='Y') ||(isdigit(authletter)))
                {
                    cout<<RED<<Bold<<"\n\t\t\t\t-----------------------------------------------------------------------------------------------------"<<RESET;
                    cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid option letter[Y/N]: "<<RESET;
                    cin.clear();                // Clear the error flag
                    cin.ignore(INT_MAX, '\n'); // Discard invalid input
                }



          if(authletter=='y' || authletter=='Y'){
            if(updateappoint !=0){
                    updateappoint=updateappoint-1;//as data stored in vector begin with index[0] so ,1 deducted from the[updateappoint]
                    DocUpdateappointmentfile(updateappoint,"patientAppointment.txt",appoint);//
                    this_thread::sleep_for(chrono::seconds(1));
                    DocUpdateappointmentfile(updateappoint,"DoctorAppointment.txt",appoint);

                    cout<<YELLOW<<"\n\t\t\t\t\t* * * * * * * * * * * * *[Appointment is Successfully updated to complete] * * * * * * * * * * * *"<<RESET<<endl;
                    cout <<MAGENTA<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
                    this_thread::sleep_for(chrono::seconds(4));
                    updateappoint=3;//assign value to terminate the loop
            }
         }
         else{
                     cout<<YELLOW<<"\n\t\t\t\t\t* * * * * * * * * * * * *[Appointment is not being updated] * * * * * * * * * * * *"<<RESET<<endl;
                    cout <<MAGENTA<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
                    this_thread::sleep_for(chrono::seconds(4));
                  updateappoint=3;//assign value to terminate the loop
                }
    }else{
         updateappoint=3;//assign value to terminate the loop
     }
    return updateappoint;

}


/**UPDATING MEDICAL RECORD FUNCTION**/

vector<docupdatelist>ReaddDocUpdatePatientList(string docname){///this file read the patient related to that doctor and store to vector for return
    vector<docupdatelist>readlist;
    ifstream read;
    read.open("DocNewAPatientList.txt");
    if(read.is_open()){
        string row;
        read.seekg(0,ios::beg);//this statement help to read from the begining
        while(getline(read,row)){
            istringstream issreader(row);
             docupdatelist readls;//struct created to store data read from the file

            if(issreader>>readls.docname>>readls.patientname){//passing the data to the relevant variable
                    if(readls.docname==docname){//condition to check the login doctor name equal to doctor name stored in the file
                    readlist.push_back(readls);//if above condition[284 line] is true then data stored to readlist vector

            }
        }
    }
     return readlist;
     read.close();
    }
    else{
        cerr<<"\n\tUnable to read the file";
    }


}

int writenewpatientmedrecord(const vector<PatientMedicalRecord> &medrecord){///When newly a record add data being append to file
    ofstream write;
    write.open("patientmedicalrec.txt",ios::app);
    if(write.is_open()){
            for(const PatientMedicalRecord& Mdrec:medrecord){
                write<<left<<Mdrec.patientname<<" "<<Mdrec.diagnosis<<" "<<Mdrec.prescribed<<" "<<Mdrec.additionalRec<<endl;
        }

    write.close();
    return 0;

    }
    else{
        return 1;
    }
}

int writeupdatepatientmedrecord(const vector<PatientMedicalRecord> &medrecord){///when data updated total data which stored to a vector being stored to file.
    ofstream write;
    write.open("patientmedicalrec.txt");
    if(write.is_open()){
            for(const PatientMedicalRecord& Mdrec:medrecord){
                write<<left<<Mdrec.patientname<<" "<<Mdrec.diagnosis<<" "<<Mdrec.prescribed<<" "<<Mdrec.additionalRec<<endl;
        }

    write.close();
    return 0;

    }
    else{
        return 1;
    }
}


/**ACCESS PATIENT RECORDS**/

vector<PatientMedicalRecord>accessinfopatient(string username,int *returnvalu){///Transfer medical details of the relevant patient to display
    int num;
    vector<PatientMedicalRecord>accessinfo;
    ifstream read;
    read.open("patientmedicalrec.txt");
    if(read.is_open()){
            string row;
        read.seekg(0,ios::beg);//read from begin of the file
        while(getline(read,row)){
            istringstream issreader(row);
            PatientMedicalRecord Medirec;

            if(issreader>>Medirec.patientname>>Medirec.diagnosis>>Medirec.prescribed>>Medirec.additionalRec){
               if(Medirec.patientname == username){// check whether data taken is satisfied above condition
                    accessinfo.push_back(Medirec);
                    num=0;
                    break;
                    read.close();

               }
               else{
                num=1;
               }
            }
        }
        *returnvalu=num;
        return accessinfo;

    }
    else{

        cerr<<"\n\tUnable to Read the file";
    }


}

int  accessPatientRecord(){///completed
    string patientname;
    int returnvalu=0;
    int backcode=0;
    char authletter;
   vector<PatientMedicalRecord>record;
do{
    cout<<"\n\n\n\n";
    cout <<MAGENTA<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout<<YELLOW<<"\n\t\t\t\t\t* * * * * * * * * * * * *[Access Patient Records] * * * * * * * * * * * *"<<RESET<<endl;
    cout<<BrightWhite<<"\n\t\t\t\tEnter the Patient Name\t: "<<RESET;
    cin.ignore();
    getline(cin,patientname);
    patientname=removespace(patientname);
    record=accessinfopatient(patientname,&returnvalu);//data transfer from the function is stored about medical record.
    if(returnvalu==0){
    for(size_t i=0;i<record.size();i++){
            system("cls");
            cout<<"\n\n\n\n";
            cout<<GREEN<<Bold<< "\n\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET;
            cout<<YELLOW<<"\n\t\t\t\t\t* * * * * * * * * * * * *[View Medical Record] * * * * * * * * * * * *"<<RESET<<endl;
            cout<<RED<<"\n\t\t\t\t\t\t\t        Diagnoses\t\t:"<<RESET<<BrightWhite<<reversedocupdates(record[i].diagnosis)<<RESET;
            cout<<RED<<"\n\t\t\t\t\t\t\t        Medical Prescribed\t:"<<RESET<<BrightWhite<<reversedocupdates(record[i].prescribed)<<RESET;
            cout<<RED<<"\n\t\t\t\t\t\t\t        Additional Recommendation:"<<RESET<<BrightWhite<<reversedocupdates(record[i].additionalRec)<<RESET<<endl;
           cout <<MAGENTA<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<<RESET;

      }
    }
    else if(returnvalu==1){
        //system("cls");
        //cout<<"\n\tPatient Name :"<<patientname;
        cout<<RED<<Bold<< "\n\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET<<endl;
        cout<<YELLOW<<"\n\t\t\t\t\t    * * * * * * * * * * * * *[No Medical Record] * * * * * * * * * * * *"<<RESET<<endl;
        cout<<RED<<Bold<< "\n\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET;
    }
    this_thread::sleep_for(chrono::seconds(3));
                 cout<<BrightWhite<<"\n\t\t\t\tDo you need to continue[Y/N]: "<<RESET;
                while (!(cin >> authletter) || !(authletter=='n' || authletter=='y' || authletter=='N' || authletter=='Y') ||(isdigit(authletter)))
                        {
                            cout<<RED<<Bold<<"\n\t\t\t\t-----------------------------------------------------------------------------------------------------"<<RESET;
                            cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid option letter[Y/N]: "<<RESET;
                            cin.clear();                // Clear the error flag
                            cin.ignore(INT_MAX, '\n'); // Discard invalid input
                        }
              if(authletter=='y' || authletter =='Y'){
                backcode=0;
              }
              else{
                backcode=3;
              }
    system("cls");
}while(backcode==0);
    return backcode;





}


/**UPDATING MEDICAL RECORD FUNCTION**/

vector<PatientMedicalRecord> updaterecordfile(){///pass current stored data in the medical file to the [updatefunction]
    vector<PatientMedicalRecord>storepatientname;
    ifstream read;
    read.open("patientmedicalrec.txt");
    if(read.is_open()){
        PatientMedicalRecord Medirec;
            while(read>>Medirec.patientname>>Medirec.diagnosis>>Medirec.prescribed>>Medirec.additionalRec){
                    storepatientname.push_back(Medirec);

            }
      return storepatientname;
      read.close();

    }
    else{
        cerr<<"\n\tUnable To Open The File";
    }
}

int validatedofcreatingnewrecord(string patientnam){///this file read[medical record file] inorder to check whether patient alreadly created a record
    ifstream read;
    read.open("patientmedicalrec.txt");
    if(!read.is_open()){
        return 2;
        }
    int num;
         PatientMedicalRecord pMed;
        while(read>>pMed.patientname>>pMed.diagnosis>>pMed.prescribed>>pMed.additionalRec){//pass data in the file to struct variable name
            if(pMed.patientname==patientnam){//check whether pass user from function match with the file username.
                num=0;
                break;
            }
            else{
                num=1;
            }
        }

    return num;
    read.close();



}

int PatientMednewrecords( string patientname){///when record created for new patient
    int returnval=0;
    int backcode=0;
    char authletter;
    vector<PatientMedicalRecord>medicalrec;
    medicalrec.clear();//use to clear existing data in the file
    PatientMedicalRecord Medirec[numberofstruct];

    int rowcount=rowreadfile("patientmedicalrec.txt");
    system("cls");
     cout<<"\n\n\n\n";
     cout <<MAGENTA<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
     cout<<YELLOW<<"\n\t\t\t\t\t   * * * * * * * * * * * * *[Update "<<RESET<<RED<<reverseusername(patientname)<<RESET<<YELLOW<<" Records] * * * * * * * * * * * *"<<RESET<<endl;
    for(int i=rowcount;i<rowcount+1;i++){
            Medirec[i].patientname=patientname;

            cout<<BrightWhite<<"\n\t\t\t\tEnter Patient's Diagnosis\t: "<<RESET;
            cin.ignore();// chech for.
            getline(cin,Medirec[i].diagnosis);
            Medirec[i].diagnosis=removespace(Medirec[i].diagnosis);


            cout<<BrightWhite<<"\n\t\t\t\tEnter Patient's Prescribed Medication : "<<RESET;
            getline(cin,Medirec[i].prescribed);
            Medirec[i].prescribed=removespacedocupdates(Medirec[i].prescribed);

            cout<<BrightWhite<<"\n\t\t\t\tEnter Patient's Additional Recommendation: "<<RESET;
            getline(cin,Medirec[i].additionalRec);
            Medirec[i].additionalRec=removespacedocupdates(Medirec[i].additionalRec);

             medicalrec.push_back(Medirec[i]);
             returnval=writenewpatientmedrecord(medicalrec);
               if(returnval==0){
                    cout<<YELLOW<<"\n\t\t\t\t\t    * * * * * * * * * * * * *[Data is Successfully Updated] * * * * * * * * * * * *"<<RESET<<endl;
                    cout <<MAGENTA<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
                   }
                   else{
                    cout<<YELLOW<<"\n\t\t\t\t\t    * * * * * * * * * * * * *[Data is Unable to Updated] * * * * * * * * * * * *"<<RESET<<endl;
                    cout <<MAGENTA<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";

                   }
               cout<<BrightWhite<<"\n\t\t\t\tDo you need to continue[Y/N]: "<<RESET;
                while (!(cin >> authletter) || !(authletter=='n' || authletter=='y' || authletter=='N' || authletter=='Y') ||(isdigit(authletter)))
                        {
                             cout<<RED<<Bold<<"\n\t\t\t\t-----------------------------------------------------------------------------------------------------"<<RESET;
                            cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid option letter[Y/N]: "<<RESET;
                            cin.clear();                // Clear the error flag
                            cin.ignore(INT_MAX, '\n'); // Discard invalid input
                        }
              if(authletter=='y' || authletter =='Y'){
                backcode=0;
              }
              else{
                backcode=3;
              }
         return backcode;
    }
}

int PatientMedexistrecords( string patientname, vector<PatientMedicalRecord> &preupdate,int enternum){///Updating file of the medical record
    int returnval=0;
    int backcode=0;
    char authletter;
    vector<PatientMedicalRecord>medicalrec;
    medicalrec.clear();
    PatientMedicalRecord Medirec[numberofstruct];
    int j=enternum;//storing the vector index brought from[update function]
    int rowcount=rowreadfile("patientmedicalrec.txt");
    system("cls");
      cout<<"\n\n\n\n";
     cout <<MAGENTA<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
     cout<<YELLOW<<"\n\t\t\t\t\t   * * * * * * * * * * * * *[Update "<<RESET<<RED<<reverseusername(patientname)<<RESET<<YELLOW<<" Records] * * * * * * * * * * * *"<<RESET<<endl;


    for(int i=rowcount;i<rowcount+1;i++){
            Medirec[i].patientname=patientname;
            preupdate[j].patientname=Medirec[i].patientname;///replacing the relevants patients details with the newly updated details

            cout<<BrightWhite<<"\n\t\t\t\tEnter Patient's Diagnosis\t: "<<RESET;
            cin.ignore();
            getline(cin,Medirec[i].diagnosis);
            Medirec[i].diagnosis=removespace(Medirec[i].diagnosis);
            preupdate[j].diagnosis=Medirec[i].diagnosis;

            cout<<BrightWhite<<"\n\t\t\t\tEnter Patient's Prescribed Medication : "<<RESET;
            getline(cin,Medirec[i].prescribed);
            Medirec[i].prescribed=removespacedocupdates(Medirec[i].prescribed);
            preupdate[j].prescribed=Medirec[i].prescribed;


            cout<<BrightWhite<<"\n\t\t\t\tEnter Patient's Additional Recommendation: "<<RESET;
            getline(cin,Medirec[i].additionalRec);
            Medirec[i].additionalRec=removespacedocupdates(Medirec[i].additionalRec);
            preupdate[j].additionalRec=Medirec[i].additionalRec;


             medicalrec.push_back(Medirec[i]);


     cout<<GREEN<<Bold<< "\n\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET;
      returnval=writeupdatepatientmedrecord(preupdate);///pass vector which store the replace data to file handling function to write
          if(returnval==0){

                    cout<<YELLOW<<"\n\t\t\t\t\t    * * * * * * * * * * * * *[Data is Successfully Updated] * * * * * * * * * * * *"<<RESET<<endl;
                    cout <<MAGENTA<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";


                   }
                   else{
                    cout<<YELLOW<<"\n\t\t\t\t\t    * * * * * * * * * * * * *[Data is Unable to Updated] * * * * * * * * * * * *"<<RESET<<endl;
                    cout <<MAGENTA<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";

                   }
                this_thread::sleep_for(chrono::seconds(3));
                cout<<BrightWhite<<"\n\t\t\t\tDo you need to continue[Y/N]: "<<RESET;
                while (!(cin >> authletter) || !(authletter=='n' || authletter=='y' || authletter=='N' || authletter=='Y') ||(isdigit(authletter)))
                        {
                            cout<<RED<<Bold<<"\n\t\t\t\t-----------------------------------------------------------------------------------------------------"<<RESET;
                            cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid option letter[Y/N]: "<<RESET;
                            cin.clear();                // Clear the error flag
                            cin.ignore(INT_MAX, '\n'); // Discard invalid input
                        }
              if(authletter=='y' || authletter =='Y'){
                backcode=0;
              }
              else{
                backcode=3;
              }
         return backcode;
    }
}

int Updaterecord(){///completed
    int enternum=0;
    int backcode;
    vector<PatientMedicalRecord>appoint;
 do{
    appoint.clear();
     cout<<"\n\n\n\n";
     cout <<MAGENTA<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
     cout<<YELLOW<<"\n\t\t\t\t\t   * * * * * * * * * * * * *[Existing Patient Records List] * * * * * * * * * * * *"<<RESET<<endl;
    appoint=updaterecordfile();
    for(size_t j=0;j<appoint.size();j++){
        cout<<BrightWhite<<"\n\t\t\t\t\t\t        "<<j+1<<". "<<reverseusername(appoint[j].patientname)<<endl;
        }
       cout<<GREEN<<Bold<< "\n\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET<<endl;
       cout<<BrightWhite<<"\n\t\t\t\tEnter the Option Number(1/2..)]/[Backcode-0]\t: "<<RESET;
        while (!(cin >>enternum) || !(enternum>=0 && enternum<=appoint.size()+1) ||(isalpha(enternum)))//input validation
        {
            cout<<RED<<Bold<<"\n\t\t\t\t-----------------------------------------------------------------------------------------------------"<<RESET;
            cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid option number(1/2..)]/[Backcode-0]: "<<RESET;
            cin.clear();             // Clear the error flag
            cin.ignore(INT_MAX, '\n'); // Discard invalid input
                }

        if(enternum !=0){
        enternum=enternum-1;
        backcode=PatientMedexistrecords(removespace(appoint[enternum].patientname),appoint,enternum);//data transfer to the function mention in order to update
        }
        else{
          backcode =3;//assign inorder to terminate a loop
        }
     system("cls");
}while(backcode==0);

        return backcode;


}

int docupdatepatientreport(string username){///completed
    int enternum=0,usernum=0,backcode=0;
    vector<docupdatelist>appoint;
do{
    appoint.clear();
    appoint=ReaddDocUpdatePatientList(username);//store the doctor patient list return from the function
    vector<PatientMedicalRecord>patientupd;//null vector
    cout<<"\n\n\n\n";
     cout <<MAGENTA<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
     cout<<YELLOW<<"\n\t\t\t\t\t   * * * * * * * * * * * * *[Patient Medical Records] * * * * * * * * * * * *"<<RESET<<endl;
     cout<<BrightWhite<<"\n\t\t\t\t\t\t\t        1.Create a Medical Record To New Patient"<<RESET<<endl;
     cout<<BrightWhite<<"\n\t\t\t\t\t\t\t        2.Update a Patient Medical Record"<<RESET<<endl;
     cout<<BrightWhite<<"\n\t\t\t\t\t\t\t        3.Back to menu"<<RESET<<endl;
     cout<<GREEN<<Bold<< "\n\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET;
     cout<<BrightWhite<<"\n\t\t\t\tEnter the Option Number\t: "<<RESET;

    while (!(cin >>usernum) || !(usernum>0 && usernum<=3) ||(isalpha(usernum)))//input validation
        {
            cout<<RED<<Bold<<"\n\t\t\t\t-----------------------------------------------------------------------------------------------------"<<RESET;
            cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid option number[1-3]: "<<RESET;
            cin.clear();             // Clear the error flag
            cin.ignore(INT_MAX, '\n'); // Discard invalid input
                }


    if(usernum==1){
            system("cls");
            cout<<"\n\n\n\n";
            cout <<MAGENTA<<"\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
            cout<<YELLOW<<"\n\t\t\t\t\t   * * * * * * * * * * * * *[Patient List] * * * * * * * * * * * *"<<RESET<<endl;
            for(size_t j=0;j<appoint.size();j++){//display list of patient related to appointment
                cout<<BrightWhite<<"\n\t\t\t\t\t\t        "<<j+1<<". "<<reverseusername(appoint[j].patientname)<<endl;
                }
            cout<<GREEN<<Bold<< "\n\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET<<endl;
            cout<<BrightWhite<<"\n\t\t\t\tEnter the Option Number(1/2..)]/[Backcode-0]\t: "<<RESET;

            while (!(cin >>enternum) || !(enternum>=0 && enternum<=appoint.size()+1 ) ||(isalpha(enternum)))//input validation
             {
            cout<<RED<<Bold<<"\n\t\t\t\t-----------------------------------------------------------------------------------------------------"<<RESET;
            cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid option number(1/2..)]/[Backcode-0]: "<<RESET;
            cin.clear();             // Clear the error flag
            cin.ignore(INT_MAX, '\n'); // Discard invalid input
                }

            if(enternum !=0){
                    enternum=enternum-1;
               if(validatedofcreatingnewrecord(removespace(appoint[enternum].patientname))==1){//check whether newly creating medrecord already being created or not
                     backcode=PatientMednewrecords(removespace(appoint[enternum].patientname));//if condition is satisfied transfer data to [patientMednewrecord] func

            }
            else{

                    cout<<RED<<Bold<< "\n\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET<<endl;
                    cout<<YELLOW<<"\n\t\t\t\t\t    * * * * * * * * * * * * *[Already Medical Record Exist] * * * * * * * * * * * *"<<RESET<<endl;
                    cout<<RED<<Bold<< "\n\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET;

                    this_thread::sleep_for(chrono::seconds(4));
                   cout<<BrightWhite<<"\n\t\t\t\tBack to Menu[code-0]\t: "<<RESET;
                    while (!(cin >>backcode) || !(backcode==0) ||(isalpha(backcode)))//input validation
                         {
                        cout<<RED<<Bold<<"\n\t\t\t\t-----------------------------------------------------------------------------------------------------"<<RESET;
                        cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid option number[Backcode-0]: "<<RESET;
                        cin.clear();             // Clear the error flag
                        cin.ignore(INT_MAX, '\n'); // Discard invalid input
                            }

              }
            }
            else{
                system("cls");
                backcode=0;//docupdatepatientreport(username);
            }



        }
        else if(usernum==2){
             system("cls");
             int returncode=Updaterecord();
             do{
             if(returncode==3){//check whether excatly user need to move to front page or not.
                system("cls");
                backcode=docupdatepatientreport(username);
             }
           }while(backcode !=3);



        }
        else{
            backcode=3;
        }
     system("cls");
}while(backcode==0);

        return backcode;




}






