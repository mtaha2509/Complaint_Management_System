#include "Department.h"
#include "Complaint.h"
#include "Employees.h"
#include "Manager.h"


string Dept_Tostring(DepartmentNames dept);

Department::Department() {
}

Department::Department(DepartmentNames name) : Dept(name) {
}

void Department::SetDept(DepartmentNames name) {
    this->Dept = name;
}

void Department::AddComplaint(Complaint* complaint) {
    complaints.push_back(complaint);
}

void Department::PrintComplaints() {
    for (auto& complaint : complaints) {
        complaint->Complain_print();
    }
}
void Department::PrintComplaint(int id) {
    for (const auto& complaint : complaints) {
        if (complaint->getCID() == id) {
            complaint->Complain_print();
            return;  // Assuming each complaint has a unique ID
        }
    }
    std::cout << "Complaint with ID " << id << " not found." << std::endl;
}
void Department::set_complaint_status_by_id(int id) {
    for (const auto& complaint : complaints) {
        if (complaint->getCID() == id) {
            complaint->SetStatus(RESOLVED);
            return;
        }
    }
}
void Department::Notify(int Id)
{
    // Find the complaint with the specified ID
    auto it = std::find_if(complaints.begin(), complaints.end(), [Id](Complaint* complaint) {
        return complaint->getCID() == Id;
        });

    // If the complaint is found, call its Notify function
    if (it != complaints.end()) {
        (*it)->Notify();
    }
}
void Department::new_set(Manager* m){
    mgr = m;
}
int Department::getComplaintNumbers()
{
    return complaints.size();
}
void Department::PrintManager()
{

}
void Department::DisplayComplaintIDandStatus()
{
    for (auto& cmp : complaints) {
        
        cmp->PrintIDandStatus();
        std::cout << "-------------------------\n";
    }
}
void Department::PrintComplaintDate_Status_Des(int id)
{
    std::cout << "-------------------------\n";
    for (auto& complaint : complaints) {
        if (complaint->getCID() == id) {
            complaint->printDate_Status_Des();
            return;  // Assuming each complaint has a unique ID
        }
    }
    std::cout << "Complaint with ID " << id << " not found." << std::endl;
}
void Department::PrintTeacher(int id)
{
    for (auto& complaint : complaints) {
        if (complaint->getCID() == id) {
            complaint->PrintTeacher();
            return;  // Assuming each complaint has a unique ID
        }
    }
    std::cout << "Complaint with ID " << id << " not found." << std::endl;
}
void Department::PrintManagerAndEmployees(int id)
{
    for (auto& complaint : complaints) {
        if (complaint->getCID() == id) {
            if (complaint->GetStatus() == ASSIGNED) {
                cout << "\nManager: \n";
                std::cout << "-------------------------\n";
                mgr->MPrint();
                std::cout << "-------------------------\n";
                cout << "Employees:\n";
                mgr->PrintAssignedEmployees(id);
                return;
            }
            else {
                std::cout << "-------------------------\n";
                cout<<"Not Assigned\n";
                std::cout << "-------------------------\n";
                return;
            }
        }
    }
}
void Department::PrintJobDate(int id)
{
    for (auto& complaint : complaints) {
        if (complaint->getCID() == id) {
            if (complaint->GetStatus() == ASSIGNED) {
                mgr->printJobByID(id);
                return;
            }
        }
        else {
            cout << "Not Assigned\n";
            return;
        }
    }
}
bool Department::HasEmployee(const std::string& employeeID) const
{
    // Check if the department has an employee with the specified ID
    auto it = std::find_if(emp.begin(), emp.end(), [employeeID](const Employees* employee) {
        return employee->getId() == employeeID;
        });

    return it != emp.end();
}
void Department::RemoveEmployee(const std::string& employeeID)
{
    emp.remove_if([employeeID](const Employees* employee) {
        return employee->getId() == employeeID;
        });
}
void Department::SetManager(Manager* manager) {
    // Assuming that only one manager is associated with a department
    // If multiple managers are allowed, you may need to change the data structure
    mgr = manager;
    //mgr->SetDepartment(*this);  // Set the department for the manager
}

void Department::setEmployee(Employees* emp)
{
    this->emp.push_back(emp);
}





void Department::Print() {
    cout << "DEPARTMENT NAME: " << Dept_Tostring(Dept) << endl;
    Manager* m = GetManager();
    m->MPrint();
    cout << "COMPLAINTS:-\n";
    PrintComplaints();
}

DepartmentNames Department::getDept()
{
    return Dept;
}

Manager* Department::GetManager() const {
    return mgr;
}

void Department::AddEmployee(Employees* employee)
{
    emp.push_back(employee);
    employee->SetDepartment(this);
}

const std::list<Complaint*>& Department::GetComplaints() const {
    return complaints;
}

list<Employees*> Department::getEmployees()
{
    return emp;
}

void Department::UpdateEmployee(string id) {
    for (auto& employee : emp) {
        if (employee->getId() == id) {
            // Assuming you have a setStatus function in the Employees class
            employee->setstatus("A");
            return;  // No need to continue searching once the employee is found
        }
    }
    // If the loop completes and no matching employee is found
    std::cout << "Employee with ID " << id << " not found in the department.\n";
}

void Department::UpdateComplaint(int id) {
    Status newStatus = ASSIGNED;

    for (auto& complaint : complaints) {
        if (complaint->getCID() == id) {
            complaint->SetStatus(newStatus);
            return;  // No need to continue searching once the complaint is found
        }
    }

    // If the loop completes and no matching complaint is found
    std::cout << "Complaint with ID " << id << " not found in the department.\n";
}


