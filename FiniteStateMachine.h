#ifndef FINITE_STATE_MACHINE_H
#define FINITE_STATE_MACHINE_H

#include "State.h"
#include <map>

/**
 * \brief Enum used to quickly access State objects inside std::map states of this FiniteStateMachine
 */
enum EState
{

	/**
	 * \brief Represents the absence of a State
	 */
	none,

	/**
	 * \brief Represents the Inventory State
	 */
	inventory, 


	/**
	 * \brief Represents MainMenu State
	 */
	mainMenu,
};

class FiniteStateMachine
{
public:
	FiniteStateMachine();
	FiniteStateMachine(std::map<EState, State*>* states, EState startState, EState endState);
	~FiniteStateMachine();


	/**
	 * \brief Updates the currentState of this FiniteStateMachine
	 * \param gameTime ???? Besser wäre GameTime Klasse mit mehreren Informationen (elapsed, etc.)
	 */
	void update(float gameTime);


	/**
	 * \brief Draws currentState of this FiniteStateMachine
	 */
	void draw();


	/**
	 * \brief If possible, changes currentState of this FiniteStateMachine to state
	 * \param state State that will be currentState if change() is successful
	 * \return True if change to state was successful, else false
	 */
	bool change(EState state);


	/**
	 * \brief Resets this FiniteStateMachine(i.e. Restores initial "State"(colloquial) of this FiniteStateMachine)
	 */
	void reset();


	/**
	 * \brief Terminates this FiniteStateMachine(i.e. ????)
	 */
	void terminate();


	/**
	 * \brief Returns std::map with all States of this FiniteStateMachine
	 * \return std::map with all States of this FiniteStateMachine
	 */
	std::map<EState, State*>* getStates();


	/**
	 * \brief Returns EState currentState of this FiniteStateMachine
	 * \return EState currentState of this FiniteStateMachine
	 */
	EState getCurrentState();

	/**
	 * \brief Returns EState startState of this FiniteStateMachine
	 * \return EState startState of this FiniteStateMachine
	 */
	EState getStartState();


	/**
	 * \brief Returns EState endState of this FiniteStateMachine
	 * \return EState endState of this FiniteStateMachine
	 */
	EState getEndState();

private:


	/**
	 * \brief std::map with all States of this FiniteStateMachine
	 */
	std::map<EState, State*>* m_states;


	/**
	 * \brief EState currentState of this FiniteStateMachine
	 */
	EState m_currentState;


	/**
	 * \brief EState startState of this FiniteStateMachine
	 */
	EState m_startState;


	/**
	 * \brief EState endState of this FiniteStateMachine
	 */
	EState m_endState;
};

#endif