#ifndef CRASH_H
#define CRASH_H

#include <exception>
#include <string>
using namespace std;

class Crash:public exception
{
	public:
		Crash(string reason);
};
#endif