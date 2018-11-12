#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void UpdateCurrentStates();
	void UpdatePreviousStates();

private:
	std::unordered_map<sf::Keyboard::Key, bool> m_currentKeyStates;
	std::unordered_map<sf::Keyboard::Key, bool> m_previousKeyStates;
};

