#include "crash.h"
#include <exception>
#include <string>
using namespace std;

Crash::Crash(string reason): exception(reason.c_str())
{
}
