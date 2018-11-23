#include <iostream>
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "Utils.h"
#include "FiniteStateMachine.h"
#include <map>
#include "State.h"
#include "AnimatedSprite.h"
#include <chrono>

using namespace sf;
using namespace TheProject;

int main()
{
	InputManager manager{};

	sf::RenderWindow window{ sf::VideoMode{800, 600}, "TheProject" };

	AnimatedSprite* gothicHero = new AnimatedSprite{ "Ressources/gothic-hero-run.png", 66, 48, {100.0f, 0.0f}, 200, .09f };
	gothicHero->addAnimation(Idle, 12, 0, 0);
	gothicHero->addAnimation(GoLeft, 5, 37, 1);
	gothicHero->addAnimation(GoUp, 5, 37, 1);
	gothicHero->addAnimation(GoRight, 5, 37, 1);
	gothicHero->addAnimation(GoDown, 5, 37, 1);
	gothicHero->addAnimation(Attack, 5, 37, 1);

	AnimatedSprite* demonAttack = new AnimatedSprite{ "Ressources/demon-attack.png", 240, 192, {-150.0f, 50.0f}, 200, .2f };
	demonAttack->addAnimation(Idle, 11, 0, 0);
	demonAttack->addAnimation(GoLeft, 5, 37, 1);
	demonAttack->addAnimation(GoUp, 5, 37, 1);
	demonAttack->addAnimation(GoRight, 5, 37, 1);
	demonAttack->addAnimation(GoDown, 5, 37, 1);
	demonAttack->addAnimation(Attack, 5, 37, 1);

	AnimatedSprite* hellBeast = new AnimatedSprite{ "Ressources/hell-beast-breath.png", 64, 64, {400.f, 50.0f}, 200, .45f };
	hellBeast->addAnimation(Idle, 4, 0, 0);
	hellBeast->addAnimation(GoLeft, 5, 37, 1);
	hellBeast->addAnimation(GoUp, 5, 37, 1);
	hellBeast->addAnimation(GoRight, 5, 37, 1);
	hellBeast->addAnimation(GoDown, 5, 37, 1);
	hellBeast->addAnimation(Attack, 5, 37, 1);

	std::vector<Entity*>* entities = new std::vector<Entity*>{ gothicHero, demonAttack, hellBeast };
	std::vector<EState>* next = new std::vector<EState>{ none };

	std::map<EState, State*>* states = new std::map<EState, State*>{ {mainMenu, new State{"MainMenu", entities, next}}, 
		{inventory, new State{"Inventory"}} };

	FiniteStateMachine fsm{ states, none, inventory };


	// NACHVOLLZIEHEN
	// timepoint for delta time measurement
	auto timepoint = std::chrono::steady_clock::now();

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

		// NACHVOLLZIEHEN
		// get dt
		float deltaTime;
		{
			const auto new_tp = std::chrono::steady_clock::now();

			// duration
			deltaTime = std::chrono::duration<float>(new_tp - timepoint).count();
			timepoint = new_tp;
		}

		if (manager.OnKeyDown(Keyboard::Key::M))
			fsm.change(mainMenu);
		else if (manager.OnKeyDown(Keyboard::Key::N))
			fsm.change(none);

		sf::Vector2f dir = { 0.0f, 0.0f };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			dir.y -= 1.0f;
			gothicHero->setAnimation(GoUp);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			dir.y += 1.0f;
			gothicHero->setAnimation(GoDown);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			dir.x -= 1.0f;
			gothicHero->setAnimation(GoLeft);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			dir.x += 1.0f;
			gothicHero->setAnimation(GoRight);
		}
		else
			gothicHero->setAnimation(Idle);

		gothicHero->setDirection(dir);

		// Kriegt sekunden übergeben
		fsm.update( deltaTime );

		manager.UpdatePreviousStates();

		window.clear();
		fsm.draw(window);
		window.display();
	}

	/**
	 * \bug Wenn in obiger Schleife Return gedrückt wurde, wird das Programm nach Drücken von Escape in der Schleife ohne anzuhalten beendet.
	 */
	// Utils::PauseConsole();

	return EXIT_SUCCESS;
}
