#ifndef _COMPLAINT_H
#define _COMPLAINT_H

#include "States.h"
#include <string>
#include <iostream>
#include "Department.h"
#include "Date.h";
using namespace std;

class Teacher; // Forward declaration
class Date;

class Complaint {
    std::string description;
    Teacher* teacher;
    Department* department;
    Status state;
    int CID;
    Date date ;
public:
    Complaint(std::string des, Teacher* t, Department* d, std::string status, int ID);
    //Complaint(std::string des, std::string name, std::string status);
    void C_setter(std::string des);
    void Complain_print();
    Status GetStatus();
    int getCID();
    void SetStatus(Status s);
    string T_ID_getter();
    DepartmentNames getdept();
    string getdescription();
    void Notify();
    void setDate(Date& d);
    string getMonth() ;
    int getYear() ;
    int getDate() ;
    void PrintIDandStatus();
    void printDate_Status_Des();
    void PrintTeacher();
    string getdate();
    
};

#endif //_COMPLAINT_H
