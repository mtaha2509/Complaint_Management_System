#include "Administrator.h"
void Administrator::Admin_setter(string fname, string lname, int age, string id) {
	Usetter(fname, lname, age);
	ID = id;
}

string Administrator::getId() const{
	return ID;
}

void Administrator::Print() {
    std::string fname, lname;
    int age;
    Ugetter(fname, lname, age);
    std::cout << "ID: " << this->ID << std::endl;
    std::cout << "Name: " << fname << " " << lname << std::endl;
    std::cout << "Age: " << age << std::endl;
}