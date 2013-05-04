#ifndef TRANSITION_FUNCTION_H
#define TRANSITION_FUNCTION_H

#include "transition.h"
#include "direction.h"
#include "uppercase.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Transition_Function
{
private:
	Uppercase uppercase;
	vector<Transition> transitions;
public:
	void load(ifstream& definition, bool& valid);
	void view() const;
	int size() const;
	string source_state (int index) const;
	char read_character(int index) const;
	string destination_state(int index) const;
	char write_character(int index) const;
	bool is_defined_transition(string source_state, char read_character, string& destination_state,
		char& write_character, direction& 	move_direction) const;
	//bool is_source_state(string state) const;
};
#endif