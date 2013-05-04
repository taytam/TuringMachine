//The States class parses the definition file for the
//states of the Turing machine.
//Module: states
//Files: states.h, states.cpp
//Application: Turing Machine Application
//Language: C++, Standard Library
//Computer: Linux Lab Computers
//OS: Ubuntu Linux
//Course: Cpts 322 - Software Engineering I
//Author: Taylor Tamblin
//Date: 4-28-13
#include "states.h"
#include "uppercase.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

//name: load(ifstream& definition, bool &valid)
//purpose: parse the definition file for states
void States::load(ifstream& definition, bool &valid)
{
	string value;
	while ((definition>>value) && (uppercase.makeUppercase(value) != "INPUT_ALPHABET:"))
    {
        for(int i = 0; i < value.size(); i++)
        {
			//validate the states
            if(!(((value[i] > 96) && (value[i] < 123)) || ((value[i] > 64) && (value[i] < 91)) ||
				((value[i] > 47) && (value[i] < 58)) || (value[i] == '_')))
            {
                cout << "File error: state contains an illegal character." << endl;
                valid = false;
                break;
            }
        }
        if(is_element(value))
        {
            cout << "File error: a duplicate state was found." << endl;
            valid = false;
        }
        else
            Names.push_back(value);
    }
}

//name: view()
//purpose: print the states of the Turing machine
void States::view() const
{
	//cout << "States = ";

	for(int i = 0; i<Names.size(); i++)
	{
		cout << Names[i];
		if(Names.size()-1 != i)
			cout << ", ";
	}
	cout << "\n\n";
}

//name: is_element(string value)
//purpose: determine if a state exists in the Turing machine states
bool States::is_element(string value)
{
	bool found = false;

	for(int i = 0; i<Names.size(); i++)
	{
		if(Names[i] == value)
		{
			found = true;
			return found;
		}
	}
	return found;
}