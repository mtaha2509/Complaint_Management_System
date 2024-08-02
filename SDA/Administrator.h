/**
 * Project Untitled
 */


#ifndef _ADMINISTRATOR_H
#define _ADMINISTRATOR_H

#include "User.h"
#include "AInterface.h"

class Administrator: public User, public  AInterface{
	string ID;
public:
	Administrator() {
		ID = '\0';
	}

	Administrator(string fname, string lname, int age, string id) : User(fname, lname, age) {
		ID = id;
	}
	void Admin_setter(string, string, int, string);
	string getId() const;
	void Print();
};

#endif //_ADMINISTRATOR_H