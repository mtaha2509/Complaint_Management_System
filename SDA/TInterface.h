#pragma once
#include<iostream>
#include<list>
using namespace std;
class Complaint;
class Department;
class TInterface {
public:
    virtual void Tsetter(std::string fname, std::string lname, int age, std::string ID) = 0;
    virtual void Print() = 0;
    virtual std::string getID() const = 0;
    virtual Complaint* SetComplaint(std::string des, std::string dept, std::string status, std::list<Department>& departments, int id, string t) = 0;
    virtual Complaint* file_complaint(std::list<Department>& departments, int id) = 0;
    virtual void Setcomplaint(Complaint* cmp) = 0;
    virtual void UpdateFile(string des, string dept, string status, string t) = 0;
    virtual void AddNotification(int ID) = 0;
    virtual void RemoveNotification(int ID) = 0;
    virtual void PrintNotification() = 0;
    virtual int getNotifications() = 0;
    virtual void UpdateComplaint(int id) = 0;
    virtual void DisplayInfo() = 0;
};