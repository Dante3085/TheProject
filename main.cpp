#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "Utils.h"
#include "FiniteStateMachine.h"

using namespace sf;
using namespace TheProject;

int main()
{
	InputManager manager;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	sf::RectangleShape shape(Vector2<float>(100, 100));
	shape.setFillColor(sf::Color::Green);

	sf::Texture tex;
	tex.loadFromFile("beer2.jpg");

	sf::Sprite sprite{ tex };
	sprite.setTextureRect(sf::IntRect(100, 100, 100, 100));
	sprite.setColor(sf::Color(255, 255, 255, 200));
	sprite.setPosition(0, 0);

	float speed = 0.3f;
	FiniteStateMachine fsm{};

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		manager.UpdateCurrentStates();

		if (manager.IsKeyDown(Keyboard::Key::Left))
			shape.setPosition(shape.getPosition().x - speed, shape.getPosition().y);

		if (manager.IsKeyDown(Keyboard::Key::Right))
			shape.setPosition(shape.getPosition().x + speed, shape.getPosition().y);

		if (manager.IsKeyDown(Keyboard::Key::Up))
			shape.setPosition(shape.getPosition().x, shape.getPosition().y - speed);

		if (manager.IsKeyDown(Keyboard::Key::Down))
			shape.setPosition(shape.getPosition().x, shape.getPosition().y + speed);

		if (manager.IsKeyDown(Keyboard::Key::LShift))
			speed = 0.3 + 0.3;
		else
			speed = 0.3;

		if (manager.OnKeyDown(Keyboard::Key::Return))
			fsm.change(inventory);

		manager.UpdatePreviousStates();

		// Left Wall
		if (shape.getPosition().x < 0)
			shape.setPosition(0, shape.getPosition().y);

		// Right Wall
		if (shape.getPosition().x + shape.getSize().x > window.getSize().x)
			shape.setPosition(window.getSize().x - shape.getSize().x, shape.getPosition().y);

		// Up Wall
		if (shape.getPosition().y < 0)
			shape.setPosition(shape.getPosition().x, 0);

		// Down Wall
		if (shape.getPosition().y + shape.getSize().y > window.getSize().y)
			shape.setPosition(shape.getPosition().x, window.getSize().y - shape.getSize().y);

		fsm.update(3.14);
		fsm.draw();

		window.clear();
		window.draw(shape);
		window.draw(sprite);
		window.display();
	}

	Utils::PauseConsole();

	return EXIT_SUCCESS;
}
