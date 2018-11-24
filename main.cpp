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

	sf::RenderWindow window{ sf::VideoMode{1920, 1080}, "TheProject" };

	AnimatedSprite* gothicHero = new AnimatedSprite{ "Ressources/gothic-hero-run.png", 66, 48, {100.0f, 0.0f}, 300, .09f };
	gothicHero->addAnimation(Idle, 12, 0, 0);
	gothicHero->addAnimation(GoLeft, 12, 0, 0);
	gothicHero->addAnimation(GoUp, 12, 0, 0);
	gothicHero->addAnimation(GoRight, 12, 0, 0);
	gothicHero->addAnimation(GoDown, 12, 0, 0);
	gothicHero->addAnimation(Attack, 12, 0, 0);

	AnimatedSprite* demonAttack = new AnimatedSprite{ "Ressources/demon-attack.png", 240, 192, {150.0f, 200.0f}, 200, .2f };
	demonAttack->addAnimation(Idle, 11, 0, 0);
	demonAttack->addAnimation(GoLeft, 5, 37, 1);
	demonAttack->addAnimation(GoUp, 5, 37, 1);
	demonAttack->addAnimation(GoRight, 5, 37, 1);
	demonAttack->addAnimation(GoDown, 5, 37, 1);
	demonAttack->addAnimation(Attack, 5, 37, 1);

	AnimatedSprite* hellBeast = new AnimatedSprite{ "Ressources/hell-beast-breath.png", 64, 64, {400.f, 50.0f}, 200.f, .45f };
	hellBeast->addAnimation(Idle, 4, 0, 0);
	hellBeast->addAnimation(GoLeft, 5, 37, 1);
	hellBeast->addAnimation(GoUp, 5, 37, 1);
	hellBeast->addAnimation(GoRight, 5, 37, 1);
	hellBeast->addAnimation(GoDown, 5, 37, 1);
	hellBeast->addAnimation(Attack, 5, 37, 1);

	AnimatedSprite* ghost = new AnimatedSprite{ "Ressources/ghost-idle.png", 64, 80, {600.f, 50.0f}, 200.f, .15f };
	ghost->addAnimation(Idle, 7, 0, 0);
	ghost->addAnimation(GoLeft, 5, 37, 1);
	ghost->addAnimation(GoUp, 5, 37, 1);
	ghost->addAnimation(GoRight, 5, 37, 1);
	ghost->addAnimation(GoDown, 5, 37, 1);
	ghost->addAnimation(Attack, 5, 37, 1);

	AnimatedSprite* breathFire = new AnimatedSprite{ "Ressources/breath-fire.png", 160, 96, {600.f, 100.0f}, 200.f, .25f };
	breathFire->addAnimation(Idle, 5, 0, 0);
	breathFire->addAnimation(GoLeft, 5, 37, 1);
	breathFire->addAnimation(GoUp, 5, 37, 1);
	breathFire->addAnimation(GoRight, 5, 37, 1);
	breathFire->addAnimation(GoDown, 5, 37, 1);
	breathFire->addAnimation(Attack, 5, 37, 1);

	std::vector<Entity*>* entities = new std::vector<Entity*>{ gothicHero, demonAttack, hellBeast, ghost, breathFire };
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
