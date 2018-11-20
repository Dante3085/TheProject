#pragma once

namespace TheProject
{
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
}