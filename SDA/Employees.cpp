/**
 * Project Untitled
 */


#include "Employees.h"
#include "Department.h"
#include "Job.h"

string Dept_Tostring(DepartmentNames s);
Employees::Employees(std::string id, string s, std::string fname, std::string lname, int age, Department* department) {
    Id = id;
    status = s;
    Usetter(fname, lname, age);
    dept = department;
}
void Employees::Print()
{
    cout << "ID: " << Id << endl;
    string fname, lname;
    int age;
    Ugetter(fname, lname, age);
    cout << "Name: " << fname << " " << lname << endl;
    cout << "Age: " << age << endl;
    std::cout << "-------------------------\n";
}
void Employees::SetDepartment(Department* department) {
    dept = department;
}

Employees::Employees()
{
	Id = '\0';
}

string Employees::get_status() {
    return status;
}

string Employees::getId() const
{
    return Id;
}

void Employees::setstatus(string s)
{
    status = s;
}

void Employees::Set_Job(Job* j)
{
    this->job = j;
}
void Employees::GetJobDetails()
{
    if (status == "A") {
        cout << "Here is the Job Assigned to You:\n";
        std::cout << "-------------------------\n";
        job->PrintDetails();
    }
    else {
        std::cout << "-------------------------\n";
        cout << "No Job has been Assigned to You.\n";
        std::cout << "-------------------------\n";
    }
}
void Employees::getter(string& id, string& dept, string& status, string& fname, string& lname, int& age)
{
    Ugetter(fname, lname, age);
    status = this->status;
    id = this->Id;
    dept = Dept_Tostring(this->dept->getDept());
}

int Employees::get_complainID() {
    return job->get_id();
}

void Employees::job_resolved(int id) {
    dept->set_complaint_status_by_id(id);
}

void Employees::Notify(int id)
{
    job->Notify(id);
}

string Employees::get_status() const
{
    return status;
}

Department* Employees::get_d_name()
{
    return dept;
}

void Employees::DeleteJob(Job* job)
{
    //delete this->job;
    this->status = "NA";
    this->job = nullptr;
}

bool Employees::FindJob(Job* job)
{
    if (this->job == job) {
        return true;
    }
    else {
        return false;
    }
}
