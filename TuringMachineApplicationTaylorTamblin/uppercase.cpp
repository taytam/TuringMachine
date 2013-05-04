//The Uppercase class provides methods to make a string
//or a character completely uppercase
//Module: uppercase
//Files: uppercase.h, uppercase.cpp
//Application: Turing Machine Application
//Language: C++, Standard Library
//Computer: Linux Lab Computers
//OS: Ubuntu Linux
//Course: Cpts 322 - Software Engineering I
//Author: Taylor Tamblin
//Date: 4-28-13
#include "uppercase.h"
#include <string>
using namespace std;

//name: makeUppercase(string input)
//purpose: make a string all uppercase
string Uppercase::makeUppercase(string input)
{
	string capital_input = input;
    for(int i = 0; i < capital_input.size(); i++)
    {
        if( (capital_input[i] > 96) && (capital_input[i] < 123) )
        {
            capital_input[i] += 32;
        }
    }
    return capital_input;
}

//name: makeUppercase(char input)
//purpose: make a character uppercase
char Uppercase::makeUppercase(char input)
{
	char capital_input = input;
    return toupper(capital_input);
}