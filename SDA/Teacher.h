#ifndef _TEACHER_H
#define _TEACHER_H

#include "User.h"
#include "Complaint.h"
#include "TInterface.h"
#include <list>
#include "Observer.h"

class Teacher : public User , public TInterface, public Observer{
    std::string ID;
    std::list<Complaint*> complaints;
    list<int> notification;
public:
    Teacher();
    Teacher(std::string fname, std::string lname, int age, std::string id);
    void Tsetter(std::string fname, std::string lname, int age, std::string ID);
    void Print();
    std::string getID() const;
    Complaint* SetComplaint(std::string des, std::string dept, std::string status, std::list<Department>& departments, int id, string t);
    Complaint* file_complaint(std::list<Department>& departments, int id);
    void Setcomplaint(Complaint* cmp);
    void UpdateFile(string des, string dept, string status, string t);
    void AddNotification(int ID);
    void RemoveNotification(int ID);
    void PrintNotification();
    int getNotifications();
    void UpdateComplaint(int id);
    void DisplayInfo();
    virtual void update(int notificationID) override {
        AddNotification(notificationID);
    }
};

#endif //_TEACHER_H
