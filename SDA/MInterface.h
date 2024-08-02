#pragma once
#include<iostream>
#include"DepartmentNames.h"
using namespace std;

class Department;
class Job;
class Manager;
class MInterface {
public:
	virtual void SetDepartment(Department& department) = 0;
	//virtual void Msetter(string fname, string lname, int age, string ID, string dept) = 0;
	virtual void MPrint() = 0;
	virtual string MgetID() const = 0;
	virtual void getComplaintById(int id) = 0;
	virtual bool DisplayNewComplaints() = 0;
	virtual void Msetter(string fname, string lname, int age, string ID, Department* department) = 0;
	virtual int DisplayEmployees() = 0;
	virtual void assign_complaint(int id) = 0;
	virtual void assign_employee(string) = 0;
	virtual void Set_Job(Job* j) = 0;
	virtual void DisplayAllComplaints() = 0;
	virtual int NumberOfNewComplaints() = 0;
	virtual void AddNotification(int id) = 0;
	virtual int getNotifications() = 0;
	virtual void PrintNotification() = 0;
	virtual void RemoveNotification(int id) = 0;
	virtual void Notify(int id) = 0;
	virtual string MgetFname() const = 0;
	virtual string MgetLname() const = 0;
	virtual int MgetAge() const = 0;
	virtual DepartmentNames getDept() const = 0;
	virtual void PrintAssignedEmployees(int id) = 0;
	virtual void printJobByID(int) = 0;
	virtual void PrintJobDate() = 0;
	virtual bool RemoveJobIfBelongsToManager(Job* job) = 0;
	virtual Manager* getMgr() = 0;
};