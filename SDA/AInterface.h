#pragma once
#include<iostream>
using namespace std;
class AInterface {
public:
	virtual void Admin_setter(string, string, int, string) = 0;
	virtual string getId() const = 0;
	virtual void Print() = 0;
};