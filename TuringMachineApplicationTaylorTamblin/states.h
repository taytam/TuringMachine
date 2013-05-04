#ifndef STATES_H
#define STATES_H
#include "uppercase.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class States
{
private:
	Uppercase uppercase;
	vector<string> Names;
public:
	void load(ifstream& definition, bool &valid);
	void view() const;
	bool is_element(string value);
};

#endif