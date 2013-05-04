//main function for the Turing machine.
//Module: main
//Files: main.cpp
//Application: Turing Machine Application
//Language: C++, Standard Library
//Computer: Linux Lab Computers
//OS: Ubuntu Linux
//Course: Cpts 322 - Software Engineering I
//Author: Taylor Tamblin
//Date: 4-28-13
#include "state.h"
#include "turing_machine.h"
#include "input_string_file.h"
#include "utility.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

//name: int main(int argc, char* argv[])
//purpose: get command line argument from user and verify
//that only 1 argument was entered
int main(int argc, char* argv[])
{
	Utility utility;

	if(argc == 2)
	{	
		string file(argv[1]);
		utility.run_program(file);
	}
		else
		{
			cout << "Invalid startup.  Error with command line argument.\n";
			cout << "Argument should be same name as the .str and .def files.";
			exit(1);
		}
	return 0;
}