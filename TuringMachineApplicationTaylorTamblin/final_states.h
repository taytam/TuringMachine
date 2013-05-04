#ifndef FINAL_STATES_H
#define FINAL_STATES_H
#include "uppercase.h"
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Final_States
{
private:
	Uppercase uppercase;
	vector<string> Names;
public:
	void load(ifstream& definition, bool &valid);
	void view() const;
	int size();
	string element(int index);
	bool is_element(string value);

};

#endif