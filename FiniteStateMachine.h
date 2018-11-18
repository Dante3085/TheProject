#ifndef FINITE_STATE_MACHINE_H
#define FINITE_STATE_MACHINE_H

#include <map>

enum EState { empty, inventory, mainMenu };

class FiniteStateMachine
{
public:
	FiniteStateMachine();
	~FiniteStateMachine();

private:
	std::map<EState, State> m_states;
};

#endif