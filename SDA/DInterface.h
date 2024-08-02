#pragma once
#include<iostream>
using namespace std;
class DInterface {
public:
	virtual string getId() const = 0;
	virtual void Print() const = 0;
};