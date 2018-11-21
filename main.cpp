#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "Utils.h"
#include "FiniteStateMachine.h"
#include <map>
#include "State.h"

using namespace sf;
using namespace TheProject;

int main()
{
	InputManager manager{};
	std::map<EState, State*>* states = new std::map<EState, State*>{ {mainMenu, new State{"MainMenu"}}, 
		{inventory, new State{"Inventory"}} };
	FiniteStateMachine fsm{ states, mainMenu, inventory };

	while(true)
	{
		manager.UpdateCurrentStates();

		if (manager.OnKeyDown(Keyboard::Key::Escape))
			break;

		if (manager.OnKeyDown(Keyboard::Key::Return))
			fsm.change(mainMenu);

		// fsm.update(3.14f);
		fsm.draw();

		manager.UpdatePreviousStates();
	}

	/**
	 * \bug Wenn in obiger Schleife Return gedrückt wurde, wird das Programm nach Drücken von Escape in der Schleife ohne anzuhalten beendet.
	 */
	Utils::PauseConsole();

	return EXIT_SUCCESS;
}
