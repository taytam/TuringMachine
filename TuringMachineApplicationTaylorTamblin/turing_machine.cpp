//The Turing_Machine class provides access to the Turing machine
//of the application.  The Turing_Machine class is composed of most
//of the classes in the application.
//Module: turing_machine
//Files: turing_machine.h, turing_machine.cpp
//Application: Turing Machine Application
//Language: C++, Standard Library
//Computer: Linux Lab Computers
//OS: Ubuntu Linux
//Course: Cpts 322 - Software Engineering I
//Author: Taylor Tamblin
//Date: 4-28-13
#include "tape.h"
#include "input_alphabet.h"
#include "tape_alphabet.h"
#include "transition_function.h"
#include "turing_machine.h"
#include "states.h"
#include "final_states.h"
#include "uppercase.h"
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

//name: Turing_Machine(string definition_file_name)
//purpose: parse the definition file and load data from it.
//makes calls to other class load functions
Turing_Machine::Turing_Machine(string definition_file_name)
{
		//initialize attributes
		maximum_transitions = 1;
		maximum_cells = 32;
		number_of_transitions = 0;
		valid = true;
		used = false;
		operating = false;
		accepted = false;
		rejected = false;
		string value;

		//if(definition_file_name.substr(definition_file_name.find_last_of(".") + 1) == "def")

			//cout << "File is a .def file" << endl;
			ifstream definition(definition_file_name + ".def");
			if(definition)
			{

			while((definition>>value) && (uppercase.makeUppercase(value) != "STATES:"))
			{
				description.push_back(value);
			}
		
			states.load(definition, valid); //load states
			input_alphabet.load(definition, valid); //load input alphabet
			tape_alphabet.load(definition, valid); //load tape alphabet

		 for(int i = 0; i < input_alphabet.size(); i++)
			{
			if(!(tape_alphabet.is_element(input_alphabet.element(i))))
				{
				cout << "File error: Input alphabet contains a character not in the tape alphabet!" << endl;
				valid = false;
				}
			}
		transition_function.load(definition, valid); //load transition function
		//check the source state, read character, destination state, and write characters of the transition
		for(int i = 0; i < transition_function.size(); i++)
		{
		  if(!(states.is_element(transition_function.source_state(i))))
			{
            cout << "Error: transition contains an invalid source state.\n";
            valid = false;
			}
			if(!(tape_alphabet.is_element(transition_function.read_character(i))))
			{
            cout << "Error: transition contains and invalid read character.\n";
            valid = false;
			}
			if(!(states.is_element(transition_function.destination_state(i))))
			{
			    cout << "Error: transition contains an invalid destination state.\n";
			    valid = false;
			}
			if(!(tape_alphabet.is_element(transition_function.write_character(i))))
			{
			    cout << "Error: transition contains an invalid write character.\n";
				valid = false;
			}
		}
		bool set_initial_state = false;

		while((definition >> value) && (uppercase.makeUppercase(value) != "BLANK_CHARACTER:"))
		{
			if(!(states.is_element(value)))
			{
			    cout << "Error: initial state is not a valid state.\n";
			    valid = false;
			}
			if(set_initial_state == false)
			{
            initial_state = value;
            set_initial_state = true;
			}
			else
			{
				cout << "Error: only one initial state is allowed.\n";
				valid = false;
			}
		}
		tape.load(definition, valid); //load tape
		final_states.load(definition, valid); //load final states
			for(int i = 0; i < final_states.size(); i++)
			{
				if(!states.is_element(final_states.element(i)))
				{
				  cout << "Error: final state is not a valid state" << endl;
				  valid = false;
				}
			}
		}
			else
			{
				valid = false;
			}
	}

//name: view_definition()
//purpose: view the definition of the Turing machine
void Turing_Machine::view_definition() const
{
		//cout << "Description = ";

		for(int i = 0; i<description.size(); i++)
		{
			cout << description[i] << " ";
		}
		cout << "\n\n";
		//cout << "Formal specification: " << endl;
		cout << "M = (Q, Sigma, Gamma, delta, q0, B, F)" << "\n\n";
		cout << "Q = ";
		states.view();
		cout << "Epsilon = ";
		input_alphabet.view();
		cout << "Gamma = ";
		tape_alphabet.view();
		cout << "delta = " << "\n";
		transition_function.view(); cout << "\n";
		cout << "q0 = " << initial_state << "\n\n";
		cout << "B = ";
		tape.view(); cout << "\n";
		cout << "F = ";
		final_states.view(); cout << "\n";
}

//name: view_instantaneous_description(int maximum_number_of_cells)
//purpose: view the instantaneous description of the Turing machine
void Turing_Machine::view_instantaneous_description(int maximum_number_of_cells) const
{
		cout << number_of_transitions << ". ";
		cout << tape.left(maximum_number_of_cells) << "[" << current_state << "]" << tape.right(maximum_number_of_cells);
		cout << "\n";
}

//name: initialize(string input_string)
//purpose: initialize values before performing input string operations
void Turing_Machine::initialize(string input_string)
{	
		used = true;
		operating = true;
		accepted = false;
		rejected = false;
		number_of_transitions = 0;
		original_input_string = input_string;
		current_state = initial_state;
		tape.initialize(input_string);

		number_of_transitions = 0;

}

//name: perform_transitions(int maximum_number_of_transitions)
//purpose: perform transitions on the input string
void Turing_Machine::perform_transitions(int maximum_number_of_transitions)
{
		string destination_state;
		char write_character;
		direction move_direction;
		
		for(int i=0; i<maximum_transitions; i++)
		{
		//check if transition is defined
		if(transition_function.is_defined_transition(current_state, tape.current_character(),
			destination_state, write_character, move_direction))
			{
			tape.update(write_character, move_direction);
			current_state = destination_state;
			number_of_transitions++;

				if(final_states.is_element(destination_state))
					{
					accepted = true;
					operating = false;
					cout << "Input string " << input_string() << " ";
					cout << "accepted in " << total_number_of_transitions() << " transitions.\n";
					return;
					}
			}
			else
				{
				rejected = true;
				operating = false;
				cout << "Input string " << input_string() << " ";
				cout << "rejected in " << total_number_of_transitions() << " transitions.\n";
				return;
				}
			}
}

//name: terminate_operations()
//purpose: set operating boolean to false
void Turing_Machine::terminate_operation()
{
	operating = false;
}

//name: input_string
//purpose: get the input string the Turing machine is
//currently operating on
string Turing_Machine::input_string() const
{
	return original_input_string;
}

//name: total_number_of_transitions()
//purpose: get the number of transitions performed so far
int Turing_Machine::total_number_of_transitions() const
{
	return number_of_transitions;
}

//name: maximum_number_of_transitions
//purpose: get the number of max transitions
int Turing_Machine::maximum_number_of_transitions() const
{
	return maximum_transitions;
}

//name: maximum_number_of_cells()
//purpose: get the number of max cells
int Turing_Machine::maximum_number_of_cells() const
{
	return maximum_cells;
}

//name: change_max_cells(int newMax)
//purpose: change the maximum cells
void Turing_Machine::change_max_cells(int newMax)
{
	maximum_cells = newMax;
}

//name: change_max_transitions(int newMax)
//purpose: change the maximum transitions
void Turing_Machine::change_max_transitions(int newMax)
{
	maximum_transitions = newMax;
}

//name: is_valid_definition()
//purpose: get boolean stating if the definition is valid
bool Turing_Machine::is_valid_definition() const
{
	return valid;
}

//name: is_valid_input_string(string value)
//purpose: determine if the input string is a valid input string
bool Turing_Machine::is_valid_input_string(string value)
{
	bool valid_input_string = true;
	for(int i=0; i<value.size(); i++)
	{
		if(!(input_alphabet.is_element(value[i])))
		{
			valid_input_string = false;
		}
	}
		return valid_input_string;
}

//name: is_used()
//purpose: determines if the input string is used
bool Turing_Machine::is_used() const
{
	return used;
}

//name: is_operating()
//purpose: determine if the Turing machine is in operation
bool Turing_Machine::is_operating() const
{
	return operating;
}

//name: is_accepted_input_string
//purpose: get boolean stating if the input string was accepted
bool Turing_Machine::is_accepted_input_string() const
{
	return accepted;
}

//name: is_rejected_input_string()
//purpose: get boolean stating if the input string was rejected
bool Turing_Machine::is_rejected_input_string() const
{
	return rejected;
}