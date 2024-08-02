/**
 * Project Untitled
 */


#ifndef _JOB_H
#define _JOB_H
#include <list>
#include <string>
#include<ctime>
#include "Date.h"
using namespace std;

class Manager;
class Employees;
class Date;

class Job {
	list<Employees*> emp;
	Manager* mgr;
	int Id;
	Date date;
public:
	Job();
	Job(int id, Employees* emp, Manager* mgr);
	void PrintDetails();
	int get_id();
	list<Employees*> get_job_emp_id();
	void SetDate(Date& d);
	void Notify(int id);
	void printEmployees();
	void PrintDate();
	bool RemoveEmployee(const std::string& employeeID);
	int NoOfEmp();
	string getManagerID();
	
};

#endif //_JOB_H