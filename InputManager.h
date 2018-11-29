#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

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

	private:
		std::map<Keyboard::Key, bool> m_currentKeyStates;
		std::map<Keyboard::Key, bool> m_previousKeyStates;
	};
}
#endif