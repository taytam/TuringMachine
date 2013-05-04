//The Input_String_File class parses the input string file
//and stores the input strings for use by the application.
//The class can also write an input string file
//Module: input_string_file
//Files: input_string_file.h, input_string_file.cpp
//Application: Turing Machine Application
//Language: C++, Standard Library
//Computer: Linux Lab Computers
//OS: Ubuntu Linux
//Course: Cpts 322 - Software Engineering I
//Author: Taylor Tamblin
//Date: 4-28-13
#include "input_string_file.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//name: Input_String_File()
//purpose: constructor to default overwrite to false
Input_String_File::Input_String_File()
{
	overwrite = false;
}

//name: load(string value)
//purpose: load the input string list
void Input_String_File::load(string value)
{
	input_strings.push_back(value);
	loaded = true;
}

//name: view()
//purpose: print out the input strings
void Input_String_File::view() const
{
	if(input_strings.size()>0)
	{
		for(int i=0; i<input_strings.size(); i++)
		{
			cout << i+1 << ". " << input_strings[i] << endl;
		}
	}
	else
	{
		cout << "Input string list is empty!";
	}
	cout << "\n";
}

//name: file_was_modified()
//purpose: set boolean overwrite to true
void Input_String_File::file_was_modified()
{
	overwrite = true;
}

//name: is_modified()
//purpose: return overwrite, indicating if the input string
//file needs to be overwritten
bool Input_String_File::is_modified()
{
	return overwrite;
}

//name: insert(string value)
//purpose: insert a string in the input string list.
//Will not insert duplicate strings
void Input_String_File::insert(string value)
{
	//also add a check if value contains characters only from input alphabet
	bool duplicate = false;
	for(int i=0; i<input_strings.size();i++)
	{
		if(input_strings[i] == value)
			duplicate = true;
	}
	if(!duplicate)
	{
		input_strings.push_back(value);
		cout << "String successfully added!\n";
		file_was_modified();
	}
	else
		cout << "String is already in the list!\n";
}

//name: delete_string(int index)
//purpose: delete a string from the list if a correct
//string number was entered
void Input_String_File::delete_string(int index)
{
	if(index > 0)
	{
	if((input_strings.size() > 0) && (index > 0) && (input_strings.size() >= index))
	{
	input_strings[index-1].erase();
	cout << "String " << index << " was deleted!\n";
	file_was_modified();

		for(int i = index; i<input_strings.size(); i++)
		{
			//string move_string = input_strings[i];
			if(input_strings.size() > 1)
			{
				input_strings[i-1].swap(input_strings[i]);
			}
		}
		input_strings.resize(input_strings.size() - 1);
		input_strings.shrink_to_fit();
	}
	else
		cout << "Error! That string number does not exist.\n";
	}
	else
		cout << "Error! That string number does not exist.\n";
}

//name: size()
//purpose: determine how many strings are in the input string list
int Input_String_File::size()
{
	return input_strings.size();
}

//name: element(int index)
//purpose: determine if a string exists in the input string list
string Input_String_File::element(int index)
{
	if((index>=0) && (input_strings.size() > index))
	{
	return input_strings[index];
	}
	else
		cout << "Error: that number of an input string does not exist.\n";
}

//name: is_element(string value)
//purpose: get the input string at specified number
bool Input_String_File::is_element(string value)
{
	bool found = false;
    for(int i = 0; i < input_strings.size(); i++)
    {
        if (value == input_strings[i])
		{
			found = true;
            return found;
		}
    }
	return found;
}

//name: was_loaded()
//purpose: determine if the string was loaded correctly
bool Input_String_File::was_loaded()
{
	return loaded;
}

//name: write_to_file(string value)
//purpose: overwrite the .str file
void Input_String_File::write_to_file(string value)
{
	if(overwrite)
	{
		ofstream file;
		file.open(value + ".str");

		for(int i=0; i<input_strings.size(); i++)
		{
			file << input_strings[i] << "\n";
		}
		file.close();
	}
}