//The Utility class provides a method to run the program
//if the argument passed in on the command line was in valid form
//Module: utility
//Files: utility.h, utility.cpp
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

//name: run_program(string file)
//purpose: run the Turing machine application while
//accepting input commands from the user during operation
void Utility::run_program(string file)
{
	Uppercase uppercase;
	const int success(0);
	bool running = false;
	bool helpActivated = false;
	//cout << "Enter a .def file to read in (must also type .def extension): ";
	//cin >> file;
	Turing_Machine tm(file);
	Input_String_File input_strings;

	//load input string file if it exists
	ifstream inputFileString(file + ".str");
    if(inputFileString)
    {
        string value;
        while(inputFileString>>value)
        {
            if(tm.is_valid_input_string(value))
                input_strings.load(value);
            else
            {
                cout << "An invalid input string was discarded.\n";
                //input_strings.is_modified(true);
            }
        }
    }
    inputFileString.close();
	//Input_String_File input_strings(file);

	if((tm.is_valid_definition()) && (input_strings.was_loaded()))
	{
		running = true;
	}
	else
	{
		running = false;
	}


	while(running){
		bool validCommand = false; //used to verify the command entered matches one of the program commands
		string input; //used for user input for commands
		char command; //command entered by user in character form
		do
		{
			cout << "Command: ";
			getline(cin, input);
			if(input.size() == 1)
			{
				command = input.front(); //get only the first char of the string

		if((command == 'X') || (command == 'x') || //exit command
			(command == 'R') || (command == 'r') || //run command
			(command == 'H') || (command == 'h') || //help command
			(command == 'W') || (command == 'w') || //show command
			(command == 'V') || (command == 'v') || //view command
			(command == 'E') || (command == 'e') || //set command
			(command == 'L') || (command == 'l') || //list command
			(command == 'T') || (command == 't') || //truncate command
			(command == 'I') || (command == 'i') || //insert command
			(command == 'D') || (command == 'd') || //delete command
			(command == 'Q') || (command == 'q')) //quit command
				{
					validCommand = true;
				}
			}
		}while(!validCommand); //run loop until valid command was entered

		command = uppercase.makeUppercase(command);
		switch(command)
		{
		//exit command
		case 'X':
			//no help message here because the program closes without warning
			//unless the input string file was altered
			tm.terminate_operation();
			if(input_strings.is_modified()) //if input string file was changed
			{
				input_strings.write_to_file(file);
				cout << "Changes were made to the input string file, file overwritten.\n";
			}
			running = false;
			break;
		//help command
		case 'H':
			if(!helpActivated)
			{
			cout << "Help activated\n" << endl;
			helpActivated = true;
			cout << "Commands available:\n";

			cout << "D - Delete - Delete an input string from the input string list.\n";
			cout << "X - Exit - Exit the application immediately.\n";
			cout << "H - Help - Toggle program help. Displays help prompts for the user during operation.\n";
			cout << "I - Insert - Insert an input string into the input string list.\n";
			cout << "L - List - Print a numbered list of the input strings.\n";
			cout << "Q - Quit - Quit operation of the Turing machine on an input string.\n";
			cout << "R - Run - Run the Turing machine on input strings.\n";
			cout << "E - Set - Set the maximum number of transitions to perform during operation of the Turing machine on an input string.\n";
			cout << "W - Show - Show the status of the application.\n";
			cout << "T - Truncate - Truncate instantaneous descriptions.\n";
			cout << "V - View - View the Turing machine.\n\n";
			//write out the help information for all 11 commands here
			}
			else
			{
				helpActivated = false;
				cout << "Help deactivated." << endl;
			}

			break;
			//run command
		case 'R':
			if(helpActivated)
			{
				cout << "\nThe Run command runs the Turing machine loaded from a definition file on ";
				cout << "a specified string from the input string list.\n";
				cout << "Type in the positive integer number of the string you wish ";
				cout << "to perform operation on.  The Turing machine will make the maximum number ";
				cout << "of operations everytime you use the run command until the string is either ";
				cout << "accepted or rejected.  It is suggested to type the 'L' command to view the ";
				cout << "current list of strings available along with their numbers in the list.\n\n";
			}
			if(!(tm.is_operating()))
			{
			int run_string;
			bool valid_run_string;
			valid_run_string = true;
			cout << "Input string number: ";
			getline(cin, input);
			if(input.size() > 0) //if something was entered
			{
				for(unsigned i = 0; i<input.size(); i++)
				{
					if((input[i] < '0') || (input[i] > '9'))
					{
						cout << "Error! Must enter number of the string to run (integer value).\n";
						valid_run_string = false;
						break;
					}		
				}
				if(valid_run_string)
				{
					run_string = atoi(input.c_str()); //convert string to int
					if(!(run_string>input_strings.size()))
					{
					tm.initialize(input_strings.element((run_string-1)));
					tm.view_instantaneous_description(tm.maximum_number_of_transitions());
					tm.perform_transitions(tm.maximum_number_of_transitions());
					if(!(tm.is_rejected_input_string()))
					tm.view_instantaneous_description(tm.maximum_number_of_cells());

					//if(tm.is_accepted_input_string())
					//	cout << "accepted in " << tm.total_number_of_transitions() << " transitions.\n";
					//else
						if(tm.is_rejected_input_string())
						{
							//cout << "Input string " << tm.input_string() << " ";
							//cout << "rejected in " << tm.total_number_of_transitions() << " transitions.\n";
						}
					}
					else
						cout << "Error: number entered exceeds number of strings in input string file.\n";
					}
				}
			}
			else
			{
				//continue operation of tm on string with each command: r

				tm.perform_transitions(tm.maximum_number_of_transitions());
				if((tm.is_operating()))
				{
					tm.view_instantaneous_description(tm.maximum_number_of_cells());
				}

				//if((tm.is_accepted_input_string()) && !(tm.is_operating()))
				//{
				//	cout << "Input string " << tm.input_string() << " ";
				//	cout << "accepted in " << tm.total_number_of_transitions() << " transitions.\n";
				//}
			}
				
			break;
			//view command
		case 'V':
			if(helpActivated)
			{
				cout << "\nThe View command will allow you to view the currently loaded Turing machine.\n";
				cout << "A description of the Turing machine is displayed, followed by the definition of the Turing machine.\n";
				cout << "The Turing machine is specified by the mathematical formula M = (Q, Epsilon, Gamma, delta, q0, B, F), where\n\n";
				cout << "Q = finite set of states.\n";
				cout << "Epsilon = finite input alphabet.\n";
				cout << "Gamma = finite tape alphabet.\n";
				cout << "delta = transition functions.\n";
				cout << "q0 = initial state.\n";
				cout << "B = blank symbol.\n";
				cout << "F = set of final states.\n";
			}
			cout << "\n";
			tm.view_definition();
			break;
			//show command
		case 'W':
			if(helpActivated)
			{
				cout << "\nThe Show command displays information about the application.  The following information is displayed:\n";
				cout << "Course = course the application was written for.\n";
				cout << "Semester = the semester the course was taken.\n";
				cout << "Year = the year the course was taken.\n";
				cout << "Instructor = the instructor of the course.\n";
				cout << "Author = the creator of the application.\n";
				cout << "Version of Application = version of the current application.\n";
				cout << "Configuration Settings = configuration settings for the Turing machine.  Includes:\n";
				cout << "\tMax number of transitions = max transitions to be performed by Turing machine.\n";
				cout << "\tMax number of cells = maximum number of cells to display during viewing of operation.\n";
				cout << "\tHelp = current status of the help command.\n";
				cout << "Name of TM = name of the Turing machine loaded into the application.\n";
				cout << "Status of TM = whether the Turing machine is operating or not.\n";
				cout << "Last input string used = last input string the Turing machine operated on.";
				cout << "will show current input string if the Turing machine is currently running.\n";
				cout << "[Results of the operation of the Turing machine on the last input string].";
				cout << " If the Turing machine is in operation, the total number of transitions that have been performed";
				cout << " on the current input string will be shown instead.\n";
			}
			cout << "\n";
			cout << "Course: " << "\t\tCpts 322: Software Engineering I" << endl;
			cout << "Semester: " << "\t\tSpring" << endl;
			cout << "Year: " << "\t\t\t2013" << endl;
			cout << "Instructor: " << "\t\tNeil Corrigan" << endl;
			cout << "Author: " << "\t\tTaylor Tamblin" << endl;
			cout << "Version of Application: " << "1.0" << endl;
			cout << "Configuration Settings:\n";
			cout << "\t\t\tMax number of transitions = " << tm.maximum_number_of_transitions() << "\n";
			cout << "\t\t\tMax number of cells = " << tm.maximum_number_of_cells() << "\n";
			cout << "\t\t\tHelp = ";
			if(helpActivated)
				cout << "On.\n";
			else
				cout << "Off.\n";
			cout << "Name of TM: \t\t" << file << endl;
			cout << "Status of TM: \t\t";
			if(tm.is_operating())
				cout << "Currently operating.\n";
			else
			cout << "Not operating.\n";
			if(tm.is_operating())
			{
				cout << "Current input string: " << tm.input_string() << endl;
			}
			else
				cout << "Last input string used: " << tm.input_string() << endl;
			if(!(tm.is_operating()))
			{
			cout << "String was ";

			if(tm.is_accepted_input_string())
				cout << "accepted";
			else
				cout << "rejected";

			cout << ". " << tm.total_number_of_transitions()
				 << " transitions performed." << endl;
			}
			else
			{
				cout << "Number of transitions: " << tm.total_number_of_transitions() << "\n";
			}
			break;
		//set command
		case 'E':
			if(helpActivated)
			{
				cout << "\nThe Set command sets the maximum number of transitions to be performed";
				cout << " by the Turing machine. Only positive integer values will be accepted.\n\n";
			}
			//string inputMax;
			int newMaxTransitions;
			bool valid_max_transitions;
			valid_max_transitions = false;
			cout << "Maximum number of transitions [" << tm.maximum_number_of_transitions() << "]: ";
			getline(cin, input);
			if(input.size() > 0) //if something was entered
			{
				for(unsigned i = 0; i<input.size(); i++)
				{
					if((input[i] < '0') || (input[i] > '9'))
					{
						cout << "Error! Must enter a positive integer value.\n";
						valid_max_transitions = false;
						break;
					}
					else
						valid_max_transitions = true;
				}
			}
			if(valid_max_transitions)
			{
			newMaxTransitions = atoi(input.c_str());
			if ((newMaxTransitions > 0) && (newMaxTransitions != tm.maximum_number_of_transitions()))
			{
				tm.change_max_transitions(newMaxTransitions);
				cout << "Maximum transitions changed to " << newMaxTransitions << "!" << endl;
			}
			else
				if((input.size() > 1) || (newMaxTransitions == tm.maximum_number_of_transitions()))
			{
				cout << "Error, value unchanged!" << endl;
			}
			}
			break;
			//truncate command
		case 'T':
			if(helpActivated)
			{
				cout << "\nThe Truncate command alters the maximum number of cells to be displayed";
				cout << " on the left and right side of the tape head.\n\n";
			}

			int newMaxCells;
			bool valid_max_cells;
			valid_max_cells = false;
			cout << "Maximum number of cells [" << tm.maximum_number_of_cells() << "]: ";
			getline(cin, input);
			if(input.size() > 0) //if something was entered
			{
				for(unsigned i = 0; i<input.size(); i++)
				{
					if((input[i] < '0') || (input[i] > '9'))
					{
						cout << "Error! Must enter a positive integer value.\n";
						valid_max_cells = false;
						break;
					}
					else
						valid_max_cells = true;
				}
			}
			if(valid_max_cells)
			{
			newMaxCells = atoi(input.c_str());
			if ((newMaxCells > 0) && (newMaxCells != tm.maximum_number_of_cells()))
			{
				tm.change_max_cells(newMaxCells);
				cout << "Maximum cells changed to " << newMaxCells << "!" << endl;
			}
			else
				if((input.size() > 1) || (newMaxCells == tm.maximum_number_of_cells()))
			{
				cout << "Error, value unchanged!" << endl;
			}
			}
			break;
			//list command
		case 'L':
			cout << "\n";
			input_strings.view();
			break;
			//insert command
		case 'I':
			if(helpActivated)
			{
				cout << "\nThe Insert command inserts strings into the input string list.";
				cout << " The string must contain characters from the input_alphabet or else the";
				cout << " string will be not be written to the list.\n\n";
			}
			bool valid_insert;
			valid_insert = true;
			cout << "Enter a string to add to list of input strings: ";
			getline(cin, input); //get input from user as string
			if(input.size() > 0) //if something was entered
			{
				if(!tm.is_valid_input_string(input))
					valid_insert = false;
				if(valid_insert)
				{
					input_strings.insert(input);
				}
				else
					cout << "Error! Input string contains characters not found in input alphabet.\n";
			}
			break;
			//delete command
		case 'D':
			if(helpActivated)
			{
				cout << "The Delete command deletes strings from the input string list.\n";
				cout << "Enter the string you wish to delete by its number and not by the actual";
				cout << " string itself.\n\n";
			}
			int delete_number;
			bool valid_delete;
			valid_delete = true;
			cout << "Enter the number of the string to be deleted: ";
			getline(cin, input); //get input from user as string
			if(input.size() > 0) //if something was entered
			{
				for(unsigned i = 0; i<input.size(); i++)
				{
					if((input[i] < '0') || (input[i] > '9'))
					{
						cout << "Error! Must enter number of the string to be deleted (positive integer value).\n";
						valid_delete = false;
						break;
					}
						
				}
				if(valid_delete)
				{
					delete_number = atoi(input.c_str()); //convert string to int
					input_strings.delete_string(delete_number);
				}
			}
			break;
			//quit command
		case 'Q':
			if(helpActivated)
			{
				cout << "The Quit command will stop operation of the Turing machine on the current";
				cout << " input string if the Turing machine is currently running.\n\n";
			}
			if(tm.is_operating())
			{
			cout << "Input string ";
			cout << tm.input_string() << "was not accepted or rejected in ";
			cout << tm.total_number_of_transitions() << " transitions." << endl;
			tm.terminate_operation();
			}
			else
				cout << "Error! Not currently running on a string" << endl;
			break;
		}
	}
	//}while(running); //run program loop while running = true

	//string name;
	//State x;
	//State y = "s2"	;
	//State z = y;
	//state_pointer p = new State(z);
	//x = *p;
	//p->set_name("s3");
	//delete p;
	//x.get_name(name);
	//cout << "name of state x is " << name << ".\n";
	//cout << "total number of states is " << State::total_number_of_states() << ".\n";
	//	system("pause");
		//return success;

}