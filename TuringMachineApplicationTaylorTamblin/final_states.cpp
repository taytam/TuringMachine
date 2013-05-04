//The Final_States class parses the definition file for the
//final states of the Turing machine.
//Module: final_states
//Files: final_states.h, final_states.cpp
//Application: Turing Machine Application
//Language: C++, Standard Library
//Computer: Linux Lab Computers
//OS: Ubuntu Linux
//Course: Cpts 322 - Software Engineering I
//Author: Taylor Tamblin
//Date: 4-28-13
#include "final_states.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

//name: load(ifstream& definition, bool &valid)
//purpose: parse the definition file for final states
void Final_States::load(ifstream& definition, bool &valid)
{
    string value;
    while((definition >> value))
    {
        Names.push_back(value);
    }
}

//name: view()
//purpose: print out the final states
void Final_States::view() const
{
	for(int i = 0; i<Names.size(); i++)
	{
		cout << Names[i] << endl;
	}
}

//name: size()
//purpose: return the number of final states
int Final_States::size()
{
	return Names.size();
}

//name: element(int index)
//purpose: return the final state contained at specified index
string Final_States::element(int index)
{
	return Names[index];
}

//name: is_element(string value)
//purpose: determine if a final state is contained in final states
bool Final_States::is_element(string value)
{
	bool found = false;
		for(int i = 0; i<Names.size(); i++)
		{
		if(Names[i] == value)
		{
			found = true;
			return found;
		}
		return found;
	}
}