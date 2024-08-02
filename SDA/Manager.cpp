#include "Manager.h"
#include "Department.h"
#include "Complaint.h"
#include "Employees.h"
#include "Job.h"

string StateTostring(Status s);

void Manager::Msetter(string fname, string lname, int age, string ID, Department* department) {
	Usetter(fname, lname, age);
	this->ID = ID;
	// Associate the manager with the provided department
	this->SetDepartment(*department);
}

void Manager::notifyTeachers(int notificationID)
{
    for (auto observer : teachersObservers) {
        observer->update(notificationID);
    }
}

void Manager::addTeacherObserver(Observer* observer)
{
    teachersObservers.push_back(observer);
}

void Manager::SetDepartment(Department& department) {
	dept = &department;
}

void Manager::update(int notificationID)
{
    AddNotification(notificationID);

    // Notify teachers about the new notification
    notifyTeachers(notificationID);
}


void Manager::MPrint()
{
	string fname, lname;
	int age;
	Ugetter(fname, lname, age);
	cout << "ID: " << this->ID << endl;
	cout << "Name: " << fname << " " << lname << endl;
	cout << "Age: " << age << endl;

}

string Manager::MgetID() const
{
	return ID;
}

void Manager::getComplaintById(int id)
{
    dept->PrintComplaint(id);
}

int Manager::DisplayEmployees()
{
    list<Employees*> emp = dept->getEmployees();
    int e = 0;
    for (auto it = emp.begin(); it != emp.end(); ++it) {
        if ((*it)->get_status() == "NA") {
            if (e == 0) {
                cout << "Available Employees:\n";
            }
            (*it)->Print(); e++;
            std::cout << "-------------------------\n";
        }
    }
    return e;
}
// Add the implementation for DisplayNewComplaints
bool Manager::DisplayNewComplaints() {
    bool check = false;
    std::cout << "New Complaints in your department:\n";
    if (dept != nullptr) {
        const std::list<Complaint*>& complaints = dept->GetComplaints();
        std::cout << "-------------------------\n";
        for (const auto& complaint : complaints) {
            if (complaint->GetStatus() == Status::NEW) {
                check = true;
                complaint->Complain_print();
            }
        }
       
    }
    else {
        std::cout << "Error: Manager not associated with any department.\n";
    }
    return check;
}

void Manager::assign_complaint(int id) {
    dept->UpdateComplaint(id);
}

void Manager::Set_Job(Job* j)
{
    job.push_back(j);
}

void Manager::assign_employee(string id) {
    dept->UpdateEmployee(id);
}

void Manager::DisplayAllComplaints() {
    std::cout << "Complaints history in your department:\n";
    int i = 0;
    if (dept != nullptr) {
        const std::list<Complaint*>& complaints = dept->GetComplaints();
        for (const auto& complaint : complaints) {
            complaint->Complain_print();
            cout << "Status: " << StateTostring(complaint->GetStatus()) << endl;
            std::cout << "-------------------------\n";
            i++;
        }

    }
    else {
        std::cout << "Error: Manager not associated with any department.\n";
    }
}

int Manager::NumberOfNewComplaints() {
    int i = 0;
    if (dept != nullptr) {
        const std::list<Complaint*>& complaints = dept->GetComplaints();
        for (const auto& complaint : complaints) {
            if (complaint->GetStatus() == Status::NEW) {
                i++;
            }
        }
        return i;

    }
    else {
        std::cout << "Error: Manager not associated with any department.\n";
    }
}

void Manager::AddNotification(int id)
{
    Notification.push_back(id);
}
int Manager::getNotifications()
{
    return Notification.size();
}

void Manager::PrintNotification()
{
    cout << "The Following Complaints Have Been Worked Upon:-\n";
    std::cout << "-------------------------\n";
    for (auto& value : Notification) {
        dept->PrintComplaint(value);
    }
    std::cout << "-------------------------\n";
}

void Manager::RemoveNotification(int id) {
    Notification.remove_if([id](int value) { return value == id; });
}

void Manager::Notify(int id)
{
    dept->Notify(id);
}

string Manager::MgetFname() const
{
    return UgetFname();
}

string Manager::MgetLname() const
{
    return UgetLname();
}

int Manager::MgetAge() const
{
    return UgetAge();
}

DepartmentNames Manager::getDept() const
{
    return dept->getDept();
}

void Manager::PrintAssignedEmployees(int id)
{
    for (auto& j : job) {
        if (j->get_id() == id)
        {
            j->printEmployees();
        }
    }
}

void Manager::printJobByID(int id)
{
    std::cout << "-------------------------\n";
    int i = 1;
    for (auto& j : job) {
        if (j->get_id() == id)
        {
            cout << "[" << i << "] ";
            j->PrintDate();
            i++;
        }
    }
    std::cout << "-------------------------\n";
}

void Manager::PrintJobDate()
{
    std::cout << "-------------------------\n";
    for (auto& j : job) {
        j->PrintDate();
    }
    std::cout << "-------------------------\n";
}

bool Manager::RemoveJobIfBelongsToManager(Job* j)
{
    auto it = std::find(job.begin(), job.end(), j);
    if (it != job.end()) {
        job.erase(it);
        //std::cout << "Job removed from the manager.\n";
        return true;  // Job was successfully removed
    }
    return false;  // Job was not found
}

Manager* Manager::getMgr()
{
    return this;
}

