#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <unordered_map>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <iomanip>
#include <list>
#include "Teacher.h"
#include "Manager.h"
#include "Department.h"
#include "Employees.h"
#include <string>
#include "Job.h"
#include "States.h"
#include "Administrator.h"
#include "Date.h"
#include "Director.h"
#include "EInterface.h"
#include "TInterface.h"
#include "MInterface.h"
#include "DInterface.h"
#include "AInterface.h"
using namespace std;
string Dept_Tostring(DepartmentNames dept) {
    switch (dept) {
    case IT: return "IT";
    case Admins: return "Admins";
    case Accounts: return "Accounts";
        // Add other cases as needed
    default: return "Unknown";
    }
}
string StateTostring(Status s)
{
    if (s == ASSIGNED) {
        return "Assigned";
    }
    else if (s == NEW) {
        return "New";
    }
    else if (s == RESOLVED) {
        return "Resolved";
    }
}
Date* tokenizeDate(const std::string& date) {
    std::istringstream iss(date);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token) {
        // If token contains a ":" (indicating the time part), further tokenize it
        if (token.find(":") != std::string::npos) {
            std::istringstream timeIss(token);
            std::string timeToken;
            while (std::getline(timeIss, timeToken, ':')) {
                tokens.push_back(timeToken);
            }
        }
        else {
            // Otherwise, treat it as a regular token
            tokens.push_back(token);
        }
    }

    // Create a new Date object
    Date* d = new Date(tokens[0], tokens[1], std::stoi(tokens[2]),
        std::stoi(tokens[3]), std::stoi(tokens[4]), std::stoi(tokens[5]), std::stoi(tokens[6]));

    return d;
}
class ComplaintManagementSystem {
private:
    std::list<Department> departments;
    std::list<Teacher> teachers;
    std::list<Manager> managers;
    std::list<Complaint> complaints;
    std::list<Employees> employees;
    std::list<Job> jobs;
    std::list<Administrator> admin;
    std::list<Director> director;
    TInterface* loggedInTeacher;
    MInterface* loggedInManager;
    EInterface* loggedInEmployee;
    AInterface* loggedInAdmin;
    DInterface* loggedInDirector;
    int ComplaintId;

public:
    ComplaintManagementSystem() {
        loggedInTeacher = nullptr;
        loggedInManager = nullptr;
        loggedInEmployee = nullptr;
        loggedInAdmin = nullptr;
        loggedInDirector = nullptr;
        ComplaintId = 1;
    }

    void initializeSystem() {
        departments.emplace_back(DepartmentNames::IT);
        departments.emplace_back(DepartmentNames::Admins);
        departments.emplace_back(DepartmentNames::Accounts);
        auto teachersPair = SetTeacher();
        teachers = teachersPair.first;
        SetManager(departments, managers);
        SetEmployee(departments, employees);
        auto adminPair = SetAdmin();
        admin = adminPair.first;
        auto directorPair = SetDirector();
        director = directorPair.first;
        set_complaints(teachers, departments, complaints);
        SetJobs(managers, employees, jobs);
    }

    void gotoxy(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    void loginInterface() {
        std::string ID;
        while (1) {
            std::cout << "Enter your ID: ";
            std::cin >> ID;
            system("CLS");

            // Handle different user types (teacher, director, manager, employee, admin)
            if (SearchTeacher(teachers, ID)) {
                teacherInterface(ID);
            }
            else if (SearchDirector(director, ID)) {
                directorInterface(ID);
            }
            else if (SearchManager(managers, ID)) {
                managerInterface(ID);
            }
            else if (SearchEmployee(employees, ID)) {
                employeeInterface(ID);
            }
            else if (SearchAdmin(admin, ID)) {
                adminInterface(ID);
            }
            else {
                std::cout << "Not Valid... Enter Again!\n";
            }
        }
    }

    bool SearchTeacher(const std::list<Teacher>& teachers, const std::string& ID) {
        for (const auto& teacher : teachers) {
            if (ID == teacher.getID()) {
                return true;
            }
        }
        return false;
    }

    bool SearchManager(const std::list<Manager>& managers, const std::string& ID) {
        for (const auto& manager : managers) {
            if (ID == manager.MgetID()) {
                return true;
            }
        }
        return false;
    }

    bool SearchEmployee(const std::list<Employees>& employee, const std::string& ID) {
        for (const auto& employees : employee) {
            if (ID == employees.getId()) {
                return true;
            }
        }
        return false;
    }

    bool SearchAdmin(const std::list<Administrator>& admin, const std::string& ID) {
        for (const auto& ad : admin) {
            if (ID == ad.getId()) {
                return true;
            }
        }
        return false;
    }
    bool SearchDirector(const std::list<Director>& director, const std::string& ID)
    {
        for (const auto& d : director) {
            if (ID == d.getId()) {
                return true;
            }
        }
        return false;
    }
    void teacherInterface(string ID) {
        auto it = std::find_if(teachers.begin(), teachers.end(), [ID](const Teacher& teacher) {
            return teacher.getID() == ID;
            });

        if (it != teachers.end()) {
            loggedInTeacher = &(*it);
            loggedInTeacher->Print();
            cout << loggedInTeacher->getNotifications() << " New Notification!!\n";
            std::cout << "-------------------------\n";
            std::cout << "Welcome!\n" << std::endl;

            while (1) {
                int func;
                std::cout << "1- File Complaint." << std::endl;
                std::cout << "2- View Notification(s)." << std::endl;
                std::cout << "3- Log out." << std::endl;
                std::cout << "Enter: ";
                std::cin >> func;
                if (func == 1) {
                    complaints.push_back(*(loggedInTeacher->file_complaint(departments, ComplaintId++)));
                }
                else if (func == 2) {
                    int choice, Cid, choice1;
                    if (loggedInTeacher->getNotifications() != 0)
                    {
                        loggedInTeacher->PrintNotification();
                        cout << "Do you Wish to Provide Feedback?\n";
                        cout << "1- YES\n2- NO\n";
                        cin >> choice;
                        if (choice == 1) {
                            cout << "Enter the Complaint ID";
                            cin >> Cid;
                            cout << "Are You Satisfied?\n";
                            cout << "1- YES\n2- NO\n";
                            cin >> choice1;
                            if (choice1 == 1) {
                                loggedInTeacher->UpdateComplaint(Cid);
                                UpdateComplainStatus(complaints, Cid, RESOLVED);
                                UpdateComplainFile(complaints);
                                loggedInTeacher->RemoveNotification(Cid);
                                cout << "Case Resolved!" << endl;
                            }
                            else if (choice1 == 2) {
                                UpdateComplainStatus(complaints, Cid, NEW);
                                UpdateComplainFile(complaints);
                                cout << "We will Again work on it!" << endl;
                            }
                        }

                        else if (choice == 2) {
                            UpdateComplainStatus(complaints, Cid, RESOLVED);
                            UpdateComplainFile(complaints);
                            cout << "Case Resolved!" << endl;
                        }
                    }
                    else {
                        std::cout << "-------------------------\n";
                        cout << "No New Notifications!!\n";
                        std::cout << "-------------------------\n";
                    }
                }
                else if (func == 3) {
                    system("CLS");
                    loggedInTeacher = nullptr;
                    break;
                }
                else {
                    break;
                }
            }
        }
    }

    void directorInterface(string ID) {
        auto it = std::find_if(director.begin(), director.end(), [ID](const Director& director) {
            return director.getId() == ID;
            });

        if (it != director.end()) {
            loggedInDirector = &(*it);
            loggedInDirector->Print();
        }
        while (1) {
            int check;
            cout << "Enter 1 to View Summary of Complaints.\n";
            cout << "Enter 2 to View Info of Complaints in a Department.\n";
            cout << "Enter 3 to Log out.\n";
            cin >> check;
            if (check == 1) {
                string mon1, mon2;
                int d1, y1, d2, y2;
                cout << "Enter the start Date\n";
                cout << "Date: ";
                cin >> d1;
                cout << "Month: ";
                cin >> mon1;
                cout << "Year: ";
                cin >> y1;
                cout << endl;
                cout << "Enter the end Date\n";
                cout << "Date: ";
                cin >> d2;
                cout << "Month: ";
                cin >> mon2;
                cout << "Year: ";
                cin >> y2;

                // Convert month strings to numbers
                int numMon1 = convertMonthToNumber(mon1);
                int numMon2 = convertMonthToNumber(mon2);

                for (auto& complaint : complaints) {
                    int complaintDate = complaint.getDate();
                    string complaintMonth = complaint.getMonth();
                    int complaintYear = complaint.getYear();

                    // Convert complaint month string to number
                    int numComplaintMonth = convertMonthToNumber(complaintMonth);

                    // Check if the complaint is within the specified date range
                    if ((complaintYear > y1 || (complaintYear == y1 && numComplaintMonth > numMon1) || (complaintYear == y1 && numComplaintMonth == numMon1 && complaintDate >= d1)) &&
                        (complaintYear < y2 || (complaintYear == y2 && numComplaintMonth < numMon2) || (complaintYear == y2 && numComplaintMonth == numMon2 && complaintDate <= d2))) {
                        // Call the Complain_Print() function on each Complaint object
                        std::cout << "-------------------------\n";
                        complaint.Complain_print();
                    }
                }
            }


            else if (check == 2) {
                string dep;
                cout << "Enter Department Name: ";
                cin >> dep;
                bool flag = true;
                for (auto& dept : departments) {
                    if (dep == Dept_Tostring(dept.getDept())) {
                        flag = false;
                        std::cout << "-------------------------\n";
                        cout << "Complaints Recieved: " << dept.getComplaintNumbers() << endl;
                        std::cout << "-------------------------\n";
                        dept.DisplayComplaintIDandStatus();
                        int choice, cid;
                        cout << "Do you wish to See Details of Any Complaint?\n";
                        cout << "1- YES\n2- NO\n";
                        cin >> choice;
                        if (choice == 1) {
                            int choice2;
                            cout << "Enter CID: ";
                            cin >> cid;
                            while (1) {
                                cout << "1- Complaint Date, Status and Description.\n";
                                cout << "2- Teacher who Initiated it.\n";
                                cout << "3- Relevant Manager and Employee.\n";
                                cout << "4- Job assignment Date.\n";
                                cout << "5- to quit.\n";
                                cin >> choice2;
                                if (choice2 == 1) {
                                    dept.PrintComplaintDate_Status_Des(cid);
                                }
                                else if (choice2 == 2) {
                                    dept.PrintTeacher(cid);
                                }
                                else if (choice2 == 3) {
                                    dept.PrintManagerAndEmployees(cid);
                                }
                                else if (choice2 == 4) {
                                    dept.PrintJobDate(cid);
                                }
                                else if (choice2 == 5) {
                                    break;
                                }
                            }

                        }
                        else if (choice == 2) {
                            break;
                        }
                        break;
                    }
                }
                if (flag) {
                    cout << "Department doesn't exist\n";
                }
            }
            else if (check == 3) {
                system("CLS");
                loggedInManager = nullptr;
                break;
            }
        }
    }

    void managerInterface(string ID) {
        auto it = std::find_if(managers.begin(), managers.end(), [ID](const Manager& manager) {
            return manager.MgetID() == ID;
            });

        if (it != managers.end()) {
            loggedInManager = &(*it);
            loggedInManager->MPrint();
            std::cout << "-------------------------\n";
            cout << loggedInManager->getNotifications() << " New Notification(s)!!\n";
            std::cout << "-------------------------\n";
            cout << loggedInManager->NumberOfNewComplaints() << " New Complaints in your Department.\n";
            std::cout << "-------------------------\n";

            while (1) {
                int check, e_available, cid, no_of_e;
                string eid;
                std::cout << "1- Assign Job." << std::endl;
                std::cout << "2- Show All Complaints History." << std::endl;
                std::cout << "3- View Notification." << std::endl;
                std::cout << "4- Log out." << std::endl;
                std::cout << "Enter: ";
                std::cin >> check;
                if (check == 1) {
                    if (loggedInManager->DisplayNewComplaints())
                    {
                        e_available = loggedInManager->DisplayEmployees();
                        if (e_available != 0)
                        {
                            cout << "Enter the Complaint ID that you wish to assign someone: ";
                            cin >> cid;
                            cout << "Enter number of Employees required for this job: ";
                            cin >> no_of_e;

                            if (no_of_e <= e_available) {
                                loggedInManager->assign_complaint(cid);
                                for (int i = 0; i < no_of_e; i++) {
                                    cout << "Enter Employee ID: ";
                                    cin >> eid;
                                    Job* newJob = new Job(cid, getEmp(eid), loggedInManager->getMgr());
                                    jobs.push_back(*newJob);
                                    loggedInManager->assign_employee(eid);
                                    SetempJob(getEmp(eid), &jobs.back());
                                    updateJobFile(cid, eid, ID);
                                    UpdateEmpStatus(employees, eid, "A");
                                    UpdateEmployeeFile(employees);
                                }
                                UpdateComplainStatus(complaints, cid, ASSIGNED);
                                UpdateComplainFile(complaints);
                                cout << "Successfully Assigned!!!\n";
                            }
                            else {
                                std::cout << "-------------------------\n";
                                cout << "Not enough employees are available.\n";
                                std::cout << "-------------------------\n";
                            }
                        }
                        else {
                            std::cout << "-------------------------\n";
                            cout << "No Free Employees in your department!\n";
                            std::cout << "-------------------------\n";
                        }
                    }
                    else {
                        std::cout << "-------------------------\n";
                        cout << "No NEW Complaints to Assign\n";
                        std::cout << "-------------------------\n";
                    }
                }
                else if (check == 2) {
                    std::cout << "-------------------------\n";
                    loggedInManager->DisplayAllComplaints();
                }
                else if (check == 3) {
                    int choice = 0, Cid;
                    if (loggedInManager->getNotifications() != 0)
                    {
                        loggedInManager->PrintNotification();
                        cout << "Do you Wish to Approve Any Job\n";
                        cout << "1- YES\n2- NO\n";
                        cin >> choice;
                        if (choice == 1) {
                            cout << "Enter the Complaint ID that you Wish to Approve: ";
                            cin >> Cid;
                            loggedInManager->Notify(Cid);
                            loggedInManager->RemoveNotification(Cid);
                        }
                        else if (choice == 2) {
                            std::cout << "-------------------------\n";
                            cout << "Sent to Drafts!!\n";
                            std::cout << "-------------------------\n";
                        }
                    }
                    else {
                        std::cout << "-------------------------\n";
                        cout << "No New Notifications!!\n";
                        std::cout << "-------------------------\n";
                    }
                }
                else if (check == 4) {
                    system("CLS");
                    loggedInManager = nullptr;
                    break;
                }
                else {
                    cout << "Invalid Input!!!" << endl;
                }
            }
        }
    }
    void SetempJob(Employees* emp, Job* job) {
        emp->Set_Job(job);
    }
    Employees* getEmp(string id) {
        auto it = std::find_if(employees.begin(), employees.end(), [id](const Employees& emp) {
            return emp.getId() == id;
            });

        if (it != employees.end()) {
            // Employee with the specified ID found
            return &(*it);
        }
        else {
            // Employee with the specified ID not found
            return nullptr;
        }
    }
    void employeeInterface(string ID) {
        int check;
        auto it = std::find_if(employees.begin(), employees.end(), [ID](const Employees& employees) {
            return employees.getId() == ID;
            });
        if (it != employees.end()) {
            int choice;
            loggedInEmployee = &(*it);
            std::cout << "-------------------------\n";
            loggedInEmployee->Print(); cout << endl;
            std::cout << "Welcome!\n" << std::endl;
            while (1) {
                std::cout << "1- Assigned Job." << std::endl;
                std::cout << "2- Update Job Status." << std::endl;
                std::cout << "3- Log out." << std::endl;
                std::cout << "Enter: ";
                cin >> check;
                if (check == 1) {

                    loggedInEmployee->GetJobDetails();

                }
                else if (check == 2) {
                    if (loggedInEmployee->get_status() == "A")
                    {
                        cout << "Have You Completed Your Job?\n";
                        cout << "1- YES\n2- NO\n";
                        cin >> choice;
                        if (choice == 1) {
                            int dum = loggedInEmployee->get_complainID();
                            loggedInEmployee->setstatus("NA");
                            UpdateEmpStatus(employees, ID, "NA");
                            UpdateEmployeeFile(employees);
                            if (Find_employees(jobs, dum)) {
                                loggedInEmployee->Notify(loggedInEmployee->get_complainID());
                            }
                            std::cout << "-------------------------\n";
                            cout << "Good Job!!!\n";
                            std::cout << "-------------------------\n";
                        }
                        else if (choice == 2) {
                            std::cout << "-------------------------\n";
                            cout << "Complete it at your Earliest Convenience!!\n" << endl;
                            std::cout << "-------------------------\n";
                        }
                    }
                    else {
                        std::cout << "-------------------------\n";
                        cout << "No Job has been Assigned to you\n";
                        std::cout << "-------------------------\n";
                    }
                }
                else if (check == 3) {
                    system("CLS");
                    loggedInEmployee = nullptr;
                    break;
                }
                else {
                    cout << "Invalid Input!!!\n";
                }
            }
        }

    }

    void adminInterface(string ID)
    {
        int check;
        auto it = std::find_if(admin.begin(), admin.end(), [ID](const Administrator& admin) {
            return admin.getId() == ID;
            });
        if (it != admin.end()) {
            loggedInAdmin = &(*it);
            loggedInAdmin->Print(); cout << endl;
            std::cout << "Welcome!\n\n" << std::endl;
            string input_dept, temp, nid; int choice = 2;
            while (1) {
                cout << "1- Add Manager." << std::endl;
                cout << "2- Remove Manager." << std::endl;
                cout << "3- Add Teacher." << std::endl;
                cout << "4- Remove Teacher." << std::endl;
                cout << "5- Add Employee." << std::endl;
                cout << "6- Remove Employee." << std::endl;
                cout << "7- Log out." << std::endl;
                cout << "Enter: ";
                cin >> check;
                if (check == 1) {
                    cout << "Enter Department: ";
                    cin >> input_dept;
                    bool departmentFound = false;
                    for (auto& depart : departments) {
                        temp = Dept_Tostring(depart.getDept());
                        if (temp == input_dept) {
                            Manager* departmentManager = depart.GetManager();
                            if (departmentManager) {
                                std::cout << "-------------------------\n";
                                departmentManager->MPrint(); choice = 1;
                                std::cout << "-------------------------\n";
                                cout << temp << " Department already has one Manager!\n";
                                std::cout << "-------------------------\n";
                            }
                            else {
                                std::cout << "-------------------------\n";
                                cout << temp << " Department does not have a Manager.\n";
                                std::cout << "-------------------------\n";
                                string newID, fname, lname; int age;
                                const Manager temp = managers.back();
                                nid = temp.MgetID();
                                newID = newIDGenerator(nid);
                                cout << "Enter first name: "; cin >> fname;
                                cout << "Enter last name: "; cin >> lname;
                                cout << "Enter age: "; cin >> age;
                                Manager* newManager = new Manager(fname, lname, age, newID);
                                newManager->SetDepartment(depart);
                                managers.push_back(*newManager);
                                depart.SetManager(newManager);
                                cout << endl;
                                ChangeManagerIdInFile("Job.txt", "N/A", newID, jobs, managers.back());
                                fstream managerFile("manager.txt", ios::in | ios::out);
                                if (managerFile.is_open()) {
                                    int totalManagers = managers.size();
                                    managerFile.seekp(0);
                                    managerFile << totalManagers << std::endl;
                                    managerFile.close();
                                    managerFile.open("manager.txt", ios::app);
                                    managerFile << newID << " " << input_dept << " " << fname << " " << lname << " " << age << endl;
                                    std::cout << "-------------------------\n";
                                    cout << "New Manager added successfully.\n";
                                    std::cout << "-------------------------\n";
                                    managerFile.close();
                                }
                                else {
                                    std::cout << "Error opening manager.txt for writing.\n";
                                }
                            }
                            departmentFound = true;
                        }
                    }
                    if (!departmentFound) {
                        std::cout << "-------------------------\n";
                        cout << "Department not found.\n";
                        std::cout << "-------------------------\n";
                    }
                }
                else if (check == 2) {
                    string ID, d;
                    cout << "Enter the Department: "; cin >> d;
                    cout << "Enter the Manager's ID: "; cin >> ID;
                    removeManager(ID, d, departments, managers, employees, jobs);
                    ChangeManagerIdInFile("Job.txt", ID, "N/A", jobs);
                }
                else if (check == 3) {
                    addNewTeacher(teachers);
                }
                else if (check == 4) {
                    removeTeacher(teachers, complaints);
                }
                else if (check == 5) {
                    addNewEmployee(employees, departments);
                }
                else if (check == 6) {
                    removeEmployee(employees, departments, managers, jobs);
                }
                else if (check == 7) {
                    system("CLS");
                    loggedInAdmin = nullptr;
                    break;
                }
                else {
                    cout << "Invalid Input!!!\n";
                }
            }
        }
    }
    std::pair<std::list<Teacher>, int> SetTeacher() {
        std::list<Teacher> teachers;
        std::fstream MyFile;
        MyFile.open("teachers.txt", std::ios::in);
        std::string fname, lname, T_ID;
        int age, NoOfTeachers;
        MyFile >> NoOfTeachers;

        for (int i = 0; i < NoOfTeachers; i++) {
            MyFile >> T_ID >> fname >> lname >> age;
            Teacher newTeacher;
            newTeacher.Tsetter(fname, lname, age, T_ID);
            teachers.push_back(newTeacher);
        }

        MyFile.close();
        return { teachers, NoOfTeachers };
    }
    void UpdateEmpStatus(std::list<Employees>& emp, string& ID, string newStatus) {
        for (auto& employee : emp) {
            if (employee.getId() == ID) {
                // Employee found, update the status
                employee.setstatus(newStatus);
                return; // Assuming each ID is unique, so we can return after updating
            }
        }
    }
    void set_complaints(std::list<Teacher>& teachers, std::list<Department>& departments, list<Complaint>& complaints) {
        std::fstream newfile;
        newfile.open("complains.txt", std::ios::in);
        std::string C_ID, description, deptName, status, date;
        int NoOfComplains;

        newfile >> NoOfComplains;
        string check;
        for (int i = 0; i < NoOfComplains; i++) {
            newfile >> C_ID >> status >> deptName;
            getline(newfile >> std::ws, description, '|');
            getline(newfile >> std::ws, date);
            Date* d = tokenizeDate(date);
            // Find the teacher with the given ID
            auto teacherIt = std::find_if(teachers.begin(), teachers.end(), [C_ID](const Teacher& teacher) {
                return teacher.getID() == C_ID;
                });

            // Find the department with the given name
            auto departmentIt = std::find_if(departments.begin(), departments.end(), [deptName](const Department& department) {
                return Dept_Tostring(department.Dept) == deptName;
                });

            if (teacherIt != teachers.end() && departmentIt != departments.end()) {
                // Create a new Complaint and associate it with the Teacher and Department
                Complaint* complaint = new Complaint(description, &(*teacherIt), &(*departmentIt), status, ComplaintId++);
                complaint->setDate(*d);
                // Add the complaint to the teacher and department
                teacherIt->Setcomplaint(complaint);
                departmentIt->AddComplaint(complaint);
                complaints.push_back(*complaint);
            }
        }

        newfile.close();
    }
    void SetEmployee(list<Department>& departments, list<Employees>& employees)
    {
        fstream myfile;
        myfile.open("employees.txt", std::ios::in);
        std::string ID, dept, lname, fname, status;
        int age, NoOfEmployees;
        myfile >> NoOfEmployees;

        for (int i = 0; i < NoOfEmployees; i++) {
            myfile >> ID >> dept >> status >> lname >> fname >> age;
            Employees* newEmployee = new Employees(ID, status, lname, fname, age, nullptr);

            // Find the department in the existing departments list
            auto it = std::find_if(departments.begin(), departments.end(), [dept](Department& department) {
                return Dept_Tostring(department.getDept()) == dept;
                });


            if (it != departments.end()) {
                // Associate the employee with the existing department
                employees.push_back(*newEmployee);
                it->AddEmployee(&employees.back());
            }


        }

        myfile.close();
    }
    void updateJobFile(int id, const std::string& eid, const std::string& mid) {

        string t;
        time_t now = time(0);
        t = ctime(&now);
        fstream JFile("Job.txt", std::ios::in | std::ios::out);
        int totalJobs;
        JFile >> totalJobs;
        totalJobs++;
        JFile.seekg(0);
        JFile << totalJobs;
        JFile.close();
        ofstream jobFile("Job.txt", std::ios::app);

        if (jobFile.is_open()) {
            jobFile << id << " " << eid << " " << mid << " " << t;
            jobFile.close();
        }
        else {
            std::cout << "Error opening Job.txt for writing.\n";
        }
    }
    Manager* findManagerById(std::list<Manager>& managers, std::string& managerId) {
        auto it = std::find_if(managers.begin(), managers.end(), [managerId](const Manager& manager) {
            return manager.MgetID() == managerId;
            });

        if (it != managers.end()) {
            return (&(*it));  // Use const_cast to remove const qualifier
        }
        else {
            return nullptr;
        }
    }
    Employees* findEmployeeById(std::list<Employees>& employees, std::string& employeeId) {
        auto it = std::find_if(employees.begin(), employees.end(), [employeeId](Employees& employee) {
            return employee.getId() == employeeId; // Assuming the correct getter function is "getId"
            });

        if (it != employees.end()) {
            return (&(*it));  // Use const_cast to remove const qualifier
        }
        else {
            return nullptr;
        }
    }
    void UpdateComplainStatus(list<Complaint>& com, int& ID, Status status) {
        for (auto& complain : com) {
            if (complain.getCID() == ID) {
                complain.SetStatus(status);
                return; // Assuming each ID is unique, so we can return after updating
            }
        }
    }
    bool Find_employees(list<Job>& job, int ID) {
        for (auto& j : job) {
            if (j.get_id() == ID) {
                list<Employees*> temp = j.get_job_emp_id();
                for (auto& employee : temp) {
                    if (employee->get_status() == "A") {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void UpdateEmployeeFile(std::list<Employees>& emp) {
        std::ofstream employeesFile("employees.txt");
        if (employeesFile.is_open()) {
            employeesFile << emp.size() << std::endl;
            for (auto& employee : emp) {
                std::string id, dept, status, fname, lname;
                int age;
                employee.getter(id, dept, status, fname, lname, age);
                employeesFile << id << " " << dept << " " << status << " " << fname << " " << lname << " " << age << std::endl;
            }
            employeesFile.close();
        }
        else {
            std::cout << "Error opening employees.txt for updating.\n";
        }
    }

    std::pair<std::list<Administrator>, int> SetAdmin() {
        std::list<Administrator> admin;
        std::fstream MyFile;
        MyFile.open("Administrator.txt", std::ios::in);
        std::string fname, lname, T_ID;
        int age, NoOfadmin;
        MyFile >> NoOfadmin;
        for (int i = 0; i < NoOfadmin; i++) {
            MyFile >> T_ID >> fname >> lname >> age;
            Administrator newAdmin;
            newAdmin.Admin_setter(fname, lname, age, T_ID);
            admin.push_back(newAdmin);
        }
        MyFile.close();
        return { admin, NoOfadmin };
    }

    void UpdateComplainFile(std::list<Complaint>& com) {
        std::ofstream complaintFile("complains.txt");
        if (complaintFile.is_open()) {
            complaintFile << com.size() << std::endl;
            for (auto& complain : com) {
                string id, dept, status, des, date;
                id = complain.T_ID_getter();
                status = StateTostring(complain.GetStatus());
                dept = Dept_Tostring(complain.getdept());
                des = complain.getdescription();
                date = complain.getdate();
                complaintFile << id << " " << status << " " << dept << " " << des << "|" << date << endl;
            }
            complaintFile.close();
        }
        else {
            cout << "Error opening complains.txt for updation.\n";
        }
    }
    int convertStringToInt(const string& input) {
        try {
            return std::stoi(input);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << e.what() << std::endl;
            return 0;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Out of range: " << e.what() << std::endl;
            return 0;
        }
    }

    string newIDGenerator(string id) {
        string prefix = id.substr(0, id.length() - 2);
        int number;
        istringstream(id.substr(id.length() - 2)) >> number;
        number++;
        std::ostringstream newId;
        newId << prefix << setw(2) << setfill('0') << number;
        return newId.str();
    }

    void addNewTeacher(std::list<Teacher>& teachers) {
        const Teacher& lastTeacher = teachers.back();
        std::string newTeacherID = newIDGenerator(lastTeacher.getID());
        std::string fname, lname;
        int age;
        std::cout << "Enter First Name: ";
        std::cin >> fname;
        std::cout << "Enter Last Name: ";
        std::cin >> lname;
        std::cout << "Enter Age: ";
        std::cin >> age;
        Teacher newTeacher(fname, lname, age, newTeacherID);
        teachers.push_back(newTeacher);
        std::fstream teacherFile("teachers.txt", std::ios::in | std::ios::out);
        if (teacherFile.is_open()) {
            int totalTeachers = teachers.size();
            teacherFile.seekp(0);
            teacherFile << totalTeachers << std::endl;
            teacherFile.close();
            teacherFile.open("teachers.txt", std::ios::app);
            teacherFile << newTeacherID << " " << fname << " " << lname << " " << age << std::endl;
            std::cout << "New teacher added successfully.\n";
            teacherFile.close();
        }
        else {
            std::cout << "Error opening teachers.txt for writing.\n";
        }
    }

    void addNewEmployee(std::list<Employees>& emp, list<Department>& dept) {
        const Employees lastEmp = emp.back();
        std::string newID = newIDGenerator(lastEmp.getId());
        std::string fname, lname;
        int age, choice;
        int i = 0;
        for (auto& department : dept) {
            std::cout << "[" << i + 1 << "]" << "Department Name: " << Dept_Tostring(department.getDept()) << std::endl;
            i++;
        }
        std::cout << "Enter the index number of Dept: ";
        std::cin >> choice;
        choice--;
        auto it = dept.begin();
        advance(it, choice);
        if (it != dept.end()) {
            std::cout << "-------------------------\n";
            std::cout << "You selected: " << Dept_Tostring(it->getDept()) << std::endl;
            std::cout << "-------------------------\n";

        }
        else {
            std::cout << "-------------------------\n";
            std::cout << "Invalid choice." << std::endl;
            std::cout << "-------------------------\n";
        }
        std::cout << "Enter First Name: ";
        std::cin >> fname;
        std::cout << "Enter Last Name: ";
        std::cin >> lname;
        std::cout << "Enter Age: ";
        std::cin >> age;
        Employees* newEmp = new Employees(newID, "NA", fname, lname, age, &(*it));
        emp.push_back(*newEmp);
        it->AddEmployee(&emp.back());
        std::fstream File("employees.txt", std::ios::in | std::ios::out);
        if (File.is_open()) {
            int totalEmp = emp.size();
            File.seekp(0);
            File << totalEmp << std::endl;
            File.close();
            File.open("employees.txt", std::ios::app);
            File << newID << " " << Dept_Tostring(it->getDept()) << " " << newEmp->get_status() << " " << fname << " " << lname << " " << age << std::endl;
            std::cout << "-------------------------\n";
            std::cout << "New Employee added successfully.\n";
            std::cout << "-------------------------\n";
            File.close();
        }
        else {
            std::cout << "Error opening the file.\n";
        }
    }

    void removeManager(const string& managerID, string d, list<Department>& departments, list<Manager>& managers, list<Employees>& emp, list<Job>& job) {
        bool managerFound = false;
        for (auto& depart : departments) {
            if (depart.GetManager()->MgetID() == managerID) {
                managerFound = true;
                depart.new_set(nullptr);
                auto it = job.begin();
                while (it != job.end()) {
                    it = std::find_if(it, job.end(), [managerID](Job& j) {
                        return j.getManagerID() == managerID;
                        });

                    if (it != job.end()) {
                        // Erase the job from the list
                        for (auto& employee : emp) {
                            if (employee.FindJob(&(*it))) {
                                employee.DeleteJob(&(*it));
                            }
                        }
                        it = job.erase(it);
                    }
                }
                auto managerIter = std::remove_if(managers.begin(), managers.end(),
                    [managerID](const Manager& manager) { return manager.MgetID() == managerID; });
                managers.erase(managerIter, managers.end());
                
                fstream managerFile("manager.txt", ios::out);
                if (managerFile.is_open()) {
                    int totalManagers = std::distance(managers.begin(), managers.end());
                    managerFile << totalManagers << endl;
                    for (const auto& manager : managers) {
                        managerFile << manager.MgetID() << " " << Dept_Tostring(manager.getDept()) << " " << manager.MgetFname() << " " << manager.MgetLname() << " " << manager.MgetAge() << endl;
                    }
                    cout << "Manager removed successfully.\n";
                    managerFile.close();
                }
                else {
                    cout << "Error opening manager.txt for writing.\n";
                }
                break;
            }
        }
        if (!managerFound) {
            cout << "Manager with ID " << managerID << " not found in any department.\n";
        }
    }

    void ChangeManagerIdInFile(const string& filename, const string& oldManagerId, const string& newManagerId, const list<Job>& job, Manager& mgr) {
  
        string line;
        fstream jobFile(filename, ios::in | ios::out);
        if (jobFile.is_open()) {
            int noOfJobs;
            jobFile >> noOfJobs;
            std::fstream tempJobFile("tempJob.txt", std::ios::out);
            tempJobFile << noOfJobs << std::endl;
            int complaintId;
            std::string employeeId, managerId, date;
            while (jobFile >> complaintId >> employeeId >> managerId) {
                getline(jobFile, date);
                if (managerId == oldManagerId) {
                    managerId = newManagerId;
                    Job* newJob = new Job(complaintId, getEmp(employeeId),  &mgr);
                    jobs.push_back(*newJob);
                    mgr.assign_employee(employeeId);
                    SetempJob(getEmp(employeeId), &jobs.back());               
                    UpdateEmpStatus(employees, employeeId, "A");
                    UpdateEmployeeFile(employees);
                }
                tempJobFile << complaintId << " " << employeeId << " " << managerId << date << std::endl;
            }
            jobFile.close();
            remove("Job.txt");
            tempJobFile.close();
            rename("tempJob.txt", "Job.txt");
        }
        else {
            cout << "Error opening Job.txt for reading and writing.\n";
        }
    }

    void ChangeManagerIdInFile(const string& filename, const string& oldManagerId, const string& newManagerId, const list<Job>& job) {
        string line;
        fstream jobFile(filename, ios::in | ios::out);
        if (jobFile.is_open()) {
            int noOfJobs;
            jobFile >> noOfJobs;
            std::fstream tempJobFile("tempJob.txt", std::ios::out);
            tempJobFile << noOfJobs << std::endl;
            std::string complaintId, employeeId, managerId, date;
            while (jobFile >> complaintId >> employeeId >> managerId) {
                getline(jobFile, date);
                if (managerId == oldManagerId) {
                    managerId = newManagerId;
                }
                tempJobFile << complaintId << " " << employeeId << " " << managerId << date << std::endl;
            }
            jobFile.close();
            remove("Job.txt");
            tempJobFile.close();
            rename("tempJob.txt", "Job.txt");
            cout << "Manager ID replaced successfully.\n";
        }
        else {
            cout << "Error opening Job.txt for reading and writing.\n";
        }
    }
    std::pair<std::list<Director>, int> SetDirector() {
        std::list<Director> director;
        std::fstream MyFile;
        MyFile.open("Director.txt", std::ios::in);
        std::string fname, lname, T_ID;
        int age, No;
        MyFile >> No;

        for (int i = 0; i < No; i++) {
            MyFile >> T_ID >> fname >> lname >> age;
            Director* newDirector = new Director(T_ID, fname, lname, age);
            director.push_back(*newDirector);
        }

        MyFile.close();
        return { director, No };
    }
    int convertMonthToNumber(const std::string& month) {
        std::unordered_map<std::string, int> monthMap = {
            {"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4},
            {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8},
            {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}
        };

        auto it = monthMap.find(month);
        if (it != monthMap.end()) {
            return it->second;
        }

        // Default to 0 if the month is not found (you can handle this case based on your requirements)
        return 0;
    }
    void SetManager(list<Department>& departments, list<Manager>& managers)
    {
        std::fstream myfile;
        myfile.open("manager.txt", std::ios::in);
        int NoOfManager;
        myfile >> NoOfManager;

        for (int i = 0; i < NoOfManager; i++) {
            std::string ID, dept, fname, lname;
            int age;

            // Read manager information
            myfile >> ID >> dept >> fname >> lname >> age;

            // Find the index of the department in the list
            auto it = std::find_if(departments.begin(), departments.end(), [dept](const Department& department) {
                return Dept_Tostring(department.Dept) == dept;
                });
            if (it != departments.end()) {
                // Create a new manager
                Manager* newManager = new Manager;
                // Set manager information and pass the department pointer
                newManager->Msetter(fname, lname, age, ID, &(*it));
                // Add the manager to the list
                managers.push_back(*newManager);
                // Set the manager in the department
                it->SetManager(&managers.back());

            }
        }
        myfile.close();
    }

    void removeEmployee(std::list<Employees>& emp, std::list<Department>& dept, std::list<Manager>& man, list<Job>& job) {
        std::cout << "List of Employees:\n";
        int i = 1;
        for (const auto& employee : emp) {
            std::cout << "[" << i << "]" << " ID: " << employee.getId() << ", Name: " << employee.UgetFname() << ", Age: " << employee.UgetAge() << std::endl;
            i++;
        }
        int choice;
        std::cout << "Enter the index of the employee to remove: ";
        std::cin >> choice;
        choice--;
        auto it = emp.begin();
        std::advance(it, choice);
        if (it != emp.end()) {
            std::string removedEmployeeID = it->getId();
            // Find the department to which the employee belongs
            auto deptIt = std::find_if(dept.begin(), dept.end(), [removedEmployeeID](const Department& department) {
                return department.HasEmployee(removedEmployeeID);
                });

            // Remove the employee from the department's list
            if (deptIt != dept.end()) {
                deptIt->RemoveEmployee(removedEmployeeID);
            }
            for (auto it1 = job.begin(); it1 != job.end(); ) {
                // Remove employee from the job
                bool employeeRemoved = it1->RemoveEmployee(removedEmployeeID);

                // Check if the job is empty after removing the employee
                if (employeeRemoved) {
                    // Find the manager that owns this job and remove it from the manager's list
                    for (auto& manager : man) {
                        bool jobRemoved = manager.RemoveJobIfBelongsToManager(&(*it1));

                        // Break the loop if the job was successfully removed
                        if (jobRemoved) {
                            //std::cout << "Job removed from the main list.\n";
                            break;
                        }
                    }

                    job.erase(it1);
                    break;
                }
                else {
                    ++it1;
                }
            }
            emp.erase(it);

            std::fstream employeeFile("employees.txt", std::ios::out | std::ios::trunc);
            if (employeeFile.is_open()) {
                int totalEmployees = emp.size();
                employeeFile << totalEmployees << std::endl;
                for (auto& employee : emp) {
                    employeeFile << employee.getId() << " " << Dept_Tostring(employee.get_d_name()->getDept()) << " " << employee.get_status() << " " << employee.UgetFname() << " " << employee.UgetLname() << " " << employee.UgetAge() << std::endl;
                }
                std::cout << "Employee removed successfully.\n";
                employeeFile.close();
            }
            else {
                std::cout << "Error opening employees.txt for writing.\n";
            }

            int noOfJobs;
            std::fstream jFile("Job.txt", std::ios::in);
            if (jFile.is_open()) {
                jFile >> noOfJobs;
                string complaintId, employeeId, managerId, line;
                while (jFile >> complaintId >> employeeId >> managerId) {
                    getline(jFile, line);
                    if (employeeId == removedEmployeeID) {
                        noOfJobs--;
                    }
                }
                jFile.close();
            }

            std::fstream jobFile("Job.txt", std::ios::in);
            if (jobFile.is_open()) {
                int dum;
                jobFile >> dum;
                string complaintId, employeeId, managerId, line;
                std::fstream tempJobFile("tempJob.txt", std::ios::out);
                tempJobFile << noOfJobs << std::endl;
                while (jobFile >> complaintId >> employeeId >> managerId) {
                    getline(jobFile, line);
                    if (employeeId != removedEmployeeID) {
                        tempJobFile << complaintId << " " << employeeId << " " << managerId << line << endl;
                    }
                }
                jobFile.close();
                remove("Job.txt");
                tempJobFile.close();
                rename("tempJob.txt", "Job.txt");
                std::cout << "Job entry for the removed employee removed successfully.\n";
            }
            else {
                std::cout << "Error opening Job.txt for reading.\n";
            }
        }
    }

    void removeTeacher(std::list<Teacher>& teachers, std::list<Complaint>& com) {
        // Display the list of teachers with their IDs
        std::cout << "List of Teachers:\n";
        for (const auto& teacher : teachers) {
            std::cout << "ID: " << teacher.getID() << ", Name: " << teacher.UgetFname() << " " << teacher.UgetLname() << ", Age: " << teacher.UgetAge() << std::endl;
        }

        // Get the ID of the teacher to be removed
        std::string teacherID;
        std::cout << "Enter the ID of the teacher to remove: ";
        std::cin >> teacherID;

        // Find the teacher with the given ID
        auto it = std::find_if(teachers.begin(), teachers.end(), [teacherID](const Teacher& teacher) {
            return teacher.getID() == teacherID;
            });

        // Check if the teacher was found
        if (it != teachers.end()) {
            // Remove the teacher from the list
            teachers.erase(it);

            // Open teachers.txt in out|trunc mode to update the number of teachers
            std::fstream teacherFile("teachers.txt", std::ios::out | std::ios::trunc);
            if (teacherFile.is_open()) {
                // Update the total number of teachers
                int totalTeachers = teachers.size();
                teacherFile << totalTeachers << std::endl;

                // Write the details of the remaining teachers
                for (const auto& teacher : teachers) {
                    teacherFile << teacher.getID() << " " << teacher.UgetFname() << " " << teacher.UgetLname() << " " << teacher.UgetAge() << std::endl;
                }

                std::cout << "Teacher removed successfully.\n";

                // Close the file
                teacherFile.close();
            }
            else {
                std::cout << "Error opening teachers.txt for writing.\n";
            }

            int noOfComplains;
            std::fstream cFile("complains.txt", std::ios::in);
            if (cFile.is_open()) {
                cFile >> noOfComplains;
                string TID, status, deptName, description;
                while (cFile >> TID >> status >> deptName) {
                    getline(cFile, description);
                    if (TID == teacherID) {
                        noOfComplains--;
                    }
                }
                cFile.close();
            }
            int cal[100], i = 0, ind = 1;
            int noOfJobs; int arr = 0, ar;
            std::fstream jFile("Job.txt", std::ios::in);
            if (jFile.is_open()) {
                jFile >> noOfJobs;
                jFile.close();
            }
            // Open complains.txt to remove the entry for the removed teacher
            std::fstream complainsFile("complains.txt", std::ios::in);
            if (complainsFile.is_open()) {
                int dum;
                string TID, status, deptName, description;
                complainsFile >> dum;
                // Create a temporary file to store the updated complaint entries
                std::fstream tempComplainsFile("tempComplains.txt", std::ios::out);
                tempComplainsFile << noOfComplains << std::endl;

                while (complainsFile >> TID >> status >> deptName) {
                    std::getline(complainsFile, description);  // Read the description with spaces

                    // Check if the entry does not match the removed teacher ID
                    if (TID != teacherID) {
                        tempComplainsFile << TID << " " << status << " " << deptName << description << std::endl;
                    }
                    else {
                        if (status == "Assigned") {
                            cal[i] = ind; i++;
                            noOfJobs--;
                        }
                    }
                    ind++;
                }
                complainsFile.close();
                remove("complains.txt");
                tempComplainsFile.close();
                rename("tempComplains.txt", "complains.txt");
                std::cout << "Complaint entry for the removed teacher removed successfully.\n";
            }
            else {
                std::cout << "Error opening complains.txt for reading.\n";
            }
            if (i > 1) {
                noOfJobs--;
            }
            for (int j = 0; j < i; j++) {
                std::fstream jobFile("Job.txt", std::ios::in);
                if (jobFile.is_open()) {
                    jobFile >> ar;
                    string complaintId, employeeId, managerId, date;

                    // Create a temporary file to store the updated job entries
                    std::fstream tempJobFile("tempJob.txt", std::ios::out);
                    tempJobFile << noOfJobs << endl;

                    while (jobFile >> complaintId >> employeeId >> managerId) {
                        getline(jobFile, date);  // Read the entire line, including spaces

                        // Check if the entry does not match the removed teacher ID
                        if (convertStringToInt(complaintId) != cal[j]) {
                            // Write the entry to the temporary file
                            tempJobFile << complaintId << " " << employeeId << " " << managerId << " " << date << std::endl;
                        }
                    }

                    // Close the original Job.txt and remove it
                    jobFile.close();
                    remove("Job.txt");
                    tempJobFile.close();

                    // Rename the temporary file to Job.txt
                    rename("tempJob.txt", "Job.txt");

                    std::cout << "Job entry for the removed teacher removed successfully.\n";
                }
                else {
                    std::cout << "Error opening Job.txt for reading.\n";
                }
                arr++;
            }
        }
        else {
            std::cout << "Teacher with ID " << teacherID << " not found.\n";
        }
    }
    void SetJobs(list<Manager>& managers, list<Employees>& emp, list<Job>& jobs)
    {
        int NoOfJobs;

        fstream jobFile("Job.txt", std::ios::in);

        jobFile >> NoOfJobs;

        for (int i = 0; i < NoOfJobs; ++i) {
            int complaintId;
            std::string employeeId, managerId, date;
            jobFile >> complaintId >> employeeId >> managerId;
            getline(jobFile >> std::ws, date);

            // Tokenize the date
            Date* d = tokenizeDate(date);

            // Find the corresponding manager, employee, and complaint
            Manager* manager = findManagerById(managers, managerId);
            Employees* employee = findEmployeeById(emp, employeeId);

            // Create a new job
            Job* newJob = new Job(complaintId, employee, manager);
            newJob->SetDate(*d);
            jobs.push_back(*newJob);
            // Add the job to the manager and employee
            if (manager) {
                manager->Set_Job(&jobs.back());
            }

            if (employee) {
                employee->Set_Job(&jobs.back());
            }

            delete d;
        }

        jobFile.close();

    }
};

int main() {
    ComplaintManagementSystem cms;
    cms.initializeSystem();
    cms.gotoxy(40, 13);
    std::cout << "Welcome to Complaint Management System\n";
    Sleep(1500);
    system("CLS");
    cms.loginInterface();

    return 0;
}