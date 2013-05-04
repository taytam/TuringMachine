//The Transition class of the turing machine gets information
//from a transition and provides validation for a transition.
//The Transition class will determine read character, write character
//and move direction for the transition function
//Module: transition
//Files: transition.h, transition.cpp
//Application: Turing Machine Application
//Language: C++, Standard Library
//Computer: Linux Lab Computers
//OS: Ubuntu Linux
//Course: Cpts 322 - Software Engineering I
//Author: Taylor Tamblin
//Date: 4-28-13
#include "transition.h"
#include "direction.h"
#include <string>
using namespace std;

//name: Transition(string source_state, char read_character, string destination_state, char 
//write_character, direction move_direction) : source(source_state), read(read_character), 
//destination(destination_state), write(write_character), move(move_direction)
//purpose: to initialize member attributes
Transition::Transition(string source_state, char read_character, string destination_state, char 
	write_character, direction move_direction) : source(source_state), read(read_character), 
	destination(destination_state), write(write_character), move(move_direction)
{}

//name: source_state()
//purpose: get the source of a transition
string Transition::source_state() const
{
	return source;
}

//name: read_character()
//purpose: get the read character of a transition
char Transition::read_character() const
{
	return read;
}

//name: destination_state()
//purpose: get the destination state of a transition
string Transition::destination_state() const
{
	return destination;
}

//name: write_character()
//purpose: get the write character of a transition
char Transition::write_character() const
{
	return write;
}

//name: move_direction()
//purpose: get the move direction of a transition
direction Transition::move_direction() const
{
	return move;
}