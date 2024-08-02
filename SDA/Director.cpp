/**
 * Project Untitled
 */


#include "Director.h"

/**
 * Director implementation
 */


string Director::getId() const
{
    return Id;
}

void Director::Print() const
{
    std::cout << "-------------------------\n";
	
	cout << "ID: " << this->Id << endl;
	cout << "Name: " << UgetFname() << " " << UgetLname() << endl;
	cout << "Age: " << UgetAge() << endl;

	std::cout << "-------------------------\n";
}
