#include "Complaint.h"
#include "Department.h"
#include "Teacher.h"

string Dept_Tostring(DepartmentNames s);
string StateTostring(Status s);

Complaint::Complaint(std::string des, Teacher* t, Department* d, std::string status, int id)
    : description(des), teacher(t), department(d) {
    if (status == "Resolved") {
        state = RESOLVED;
    }
    else if (status == "Assigned") {
        state = ASSIGNED;
    }
    else if (status == "New") {
        state = NEW;
    }
    this->CID = id;
}

void Complaint::C_setter(std::string des) {
    description = des;
}

void Complaint::Complain_print() {
    
    cout << "Complaint ID: " << CID << endl;
    cout << "Status: " << StateTostring(state) << endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Initiated By: " << teacher->getID() << std::endl; 
    cout << "Belongs to Department: " << Dept_Tostring(department->getDept()) << endl;
    cout << "Complaint Filed Date: ";
    date.Print();
    std::cout << "-------------------------\n";
}

Status Complaint::GetStatus() {
    return state;
}

int Complaint::getCID()
{
    return CID;
}

void Complaint::SetStatus(Status s)
{
    this->state = s;
}

string Complaint::T_ID_getter() {
    return teacher->getID();
}

DepartmentNames Complaint::getdept()
{
    return department->getDept();
}

string Complaint::getdescription()
{
    return description;
}

void Complaint::Notify()
{
    teacher->AddNotification(this->CID);
}

void Complaint::setDate(Date& d)
{
    date = d;
}

string Complaint::getMonth() 
{
    return date.getMonth();
}

int Complaint::getYear() 
{
    return date.getYear();
}

int Complaint::getDate() 
{
    return date.getDate();
}

void Complaint::PrintIDandStatus()
{
    cout << "Complaint ID: " << CID << endl;
    cout << "Status: " << StateTostring(state) << endl;
}

void Complaint::printDate_Status_Des()
{
    cout << "Filed Date: ";
    date.Print();
    cout << "Status: " << StateTostring(state) << endl;
    cout << "Description: " << description << endl;
    std::cout << "-------------------------\n";
}

void Complaint::PrintTeacher()
{
    std::cout << "-------------------------\n";
    cout << "Initiated By: "<<endl;
    teacher->DisplayInfo();
    std::cout << "-------------------------\n";
}

string Complaint::getdate()
{
    return date.getdate();
}

