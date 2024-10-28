#include <iostream>
#include "authenticationfunc.h"
#include "patientfunctionheader.h"
#include "doctorfunctionheader.h"
#include "colorheader.h"
#include <stdio.h>
#include <cstdlib>
using namespace std;

int main()
{   char authletter;
    string username="";
    int outnum=0;
    int auth_num1=0,Backcode=0,code=0;
    int auth_num=0;//number from home page
    int firtpgnum;
do{
   firtpgnum=firstpage();
    if(firtpgnum==1){
    do{
        system("cls");
       auth_num=homepg();

    system("cls");
         if(auth_num==1){//home page number checked
               auth_num1=homepg1();//number from sign page
               do{
                        system("cls");
                       signinpg(auth_num,auth_num1,&outnum,&username);


                               if(outnum==0){
                                    cout<<YELLOW<<"\n\n\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * "<<RESET<<MAGENTA<<"LOGIN SUCCESS"<<RESET<<YELLOW<<"* * * * * * * * * * * * * * * * * * * * * * * * *"<<RESET<<endl;
                                      cout<<MAGENTA<< "\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<<RESET;
                                    this_thread::sleep_for(chrono::seconds(6));
                                             if(auth_num1==2){//patient
                                                    system("cls");
                                                  do{
                                                   int patientcode= patienthomepg(username);
                                                   switch(patientcode){
                                                   case 1:
                                                       system("cls");
                                                       Backcode=viewrecords(username);
                                                          break;
                                                   case 2:
                                                    system("cls");
                                                     Backcode=DoctorList(username);
                                                     break;
                                                   case 3:
                                                     system("cls");
                                                     Backcode=appointmentcancel(username);
                                                     break;
                                                   case 4:
                                                      system("cls");
                                                      Backcode=updatepersonalinfo(username);
                                                      break;
                                                   case 5:
                                                       system("cls");
                                                       cout<<"\n\n\n\n\n";
                                                        cout<<RED<<Bold<< "\n\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET<<endl;
                                                        cout<<YELLOW<<"\n\t\t\t\t\t    * * * * * * * * * * * * *[Thank you for using our Servic] * * * * * * * * * * * *"<<RESET<<endl;
                                                        cout<<RED<<Bold<< "\n\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET;
                                                        this_thread::sleep_for(chrono::seconds(4));

                                                        Backcode=5;
                                                       break;

                                                   }
                                                   patientcode=0;
                                                   system("cls");
                                             }while(Backcode==3);
                                }else if(auth_num1==1){
                                             do{
                                                system("cls");
                                                int doctorcode=doctorhomepg(username);

                                                switch(doctorcode){
                                                case 1:
                                                    system("cls");
                                                    Backcode=viewdoctorschedul(username);
                                                    break;
                                                case 2:
                                                    system("cls");
                                                    Backcode=accessPatientRecord();
                                                    break;
                                                case 3:
                                                    system("cls");
                                                    Backcode=docupdatepatientreport(username);
                                                    break;

                                                case 4:
                                                    system("cls");
                                                    Backcode=docMarkAppointment(username);
                                                    break;
                                                case 5:
                                                    system("cls");
                                                    cout<<"\n\n\n\n\n";
                                                    cout<<RED<<Bold<< "\n\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET<<endl;
                                                    cout<<YELLOW<<"\n\t\t\t\t\t    * * * * * * * * * * * * *[Thank you for using our Servic] * * * * * * * * * * * *"<<RESET<<endl;
                                                    cout<<RED<<Bold<< "\n\t\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<RESET;
                                                    this_thread::sleep_for(chrono::seconds(4));

                                                    Backcode=5;
                                                    break;


                                                    }
                                                    doctorcode=0;
                                                   system("cls");
                                                }while(Backcode==3);
                                        }


                                } else if(outnum==1){
                                   cout<<RED<<"\n\n\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * "<<RESET<<MAGENTA<<"INCORRECT USERNAME OR PASSWORD"<<RESET<<RED<<"* * * * * * * * * * * * * * * * * * "<<RESET<<endl;

                                    this_thread::sleep_for(chrono::seconds(2));
                                    cout<<RED<<Bold<< "\n\t\t\t\t-------------------------------------------------------------------------------------------------------------"<<RESET;
                                     cout<<GREEN<<"\n\t\t\t\tDo you Want to Try Again(Y/N):"<<RESET;

                                     while (!(cin >> authletter) || !(authletter=='n' || authletter=='y' || authletter=='N' || authletter=='Y') ||(isdigit(authletter)))
                                                {
                                                    cout<<RED<<Bold<< "\n\t\t\t\t---------------------------------------------------------------------------------------------------------------"<<RESET;
                                                    cout<<RED<<"\n\t\t\t\tInvalid option.Enter a valid Option[Y/N]:"<<RESET;

                                                    cin.clear();                // Clear the error flag
                                                    cin.ignore(INT_MAX, '\n'); // Discard invalid input
                                                }

                                     system("cls");
                                 }
                                 else{
                                    continue;
                                 }
                    }while(authletter=='y' || authletter=='Y');
            }
                else if(auth_num==2){
                    auth_num1=homepg1();
                     system("cls");
                      signuppage(auth_num1);
                       // system("cls");
                       this_thread::sleep_for(chrono::seconds(2));
                       outnum=3;
            }
                else{
                        cout<<"invalid";
                        return 0;
                }
                system("cls");


        }while((code==2)||(auth_num1==3) || (outnum==3)||(authletter=='n' )|| (authletter=='N'));
    }

}while(Backcode==5);

  return 0;
}


