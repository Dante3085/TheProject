#ifndef UTILS_H
#define UTILS_H

#include <iostream>

namespace TheProject
{
	/**
	 * \brief Contains static functions that serve general purposes
	 */
	namespace Utils
	{
		/**
		 * \brief Pauses the Console until Enter/Return is pressed.
		 */
		void PauseConsole()
		{
			std::cout << "Press Enter/Return to continue...";
			std::cin.get();
		}
	}
}
#endif