//The Tape_Alphabet class parses the definition file and
//stores the characters that the tape can contain.
//The tape must include at least all of the characters
//contained in the input alphabet
//Module: tape_alphabet
//Files: tape_alphabet.h, tape_alphabet.cpp
//Application: Turing Machine Application
//Language: C++, Standard Library
//Computer: Linux Lab Computers
//OS: Ubuntu Linux
//Course: Cpts 322 - Software Engineering I
//Author: Taylor Tamblin
//Date: 4-28-13
#include "tape_alphabet.h"
#include "uppercase.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

//name: load(ifstream& definition, bool& valid)
//purpose: parse the definition file for the tape alphabet
void Tape_Alphabet::load(ifstream& definition, bool& valid)
{
    string value;

    while((definition>>value) && (uppercase.makeUppercase(value) != "TRANSITION_FUNCTION:"))
    {
        if((value.size() == 1) && (value[0] != '\\') && (value[0] != '[') &&
			(value[0] != ']') && (value[0] != '<') && (value[0] != '>'))

            Alphabet.push_back(value[0]);
        else
        {
            cout << "Error: illegal character in tape alphabet" << endl;
            valid = false;
        }
    }
}

//name: view()
//purpose: print the tape alphabet
void Tape_Alphabet::view() const
{
	cout << "{";
	for(int i=0; i<Alphabet.size(); i++)
	{
		cout << Alphabet[i];
		if(Alphabet.size()-1 != i)
			cout << ",";
	}
	cout << "}\n\n";
}

//name: is_element(char value)
//purpose: determine if a character is contained in the
//tape alphabet
bool Tape_Alphabet::is_element(char value) const
{
	bool found = false;

	for(int i=0; i<Alphabet.size(); i++)
	{
		if (Alphabet[i] == value)
		{
			found = true;
			return found;
		}
	}

	return found;
}