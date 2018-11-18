#pragma once
#include "Entity.h"
#include <vector>
#include "FiniteStateMachine.h"

class State
{
public:
	State();
	State(std::vector<Entity*>* entities, std::vector<EState>* next);
	~State();

	void update(float gameTime);
	void draw(/* TODO */);

private:

	/**
	 * \brief Entities that inhabit this State.
	 */
	std::vector<Entity*>* m_entities;


	/**
	 * \brief States that can be reached from this State.
	 */
	std::vector<EState>* m_next;


};

