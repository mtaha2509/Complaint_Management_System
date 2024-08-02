#pragma once
#include <string>
using namespace std;
class Department;
class Job;

class EInterface {
public:
    virtual void Print() = 0;
    virtual void SetDepartment(Department* department) = 0;
    virtual string get_status() = 0;
    virtual string getId() const = 0;
    virtual void setstatus(string s) = 0;
    virtual void getter(string& id, string& dept, string& status, string& fname, string& lname, int& age) = 0;
    virtual void Set_Job(Job* j) = 0;
    virtual void GetJobDetails() = 0;
    virtual int get_complainID() = 0;
    virtual void job_resolved(int) = 0;
    virtual void Notify(int id) = 0;
    virtual string get_status() const = 0;
    virtual Department* get_d_name() = 0;
    virtual void DeleteJob(Job* job) = 0;
    virtual bool FindJob(Job* job) = 0;

};