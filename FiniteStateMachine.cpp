#include "FiniteStateMachine.h"
#include <algorithm>

namespace TheProject
{

	FiniteStateMachine::FiniteStateMachine()
		: m_states{ new std::map<EState, State*> }, m_startState(none), m_endState(none)
	{
		m_states->insert(std::pair<EState, State*>(none, new State));
		m_states->insert(std::pair<EState, State*>(inventory, new State));
	}


	FiniteStateMachine::FiniteStateMachine(std::map<EState, State*>* states, EState startState, EState endState)
		: m_states{ states }, m_startState{ startState }, m_endState{ endState }
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
		// Check if state is known to this FiniteStateMachine (http://www.cplusplus.com/reference/map/map/count/)
		if (m_states->count(state) == 0)
			return false;

		// Check if currentState of this FiniteStateMachine can transition to State
		std::vector<EState>* next = m_states->at(m_currentState)->getNext();
		if (!(std::find(next->begin(), next->end(), state) != next->end()))
			return false;

		// Call onExit on currentState
		m_states->at(m_currentState)->onExit();

		// Call onEnter on state
		m_states->at(state)->onEnter();

		// Set currentState to state
		m_currentState = state;
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
}
