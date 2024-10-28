#ifndef PATIENTFUNCTIONHEADER_H_INCLUDED
#define PATIENTFUNCTIONHEADER_H_INCLUDED

#include <string.h>
#include <fstream>
#include <conio.h>
#include <thread>

using namespace std;
struct appointmentstruct {

   string docname;
   string apptime;
   string days;
   string patientname;
   string status;
   string mobilenum;
   int patientno;
};


string reverseusername(string name);
int DoctorList(string);
void AccessPatientRecord();
int  appointmentcancel(string);
void patientdetailsfile(string);
int updatepersonalinfo(string);
int patienthomepg(string);
int viewrecords(string );



#endif // PATIENTFUNCTIONHEADER_H_INCLUDED
