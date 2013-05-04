//The Tape class parses the definition file for the blank
//character.  The Tape class provides viewing of the Turing
//machine tape.
//Module: tape
//Files: tape.h, tape.cpp
//Application: Turing Machine Application
//Language: C++, Standard Library
//Computer: Linux Lab Computers
//OS: Ubuntu Linux
//Course: Cpts 322 - Software Engineering I
//Author: Taylor Tamblin
//Date: 4-28-13
#include "tape.h"
#include "direction.h"
#include "uppercase.h"
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

//name: Tape()
//purpose: initialize member attributes
Tape::Tape() : cells(" "), current_cell(0), blank(' ')
{
}

//name: load(ifstream& definition, bool& valid)
//purpose: parse the definition file for the blank character
void Tape::load(ifstream& definition, bool& valid)
{
	string value;

	if((definition >> value) &&	(value.length()==1) && (value[0] != '\\') &&
	(value[0] != '[') && (value[0] != ']') && (value[0] != '<') &&
	(value[0] != '>') && (value[0] != '!') && (value[0] <= '~'))
		blank = value[0];
	else
	{
		cout << "Error: illegal blank character.\n";
		valid = false;
	}
	if((!(definition>>value)) || (uppercase.makeUppercase(value) != "FINAL_STATES:"))
	{
		cout << "Error: missing keyword after blank character.\n";
		valid = false;
	}
}

//name: view()
//purpose: print the blank character
void Tape::view() const
{
	cout << blank << "\n";
}

//name: initialize(string input_string)
//purpose: reset the tape (member variables)
void Tape::initialize(string input_string)
{
	cells = input_string + blank;
	current_cell = 0;
}

//name: update(char write_character, direction move_direction)
//purpose: move either left or right on the Turing machine tape
//and write the write character to the current cell
void Tape::update(char write_character, direction move_direction)
{
	move_direction = uppercase.makeUppercase(move_direction);

	if((move_direction == 'L') && (current_cell==0))
	//throw crash("Left move from first cell");
	{
	cout << "Error: Left move from first cell." << endl;
	return;}

	if((move_direction=='R') &&
	(current_cell == cells.length()-1))
		cells += blank;
		cells[current_cell]=write_character;

	if(move_direction == 'L')
		--current_cell;
	else
		++current_cell;
}

//name: left(int maximum_number_of_cells)
//purpose: perform a left movement on the Turing machine tape
string Tape::left(int maximum_number_of_cells) const
{
	int first_cell = max(0, current_cell - maximum_number_of_cells);
	string value = cells.substr(first_cell, current_cell - first_cell);
	if(value.length() < current_cell)
	value.insert(0, "<");
	return value;
}

//name: right(int maximum_number_of_cells)
//purpose: perform a right movement on the Turing machine tape
string Tape::right(int maximum_number_of_cells) const
{
	int end_cell = cells.length()-1;
	while((end_cell >= current_cell) &&
		(cells[end_cell]==blank))
	--end_cell;
	int last_cell = min(end_cell, current_cell+maximum_number_of_cells-1);
string value=cells.substr(current_cell, last_cell - current_cell+1);
if(value.length() < end_cell - current_cell + 1)
	value.append(">");
	return value;
}

//name: current_character()
//purpose: get the character at the current cell
char Tape::current_character() const
{
	return cells[current_cell];
}

//name: blank_character()
//purpose: get the blank character of the Turing machine
char Tape::blank_character() const
{
	return blank;
}

//name: is_first_cell()
//purpose: determine if the cell is the first cell
//on the tape
bool Tape::is_first_cell() const
{
	return(current_cell == 0);
}