#ifndef FINITE_STATE_MACHINE_H
#define FINITE_STATE_MACHINE_H

#include "Enums.h"
#include <map>
#include <SFML/Graphics/RenderTarget.hpp>

namespace TheProject
{
	// Forward Declaration für State
	class State;

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
		void update(float gameTime) const;

		/**
		 * \brief Draws currentState of this FiniteStateMachine
		 */
		void draw(sf::RenderTarget& rt) const;


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
		std::map<EState, State*>* getStates() const;


		/**
		 * \brief Returns EState currentState of this FiniteStateMachine
		 * \return EState currentState of this FiniteStateMachine
		 */
		EState getCurrentState() const;

		/**
		 * \brief Returns EState startState of this FiniteStateMachine
		 * \return EState startState of this FiniteStateMachine
		 */
		EState getStartState() const;


		/**
		 * \brief Returns EState endState of this FiniteStateMachine
		 * \return EState endState of this FiniteStateMachine
		 */
		EState getEndState() const;

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
}
#endif