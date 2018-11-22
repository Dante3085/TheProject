#include "InputManager.h"
#include <iostream>

using namespace sf;

namespace TheProject
{
	/**
	 * \brief Constructor
	 */
	InputManager::InputManager()
	{
		std::cout << "InputManager created" << std::endl;
	}

	/**
	 * \brief Destructor
	 */
	InputManager::~InputManager()
	{
		std::cout << "InputManager destroyed" << std::endl;
	}

	/**
	 * \brief Updates current Key States. Call before you'r Key-Operations.
	 */
	void InputManager::UpdateCurrentStates()
	{
		// Creates Iterator for map
		std::map<Keyboard::Key, bool>::iterator it;

		// Uses Iterator to iterate over map
		for (it = m_currentKeyStates.begin(); it != m_currentKeyStates.end(); it++)
			it->second = Keyboard::isKeyPressed(it->first);
	}

	/**
	 * \brief Updates previous Key States. Call after you'r Key-Operations.
	 */
	void InputManager::UpdatePreviousStates()
	{
		m_previousKeyStates = m_currentKeyStates;
	}


	/**
	 * \brief Gets whether or not key was previously not pressed and is now pressed (=KeyPress that ignores holding)
	 */
	bool InputManager::OnKeyDown(Keyboard::Key key)
	{
		// Note: If [] - operator does not find key, it inserts new element with that key (see: http://www.cplusplus.com/reference/map/map/operator[]/)
		return !m_previousKeyStates[key] && m_currentKeyStates[key];
	}
}