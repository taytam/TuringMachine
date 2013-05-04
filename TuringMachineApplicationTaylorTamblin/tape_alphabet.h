#ifndef TAPE_ALPHABET_H
#define TAPE_ALPHABET_H
#include "uppercase.h"
#include <vector>
#include <fstream>
using namespace std;


class Tape_Alphabet
{
private:
	Uppercase uppercase;
	vector<char> Alphabet;
public:
	void load(ifstream& definition, bool& valid);
	void view() const;
	bool is_element(char value) const;

};

#endif