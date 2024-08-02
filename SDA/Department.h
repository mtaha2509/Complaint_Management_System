#ifndef _DEPARTMENT_H
#define _DEPARTMENT_H

#include "DepartmentNames.h"
#include <list>
#include<string>
#include "States.h"
#include <memory>
using namespace std;

class Complaint;
class Manager;
class Employees;

class Department {
    std::list<Employees*> emp;
    Manager* mgr;
    std::list<Complaint*> complaints;

public:
    DepartmentNames Dept;
    Department();
    Department(DepartmentNames name);
    void SetDept(DepartmentNames name);
    void AddComplaint(Complaint* complaint);
    void PrintComplaints();
    void SetManager(Manager* manager);
    void setEmployee(Employees* emp);
    void Print();
    DepartmentNames getDept();
    Manager* GetManager() const;
    void AddEmployee(Employees* employee);
    const list<Complaint*>& GetComplaints() const;
    list<Employees*> getEmployees();
    void UpdateEmployee(string id);
    void UpdateComplaint(int id);
    void PrintComplaint(int id);
    void set_complaint_status_by_id(int);
    void Notify(int Id);
    void new_set(Manager* manager);
    int getComplaintNumbers();
    void PrintManager();
    void DisplayComplaintIDandStatus();
    void PrintComplaintDate_Status_Des(int id);
    void PrintTeacher(int id);
    void PrintManagerAndEmployees(int id);
    void PrintJobDate(int id);
    bool HasEmployee(const std::string& employeeID) const;
    void RemoveEmployee(const std::string& employeeID);
};

#endif //_DEPARTMENT_H
