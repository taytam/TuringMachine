#ifndef INPUT_STRING_FILE_H
#define INPUT_STRING_FILE_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Input_String_File
{
private:
	bool overwrite; //determine if the string will be overwritten at the end of program
	bool loaded;
	vector<string> input_strings;
public:
	Input_String_File();
	void load(string value);
	void view() const;
	void file_was_modified();
	bool is_modified();
	void insert(string value);
	void delete_string(int index);
	int size();
	string element(int index);
	bool is_element(string value);
	bool was_loaded();
	void write_to_file(string value);
};

#endif