#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "Utils.h"

using namespace sf;

int main()
{
	InputManager manager;

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::RectangleShape shape(Vector2<float>(100, 100));
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			manager.UpdateCurrentStates();

			if (manager.OnKeyDown(Keyboard::Key::Return))
				std::cout << "Pressed Return" << std::endl;

			if (manager.OnKeyDown(Keyboard::Key::Space))
				std::cout << "Pressed Space" << std::endl;

			if (manager.IsKeyDown(Keyboard::Key::BackSpace))
				std::cout << "Pressed Backspace" << std::endl;

			if (manager.OnKeyDown(Keyboard::Key::Escape))
			{
				std::cout << "Pressed Esacpe" << std::endl;
				event.type = sf::Event::Closed;
			}

			manager.UpdatePreviousStates();

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	Utils::PauseConsole();

	return EXIT_SUCCESS;
}
