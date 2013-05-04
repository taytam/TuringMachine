#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H

#include "tape.h"
#include "input_alphabet.h"
#include "tape_alphabet.h"
#include "transition_function.h"
#include "states.h"
#include "final_states.h"
#include <string>
#include <vector>
using namespace std;

class Turing_Machine
{
private:
	Uppercase uppercase;
	Tape tape;
	Input_Alphabet input_alphabet;
	Tape_Alphabet tape_alphabet;
	States states;
	Final_States final_states;
	Transition_Function transition_function;
	vector<string> description;
	string initial_state;
	string current_state;
	string original_input_string;
	int number_of_transitions;
	int maximum_transitions;
	int maximum_cells;
	bool valid;
	bool used;
	bool operating;
	bool accepted;
	bool rejected;
public:
	Turing_Machine(string definition_file_name);
	void view_definition() const;
	void view_instantaneous_description(int maximum_number_of_cells) const;
	void initialize(string input_string);
	void perform_transitions(int maximum_number_of_transitions);
	void terminate_operation();
	string input_string() const;
	int total_number_of_transitions() const;
	int maximum_number_of_transitions() const;
	int maximum_number_of_cells() const;
	void change_max_cells(int newMax);
	void change_max_transitions(int newMax);
	bool is_valid_definition() const;
	bool is_valid_input_string(string value);
	bool is_used() const;
	bool is_operating() const;
	bool is_accepted_input_string() const;
	bool is_rejected_input_string() const;
};
#endif