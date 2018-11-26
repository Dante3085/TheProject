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

	std::vector<std::string> gothicHeroSpriteSheetLocations{ "Ressources/gothic-hero-idle.png", "Ressources/gothic-hero-run.png", 
		"Ressources/gothic-hero-jump.png", "Ressources/gothic-hero-attack.png" };
	AnimatedSprite* gothicHero = new AnimatedSprite{ gothicHeroSpriteSheetLocations, {0.0f, 0.0f}, 300 };
	gothicHero->addAnimation(Idle, 0, 38, 48, 0, 0, 4);
	gothicHero->addAnimation(GoLeft, 1, 66, 48, 0, 0, 12, 0.1f, true);
	gothicHero->addAnimation(GoRight, 1, 66, 48, 0, 0, 12, 0.1f);
	gothicHero->addAnimation(Jump, 2, 61, 77, 0, 0, 5, 0.2f);
	gothicHero->addAnimation(Attack, 3, 95, 48, 0, 0, 6);
	gothicHero->setAnimation(Idle);

	std::vector<std::string> swordsmanSpriteSheetLocations{ "Ressources/swordsman.png" };
	AnimatedSprite* swordsman = new AnimatedSprite{ swordsmanSpriteSheetLocations, {0.f, 150.0f}, 300 };
	swordsman->addAnimation(Idle, 0, 48, 43, 433, 0, 4);
	swordsman->addAnimation(GoLeft, 0, 50, 50, 100, 0, 8, .1f);
	swordsman->addAnimation(GoUp, 0, 50, 50, 50, 0, 12, .1f);
	swordsman->addAnimation(GoRight, 0, 50, 50, 100, 8, 8, .1f);
	swordsman->addAnimation(GoDown, 0, 50, 50, 0, 0, 12, .1f);
	swordsman->setAnimation(Idle);

	std::vector<std::string> demonSpriteSheetLocations{ "Ressources/demon-idle.png", "Ressources/demon-attack.png" };
	AnimatedSprite* demon = new AnimatedSprite{ demonSpriteSheetLocations, {0.f, 250.f}, 300 };
	demon->addAnimation(Idle, 0, 160, 144, 0, 0, 6);
	demon->addAnimation(Attack, 1, 240, 192, 0, 0, 11);
	demon->setAnimation(Idle);

	std::vector<std::string> wizardSpriteSheetLocations{ "Ressources/wizard idle.png", "Ressources/wizard fly forward.png",
	"Ressources/wizard death.png"};
	AnimatedSprite* wizard = new AnimatedSprite{ wizardSpriteSheetLocations, {0.f, 500.f}, 300 };
	wizard->addAnimation(Idle, 0, 80, 80, 0, 0, 10);
	wizard->addAnimation(Attack, 1, 240, 192, 0, 0, 11);
	wizard->setAnimation(Idle);

	std::vector<std::string> fireSpriteSheetLocations { "Ressources/11_fire_spritesheet.png" };
	AnimatedSprite* fire = new AnimatedSprite{ fireSpriteSheetLocations, {0.f, 0.f}, 300 };
	fire->addAnimation(Idle, 0, 100, 100, 0, 0, 61, .05f);
	fire->setAnimation(Idle);

	std::vector<std::string> phantomSpriteSheetLocations{ "Ressources/14_phantom_spritesheet.png" };
	AnimatedSprite* phantom = new AnimatedSprite{ phantomSpriteSheetLocations, {200.f, 0.f}, 300 };
	phantom->addAnimation(Idle, 0, 100, 100, 0, 0, 61, .05f);
	phantom->setAnimation(Idle);

	std::vector<std::string> bubbleSpriteSheetLocations{ "Ressources/20_magicbubbles_spritesheet.png" };
	AnimatedSprite* bubbles = new AnimatedSprite{ bubbleSpriteSheetLocations, {400.f, 0.f}, 300 };
	bubbles->addAnimation(Idle, 0, 100, 100, 0, 0, 61, .05f);
	bubbles->setAnimation(Idle);

	std::vector<std::string> loadingSpriteSpriteSheetLocations{ "Ressources/15_loading_spritesheet.png" };
	AnimatedSprite* loadingSprite = new AnimatedSprite{ loadingSpriteSpriteSheetLocations, {600.f, 0.f}, 300 };
	loadingSprite->addAnimation(Idle, 0, 100, 100, 0, 0, 60, .05f);
	loadingSprite->setAnimation(Idle);

	AnimatedSprite* loadingSprite2 = new AnimatedSprite{ loadingSpriteSpriteSheetLocations, {800.f, 0.f}, 300 };
	loadingSprite2->addAnimation(Idle, 0, 100, 100, 0, 0, 61, .05f, false, true);
	loadingSprite2->setAnimation(Idle);

	std::vector<std::string> freezingSpriteSheetLocations{ "Ressources/19_freezing_spritesheet.png" };
	AnimatedSprite* freezing = new AnimatedSprite{ freezingSpriteSheetLocations, {1000.f, 0.f}, 300 };
	freezing->addAnimation(Idle, 0, 100, 100, 0, 0, 86, .05f);
	freezing->setAnimation(Idle);

	std::vector<std::string> vortexSpriteSheetLocations{ "Ressources/13_vortex_spritesheet.png" };
	AnimatedSprite* vortex = new AnimatedSprite{ vortexSpriteSheetLocations, {0.f, 200.f}, 300 };
	vortex->addAnimation(Idle, 0, 100, 100, 0, 0, 60, .05f);
	vortex->setAnimation(Idle);

	std::vector<Entity*>* entities = new std::vector<Entity*>{ fire, phantom, bubbles, loadingSprite, 
		loadingSprite2, freezing, vortex, demon, gothicHero, swordsman};
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
			swordsman->setAnimation(GoUp);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			dir.y += 1.0f;
			gothicHero->setAnimation(GoDown);
			swordsman->setAnimation(GoDown);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			dir.x -= 1.0f;
			gothicHero->setAnimation(GoLeft);
			swordsman->setAnimation(GoLeft);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			gothicHero->setAnimation(Jump);

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			gothicHero->setAnimation(Attack);
			demon->setAnimation(Attack);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			dir.x += 1.0f;
			gothicHero->setAnimation(GoRight);
			swordsman->setAnimation(GoRight);
		}

		else if (manager.OnKeyDown(sf::Keyboard::R))
		{
			if (phantom->getAnimationReverse(Idle))
				phantom->setAnimationReverse(Idle, false);
			else
				phantom->setAnimationReverse(Idle, true);
		}

		else
		{
			gothicHero->setAnimation(Idle);
			swordsman->setAnimation(Idle);
			demon->setAnimation(Idle);
		}

		gothicHero->setDirection(dir);
		swordsman->setDirection(dir);
		demon->setDirection(dir);
		phantom->setDirection(dir);

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
