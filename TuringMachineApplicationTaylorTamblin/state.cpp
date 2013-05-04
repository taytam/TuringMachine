#include "state.h"
#include "string_pointer.h"
#include <string>
using namespace std;

int State::number_of_states = 0;
State::State()
{
	state_name = new string;
	++number_of_states;
}

State::State(string name)
{
	state_name = new string(name);
	++number_of_states;
}

State::State(const State& state)
{
	state_name = new string(*state.state_name);
	++number_of_states;
}

State::~State()
{
	delete state_name;
	--number_of_states;
}

State& State::operator=(const State& state)
{
	if(this != &state)
		*state_name = *state.state_name;
	return *this;
}

void State::get_name(string& name) const
{
	name = *state_name;
}

void State::set_name(string name)
{
	*state_name = name;
}

int State::total_number_of_states()
{
	return number_of_states;
}