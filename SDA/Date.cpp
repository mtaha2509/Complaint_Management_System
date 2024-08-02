/**
 * Project Untitled
 */


#include "Date.h"
#include<iostream>
#include <iomanip> 
#include <string>

using namespace std;
/**
 * Date implementation
 */

void Date::Print() const
{
	cout << day << " " << month << " " << date << " " << hr << ":"<<mins << ":" << sec <<" "<< year << endl;
}

string Date::getMonth() const
{
	return month;
}

int Date::getYear() const
{
	return year;
}

int Date::getDate() const
{
	return date;
}

std::string Date::getdate() {
    // Format the date
    string formattedDate = day + " " + month + "  " + std::to_string(date) +
        " " + (hr < 10 ? "0" : "") + std::to_string(hr) +
        ":" + (mins < 10 ? "0" : "") + std::to_string(mins) +
        ":" + (sec < 10 ? "0" : "") + std::to_string(sec) +
        " " + std::to_string(year);
    return formattedDate;
}







