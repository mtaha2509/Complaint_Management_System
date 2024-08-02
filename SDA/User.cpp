#include "User.h"
User::User()
{
	first_name = '\0';
	last_name = '\0';
	age = 0;
}

User::User(string fname, string lname, int age)
{
	first_name = fname;
	last_name = lname;
	this->age = age;
}

void User::Usetter(string fname, string lname, int age)
{
	first_name = fname;
	last_name = lname;
	this->age = age;
}

void User::Ugetter(string& fname, string& lname, int& age)
{
	fname = first_name;
	lname = last_name;
	age = this->age;
}

string User::UgetFname() const
{
	return first_name;
}

string User::UgetLname() const
{
	return last_name;
}

int User::UgetAge() const
{
	return age;
}
