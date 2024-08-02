/**
 * Project Untitled
 */


#ifndef _DIRECTOR_H
#define _DIRECTOR_H

#include "User.h"
#include "DInterface.h"

class Director: public User, public DInterface {
	string Id;
public:
	Director() { Id = '\0'; }
	Director(string id, string fname, string lname, int age) :User(fname,lname,age) { Id = id; }
	string getId() const;
	void Print() const;
};

#endif //_DIRECTOR_H