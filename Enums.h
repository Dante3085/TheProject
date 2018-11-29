#ifndef ENUMS_H
#define ENUMS_H

/**
 * \attention Not every File needs all enums
 */

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
		 * \brief Represents Debugging State
		 */
		debugging,

		/**
		 * \brief Represents MainMenu State
		 */
		mainMenu,
	};

	enum EAnimation
	{
		None,
		Idle,
		GoLeft,
		GoUp,
		GoRight,
		GoDown,
		Attack,
		Jump
	};
}
#endif