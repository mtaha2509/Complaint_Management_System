/**
 * Project Untitled
 */


#ifndef _EMPLOYEES_H
#define _EMPLOYEES_H
#include "EInterface.h"
#include "User.h"
#include "Observer.h"
#include <vector>
class Department;
class Job;

class Employees: public User , public EInterface{
	vector<Observer*> managersObservers;;
	string Id, status;
	Job* job;
	Department* dept;
public:
	void Print();
	void SetDepartment(Department* department);
	Employees(std::string id,string s, std::string lname, std::string fname, int age, Department* department);
	Employees();
	string get_status();
	string getId() const;
	void setstatus(string s);
	void getter(string &id, string &dept, string &status, string &fname, string &lname, int &age);
	void Set_Job(Job* j);
	void GetJobDetails();
	int get_complainID();
	void job_resolved(int);
	void Notify(int id);
	string get_status() const;
	Department* get_d_name();
	void DeleteJob(Job* job);
	bool FindJob(Job* job);
	void addManagerObserver(Observer* observer) {
		managersObservers.push_back(observer);
	}

	// Notify managers when a new notification is added
	void notifyManagers(int notificationID) {
		for (auto observer : managersObservers) {
			observer->update(notificationID);
		}
	}
};

#endif //_EMPLOYEES_H