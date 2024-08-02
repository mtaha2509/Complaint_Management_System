#include "Job.h"
#include "Manager.h"
#include "Employees.h"
#include <string>
#include <algorithm>

Job::Job() {

}

Job::Job(int id, Employees* emp, Manager* mgr)
{
	this->Id = id;
	this->emp.push_back(emp);
	this->mgr = mgr;
}

void Job::PrintDetails()
{
	mgr->getComplaintById(this->Id);
	cout << "Assigned to you by the manager: " << mgr->MgetID()<<endl;
	std::cout << "-------------------------\n";
}

int Job::get_id()
{
	return Id;
}

list<Employees*> Job::get_job_emp_id() {
	return emp;
}

void Job::SetDate(Date& d)
{
	date = d;
}

void Job::Notify(int id)
{
	mgr->AddNotification(id);
}

void Job::printEmployees()
{
	for (auto& e : emp) {
		e->Print();
	}
}

void Job::PrintDate()
{
	date.Print();
}

bool Job::RemoveEmployee(const std::string& employeeID)
{
	auto it = std::remove_if(emp.begin(), emp.end(), [employeeID](const Employees* employee) {
		return employee->getId() == employeeID;
		});

	// Determine if an employee was removed
	bool employeeRemoved = (it != emp.end());

	// Erase the removed employees from the list
	//emp.erase(it, emp.end());

	return employeeRemoved;
}

int Job::NoOfEmp()
{
	return emp.size();
}

string Job::getManagerID()
{
	return mgr->MgetID();
}
