#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "Utils.h"
#include "FiniteStateMachine.h"
#include <map>
#include "State.h"
#include "AnimatedSprite.h"

using namespace sf;
using namespace TheProject;

int main()
{
	InputManager manager{};

	/*std::map<EState, State*>* states = new std::map<EState, State*>{ {mainMenu, new State{"MainMenu"}}, 
		{inventory, new State{"Inventory"}} };

	FiniteStateMachine fsm{ states, none, inventory };*/

	sf::RenderWindow window{ sf::VideoMode{1920, 1080}, "TheProject" };
	AnimatedSprite animSprite{ "adventurer.png", {100.0f, 100.0f} };

	while(window.isOpen())
	{
		manager.UpdateCurrentStates();

		// Process Events
		sf::Event event;
		while(window.pollEvent(event))
		{
			//// Close Window
			//if (event.type == sf::Event::Closed)
			//	window.close();

			if (manager.OnKeyDown(Keyboard::Key::Escape))
				window.close();
		}

		sf::Vector2f dir = { 0.0f, 0.0f };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			dir.y -= 1.0f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			dir.y += 1.0f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			dir.x -= 1.0f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			dir.x += 1.0f;

		animSprite.setDirection(dir);

		// 60 fps
		animSprite.update(1.0f / 60.0f);

		manager.UpdatePreviousStates();

		window.clear();
		animSprite.draw(window);
		window.display();
	}

	/**
	 * \bug Wenn in obiger Schleife Return gedrückt wurde, wird das Programm nach Drücken von Escape in der Schleife ohne anzuhalten beendet.
	 */
	Utils::PauseConsole();

	return EXIT_SUCCESS;
}
