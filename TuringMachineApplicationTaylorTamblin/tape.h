#ifndef TAPE_H
#define TAPE_H

#include "direction.h"
#include "uppercase.h"
#include <string>
#include <fstream>
using namespace std;

class Tape
{
private:
	Uppercase uppercase;
	string cells;
	int current_cell;
	char blank;
public:
	Tape();
	void load(ifstream& Definition, bool& valid);
	void view() const;
	void initialize(string input_string);
	void update(char write_character, direction move_direction);
	string left(int maximum_number_of_cells) const;
	string right(int maximum_number_of_cells) const;
	char current_character() const;
	char blank_character() const;
	bool is_first_cell() const;
};

#endif