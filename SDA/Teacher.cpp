#define _CRT_SECURE_NO_WARNINGS
#include "Teacher.h"
#include <iostream>
#include<fstream>
#include<ctime>
#include<Windows.h>
#include "Date.h"
Date* tokenizeDate(const std::string& date);
string Dept_Tostring(DepartmentNames dept);

Teacher::Teacher() : User() {
    ID = '\0';
}

Teacher::Teacher(std::string fname, std::string lname, int age, std::string id) : User(fname, lname, age) {
    ID = id;
}

void Teacher::Tsetter(std::string fname, std::string lname, int age, std::string ID) {
    Usetter(fname, lname, age);
    this->ID = ID;
}

void Teacher::Print() {
    std::string fname, lname;
    int age;
    Ugetter(fname, lname, age);
    std::cout << "ID: " << this->ID << std::endl;
    std::cout << "Name: " << fname << " " << lname << std::endl;
    std::cout << "Age: " << age << std::endl;
    if (!complaints.empty()) {
        std::cout << "Complaints:\n";
        std::cout << "-------------------------\n";
        for (const auto& complaint : complaints) {
            complaint->Complain_print();
        }
    }
}

std::string Teacher::getID() const {
    return ID;
}

Complaint* Teacher::SetComplaint(string des, string dept, string status, std::list<Department>& departments, int id, string t) {
    Date* d = tokenizeDate(t);
    // Find the department based on the name
    auto it = find_if(departments.begin(), departments.end(), [dept](const Department& department) {
        return Dept_Tostring(department.Dept) == dept;
        });

    if (it != departments.end()) {
        // Create a new Complaint using the new constructor
        Complaint* newComplaint = new Complaint(des, this, &(*it), status, id);
        newComplaint->setDate(*d);
        complaints.push_back(newComplaint);

        // Add the complaint to the department
        it->AddComplaint(complaints.back());
        return newComplaint;
    }
    
}




Complaint* Teacher::file_complaint(std::list<Department>& departments, int id) {
    string t;
    time_t now = time(0);
    t = ctime(&now);
    string desc;
    string dept;
    cout << "Enter Dept: ";
    cin >> dept;
    cout << "Enter your complaint: ";
    cin.ignore();
    getline(cin, desc);

    Complaint* newCom = SetComplaint(desc, dept, "New", departments, id, t);
    UpdateFile(desc, dept, "New", t);
    return newCom;
}

void Teacher::Setcomplaint(Complaint* cmp)
{
    complaints.push_back(cmp);
}

void Teacher::UpdateFile(string des, string dept, string status, string t)
{
    
    std::fstream complaintsFile("complains.txt", std::ios::in | std::ios::out);
    int totalComplaints;
    complaintsFile >> totalComplaints;
    totalComplaints++;
    complaintsFile.seekg(0);
    complaintsFile << totalComplaints;
    complaintsFile.close();

    // Append the new complaint to the file
    std::ofstream outFile("complains.txt", std::ios::app);

    outFile << ID << " New " << dept << " " << des << "|" << t;
    outFile.close();
}

void Teacher::AddNotification(int ID)
{
    notification.push_back(ID);
}

void Teacher::RemoveNotification(int ID)
{
    notification.remove_if([ID](int value) { return value == ID; });
}

void Teacher::PrintNotification()
{
    cout << "Your Following Complaints Have Been Worked Upon:-\n";
    std::cout << "-------------------------\n";
    for (int notificationId : notification) {
        // Find the complaint with matching CID in the complaints list
        auto it = std::find_if(complaints.begin(), complaints.end(), [notificationId](Complaint* complaint) {
            return complaint->getCID() == notificationId;
            });

        // If a matching complaint is found, print its details
        if (it != complaints.end()) {
            (*it)->Complain_print();
        }
    }
    std::cout << "-------------------------\n";
}

int Teacher::getNotifications()
{
    return notification.size();
}

void Teacher::UpdateComplaint(int id)
{
    auto it = std::find_if(complaints.begin(), complaints.end(), [id](Complaint* complaint) {
        return complaint->getCID() == id;
        });

    // If a matching complaint is found, update its status to RESOLVED
    if (it != complaints.end()) {
        (*it)->SetStatus(Status::RESOLVED);
    }

}

void Teacher::DisplayInfo()
{
    std::string fname, lname;
    int age;
    Ugetter(fname, lname, age);
    std::cout << "ID: " << this->ID << std::endl;
    std::cout << "Name: " << fname << " " << lname << std::endl;
    std::cout << "Age: " << age << std::endl;
}
