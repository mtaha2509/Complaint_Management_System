/**
 * Project Untitled
 */


#ifndef _DATE_H
#define _DATE_H
#include <string>
using namespace std;

class Date {
	string day;
	string month;
	int date;
	int year;
	int hr;
	int mins;
	int sec;
public:
	Date() : date(0), year(0), hr(0), mins(0), sec(0) {}

	Date(const std::string& day, const std::string& month, int date, int hr, int mins, int sec, int year)
		: day(day), month(month), date(date), year(year), hr(hr), mins(mins), sec(sec) {}
	void Print() const;
	string getMonth() const;
	int getYear() const;
	int getDate() const;
	string getdate();
};


#endif //_DATE_H