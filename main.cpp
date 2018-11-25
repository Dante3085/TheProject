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

	sf::RenderWindow window{ sf::VideoMode{1280, 720}, "TheProject" };

	std::vector<std::string> spriteSheetLocations{ "Ressources/gothic-hero-idle.png", "Ressources/gothic-hero-run.png", 
		"Ressources/gothic-hero-jump.png", "Ressources/gothic-hero-attack.png" };

	AnimatedSprite* gothicHero = new AnimatedSprite{ spriteSheetLocations, {100.0f, 0.0f}, 300 };
	gothicHero->addAnimation(Idle, 0, 38, 48, 0, 0, 4);
	gothicHero->addAnimation(GoLeft, 1, 66, 48, 0, 0, 12, 0.1f, true);
	gothicHero->addAnimation(GoRight, 1, 66, 48, 0, 0, 12, 0.1f);
	gothicHero->addAnimation(Jump, 2, 61, 77, 0, 0, 5, 0.2f);
	gothicHero->addAnimation(Attack, 3, 95, 48, 0, 0, 6);
	gothicHero->setAnimation(Idle);

	std::vector<Entity*>* entities = new std::vector<Entity*>{ gothicHero };
	std::vector<EState>* next = new std::vector<EState>{ none };

	std::map<EState, State*>* states = new std::map<EState, State*>{ {debugging, new State{"Debugging", entities, next}}, 
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
			fsm.change(debugging);
		else if (manager.OnKeyDown(Keyboard::Key::N))
			fsm.change(none);

		sf::Vector2f dir = { 0.0f, 0.0f };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			dir.y -= 1.0f;
			gothicHero->setAnimation(GoUp);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			dir.y += 1.0f;
			gothicHero->setAnimation(GoDown);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			dir.x -= 1.0f;
			gothicHero->setAnimation(GoLeft);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			gothicHero->setAnimation(Jump);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			gothicHero->setAnimation(Attack);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			dir.x += 1.0f;
			gothicHero->setAnimation(GoRight);
		}
		

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
