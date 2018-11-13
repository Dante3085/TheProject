#pragma once
#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;

class InputManager
{
public:
	InputManager();
	~InputManager();

	void UpdateCurrentStates();
	void UpdatePreviousStates();

	bool OnKeyDown(Keyboard::Key key);
	bool IsKeyDown(Keyboard::Key key);

private:
	std::map<Keyboard::Key, bool> m_currentKeyStates;
	std::map<Keyboard::Key, bool> m_previousKeyStates;
};

