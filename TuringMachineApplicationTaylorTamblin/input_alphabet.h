#ifndef INPUT_ALPHABET_H
#define INPUT_ALPHABET_H
#include "uppercase.h"
#include <vector>
#include <fstream>
using namespace std;

class Input_Alphabet
{
private:
	Uppercase uppercase;
	vector<char> Alphabet;
public:
	void load(ifstream& definition, bool &valid);
	void view() const;
	int size();
	char element(int index);
	bool is_element(char value);
};

#endif