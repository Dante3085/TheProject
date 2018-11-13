#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "InputManager.h"

using namespace sf;

int main()
{
	InputManager manager;

	while(true)
	{
		manager.UpdateCurrentStates();

		if (manager.OnKeyDown(Keyboard::Key::Return))
			std::cout << "Pressed Return" << std::endl;

		if (manager.OnKeyDown(Keyboard::Key::Space))
			std::cout << "Pressed Space" << std::endl;

		if (manager.IsKeyDown(Keyboard::Key::BackSpace))
			std::cout << "Pressed Backspace" << std::endl;

		manager.UpdatePreviousStates();
	}

	std::cout << "Press Enter to continue..." << std::endl;
	std::string b;
	std::getline(std::cin, b);
	return EXIT_SUCCESS;
}
