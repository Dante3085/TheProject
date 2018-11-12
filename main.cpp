#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	int counter = 0;
	bool current = false;
	bool previous = false;

	while(true)
	{
		current = Keyboard::isKeyPressed(Keyboard::Key::Return);
		// std::cout << "Current: " << current << std::endl;

		// std::cout << "Counter: " << counter++ << std::endl;

		if (!previous && current)
			std::cout << "Enter" << std::endl;

		previous = current;
		// std::cout << "Previous: " << previous << std::endl;

	}

	std::cout << "Press Enter to continue..." << std::endl;
	std::string b;
	std::getline(std::cin, b);
	return EXIT_SUCCESS;
}
