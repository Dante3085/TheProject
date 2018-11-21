#include "FiniteStateMachine.h"
#include "State.h"
#include <algorithm>
#include <iostream>
#include <string>

namespace TheProject
{

	FiniteStateMachine::FiniteStateMachine()
		: m_states{ new std::map<EState, State*> }, m_startState{ none }, m_endState{ none }, m_currentState(none)
	{
		m_states->insert(std::pair<EState, State*>(none, new State{"none"}));
		m_states->insert(std::pair<EState, State*>(mainMenu, new State{"mainMenu"}));
		m_states->insert(std::pair<EState, State*>(inventory, new State{"inventory"}));
	}


	FiniteStateMachine::FiniteStateMachine(std::map<EState, State*>* states, EState startState, EState endState)
		: m_states{ states }, m_startState{ startState }, m_endState{ endState }
	{
		m_currentState = m_startState;
	}

	FiniteStateMachine::~FiniteStateMachine()
	{
		// Delete all States inside FiniteStateMachine
		std::map<EState, State*>::iterator it;
		while(it != m_states->end())
		{
			delete it->second;
			++it;
		}

		// Delete State container of this FiniteStateMachine
		delete m_states;
	}

	void FiniteStateMachine::update(float gameTime)
	{
		// Make sure that currentState exists (Alternative: Check if m_states is empty)
		/*State* temp = m_states->at(m_currentState);
		if (temp != nullptr)
			temp->update(gameTime);*/

		if (!m_states->empty())
			m_states->at(m_currentState)->update(gameTime);
	}

	void FiniteStateMachine::draw()
	{
		if (!m_states->empty())
			m_states->at(m_currentState)->draw();
	}

	bool FiniteStateMachine::change(EState state)
	{
		if (m_currentState == state)
		{
			std::cout << "@FiniteStateMachine.change(): Passed state is already active" << std::endl;
			return false;
		}

		// Check if state is known to this FiniteStateMachine (http://www.cplusplus.com/reference/map/map/count/)
		if (m_states->count(state) == 0)
		{
			std::cout << "@FiniteStateMachine.change(): FiniteStateMachine does not know passed state " << std::endl;
			return false;
		}

		// Check if currentState of this FiniteStateMachine can transition to state
		std::vector<EState>* next = m_states->at(m_currentState)->getNext();
		if (!(std::find(next->begin(), next->end(), state) != next->end()))
		{
			std::cout << "@FiniteStateMachine.change(): CurrentState \"" << m_states->at(m_currentState)->getName()
				<< " can not transition to passed state " << std::endl;
			return false;
		}

		m_states->at(m_currentState)->onExit();
		m_states->at(state)->onEnter();
		m_currentState = state;

		return true;
	}

	void FiniteStateMachine::reset()
	{
	}

	void FiniteStateMachine::terminate()
	{
	}

	std::map<EState, State*>* FiniteStateMachine::getStates()
	{
		return m_states;
	}

	EState FiniteStateMachine::getCurrentState()
	{
		return m_currentState;
	}

	EState FiniteStateMachine::getStartState()
	{
		return m_startState;
	}

	EState FiniteStateMachine::getEndState()
	{
		return m_endState;
	}
}
