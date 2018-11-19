#pragma once


#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;

namespace TheProject
{
	/**
	 * \brief Sollte eher Namespace sein. Klassen nur mit statischen Funktionen sind nicht sinnvoll
	 */
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void UpdateCurrentStates();
		void UpdatePreviousStates();

		bool OnKeyDown(Keyboard::Key key);
		bool OnDoubleKeyDown(Keyboard::Key key);

		bool IsKeyDown(Keyboard::Key key);

	private:
		std::map<Keyboard::Key, bool> m_currentKeyStates;
		std::map<Keyboard::Key, bool> m_previousKeyStates;
	};
}