#ifndef _USER_H
#define _USER_H

//#include "Teacher.h"
#include <string.h>
#include <iostream>
using namespace std;


class User {
	string first_name;
	string last_name;
	int age;
public:
	User();
	User(string fname, string lname, int age);
	void Usetter(string fname, string lname, int age);
	void Ugetter(string &fname, string &lname, int &age);
	string UgetFname() const;
	string UgetLname() const;
	int UgetAge() const;
};

#endif //_USER_H