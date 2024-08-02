/**
 * Project Untitled
 */


#ifndef _MANAGER_H
#define _MANAGER_H

#include "User.h"
#include "DepartmentNames.h"
#include "MInterface.h"
#include "Observer.h"
#include <vector>
#include<list>

class Department;
class Job;

class Manager : public User, public MInterface, public Observer {
	list<Job*> job;
	Department* dept;
	string ID;
	list<int> Notification;
	vector<Observer*> teachersObservers;
public:
	Manager() : User() { ID = '\0'; };
	Manager(string fname, string lname, int age, string id) : User(fname, lname, age) {
		ID = id;
	}
	void notifyTeachers(int notificationID);
	void addTeacherObserver(Observer* observer);
	void SetDepartment(Department& department);
	virtual void update(int notificationID) override;
	//void Msetter(string fname, string lname, int age, string ID, string dept);
	void MPrint();
	string MgetID() const;
	void getComplaintById(int id);
	bool DisplayNewComplaints();
	void Msetter(string fname, string lname, int age, string ID, Department* department);
	int DisplayEmployees();
	void assign_complaint(int id);
	void assign_employee(string);
	void Set_Job(Job* j);
	void DisplayAllComplaints();
	int NumberOfNewComplaints();
	void AddNotification(int id);
	int getNotifications();
	void PrintNotification();
	void RemoveNotification(int id);
	void Notify(int id);
	string MgetFname() const;
	string MgetLname() const;
	int MgetAge() const;
	DepartmentNames getDept() const;
	void PrintAssignedEmployees(int id);
	void printJobByID(int);
	void PrintJobDate();
	bool RemoveJobIfBelongsToManager(Job* job);
	Manager* getMgr();
};

#endif //_MANAGER_H