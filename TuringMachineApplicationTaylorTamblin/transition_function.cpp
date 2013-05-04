//The Transition_Function class parses the definition file
//for transitions and then stores them for use
//Module: transition_function
//Files: transition_function.h, transition_function.cpp
//Application: Turing Machine Application
//Language: C++, Standard Library
//Computer: Linux Lab Computers
//OS: Ubuntu Linux
//Course: Cpts 322 - Software Engineering I
//Author: Taylor Tamblin
//Date: 4-28-13
#include "transition_function.h"
#include "transition.h"
#include "direction.h"
#include "uppercase.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

//name: load(ifstream& definition, bool& valid)
//purpose: parse the definition file for transition functions
void Transition_Function::load(ifstream& definition, bool& valid)
{
    string source_state;
    string read_character;
    string destination_state;
    string write_character;
    string direction;
    while((definition >> source_state) && (uppercase.makeUppercase(source_state) != "INITIAL_STATE:"))
    {
        definition >> read_character;
        definition >> destination_state;
        definition >> write_character;
        definition >> direction;

        if((uppercase.makeUppercase(read_character) == "INITIAL_STATE:")
                || (uppercase.makeUppercase(destination_state) == "INITIAL_STATE:")
                || (uppercase.makeUppercase(write_character) == "INITIAL_STATE:")
                || (uppercase.makeUppercase(direction) == "INITIAL_STATE:"))
        {
            cout << "Error: transition is not in the correct format.\n";
            valid = false;
            break;
        }
        if((direction.size() != 1) || ((direction[0] != 'L')
                    && (direction[0] != 'l') && (direction[0] != 'R')
                    && (direction[0] != 'r')))
        {
            cout << "Error: transition contains an invalid direction.\n";
            valid = false;
        }

        if((read_character.size() == 1) && (write_character.size() == 1)
                && (direction.size() == 1))
        {
			//load up transition
            Transition transition(source_state, read_character[0], destination_state, write_character[0], direction[0]);
            transitions.push_back(transition);
        }
    }
}

//name: view()
//purpose: print the transition functions
void Transition_Function::view() const
{
	for(int i=0; i<transitions.size(); i++)
	{
		cout << transitions[i].source_state() << ", ";
		cout << transitions[i].read_character() << ") = (";
		cout << transitions[i].destination_state() << ", ";
		cout << transitions[i].write_character() << ", ";
		cout << transitions[i].move_direction() << ")\n";
	}
}

//name: size()
//purpose: get the number of transition functions
int Transition_Function::size() const
{
	return transitions.size();
}

//name: source_state(int index)
//purpose: get the source state of the transition
string Transition_Function::source_state(int index) const
{
	return transitions[index].source_state();
}

//name: read_character(int index)
//purpose: get the read character of the transition
char Transition_Function::read_character(int index) const
{
	return transitions[index].read_character();
}

//name: destination_state(int index)
//purpose: get the destination state of the transition
string Transition_Function::destination_state(int index) const
{
	return transitions[index].destination_state();
}

//name: write_character(int index)
//purpose: get the write character of the transition
char Transition_Function::write_character(int index) const
{
	return transitions[index].write_character();
}

//name: is_defined_transition(string source state, char read_character,
//string& destination_state, char& write_character, direction& move_direction)
//purpose: determine if the transition state is a defined transition and then return
//the destination state, write character, and move direction for the transition to be made
bool Transition_Function::is_defined_transition(string source_state, char read_character,
	string& destination_state, char& write_character, direction& move_direction) const
{
	bool is_defined = false;
	for(int index = 0; index<transitions.size(); index++)
	if ((transitions[index].source_state()==source_state) && (transitions[index].read_character()==read_character))
	{
		destination_state = transitions[index].destination_state();
		write_character = transitions[index].write_character();
		move_direction = transitions[index].move_direction();
		is_defined = true;
		return is_defined;
	}
	return is_defined;
}

//bool Transition_Function::is_source_state(string state) const
//{
//	return false;
//}