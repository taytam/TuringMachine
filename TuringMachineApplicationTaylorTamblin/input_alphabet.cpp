//The Input_Alphabet class parses the definition file for the
//input alphabet of the Turing machine.
//Module: input_alphabet
//Files: input_alphabet.h, input_alphabet.cpp
//Application: Turing Machine Application
//Language: C++, Standard Library
//Computer: Linux Lab Computers
//OS: Ubuntu Linux
//Course: Cpts 322 - Software Engineering I
//Author: Taylor Tamblin
//Date: 4-28-13#include "input_alphabet.h"
#include "input_alphabet.h"
#include "uppercase.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

//name: load(ifstream& definition, bool& valid)
//purpose: parse the definition file for input alphabet
void Input_Alphabet::load(ifstream& definition, bool& valid)
{
    string value;
    while((definition >> value) && (uppercase.makeUppercase(value) != "TAPE_ALPHABET:"))
    {
        if((value.size() == 1) && (value[0] != '\\') &&
			(value[0] != '[') && (value[0] != ']') &&
			(value[0] != '<') && (value[0] != '>'))

            Alphabet.push_back(value[0]);
        else
        {
            cout << "Error: input alphabet contains an illegal character" << endl;
            valid = false;
        }
    }
}

//name: view()
//purpose: print out the input alphabet
void Input_Alphabet::view() const
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

//name: size()
//purpose: get the size of the input alphabet
int Input_Alphabet::size()
{
	return Alphabet.size();
}

//name: element(int index)
//purpose: get the state at specified index
char Input_Alphabet::element(int index)
{
	return Alphabet[index];
}

//name: is_element(char value)
//purpose: determine if character is contained in input alphabet
bool Input_Alphabet::is_element(char value)
{
	bool found = false;
	for(int i=0; i<Alphabet.size(); i++)
	{
		if(Alphabet[i] == value)
		{
			found = true;
			return found;
		}
	}
	return found;
}