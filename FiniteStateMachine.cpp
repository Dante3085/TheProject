#include "FiniteStateMachine.h"

FiniteStateMachine::FiniteStateMachine()
	: m_states{new std::map<EState, State*>}, m_startState(none), m_endState(none)
{
}


FiniteStateMachine::FiniteStateMachine(std::map<EState, State*>* states, EState startState, EState endState)
	: m_states{states}, m_startState{startState}, m_endState{endState}
{
}

FiniteStateMachine::~FiniteStateMachine()
{
}

void FiniteStateMachine::update(float gameTime)
{
	m_states->at(m_currentState)->update(gameTime);
}

void FiniteStateMachine::draw()
{
	m_states->at(m_currentState)->draw();
}

bool FiniteStateMachine::change(EState state)
{
	// Check if state is in m_states (http://www.cplusplus.com/reference/map/map/count/)
	if (m_states->count(state) == 0)
		return false;

	std::vector<EState>* test = m_states->at(state)->getNext();
	if (m_states->at(state)->getNext().)
}

void FiniteStateMachine::reset()
{
}

void FiniteStateMachine::terminate()
{
}

std::map<EState, State*>* FiniteStateMachine::getStates()
{
}

EState FiniteStateMachine::getCurrentState()
{
}

EState FiniteStateMachine::getStartState()
{
}

EState FiniteStateMachine::getEndState()
{
}
