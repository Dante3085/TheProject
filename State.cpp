#include "State.h"
#include "DrawableEntity.h"
#include <iostream>
#include <string>

namespace TheProject
{
	State::State()
		: m_entities(new std::vector<Entity*>{}), m_name{ "UNNAMED" }, m_next(new std::vector<EState>{})
	{
		m_next->push_back(mainMenu);
		m_next->push_back(inventory);
	}

	State::State(std::string name)
		: m_entities(new std::vector<Entity*>{}), m_name{ name }, m_next(new std::vector<EState>{})
	{
		m_next->push_back(mainMenu);
		m_next->push_back(inventory);
	}

	State::State(std::string name, std::vector<Entity*>* entities, std::vector<EState>* next)
		: m_name{name}, m_entities(entities), m_next{ next }
	{
	}

	State::~State()
	{
	}

	void State::update(float gameTime)
	{
		// Habe es nicht hinbekommen einen erweiterten for-loop zum laufen zu bringen
		for (int i = 0; i < m_entities->size(); i++)
			m_entities->at(i)->update(gameTime);

	}

	void State::draw()
	{
		DrawableEntity* drawEnt;
		for (int i = 0; i < m_entities->size(); i++)
		{
			// Wie checke ich hier, ob die Entity an der Stelle i eine DrawableEntitiy ist ?
			if ((drawEnt = dynamic_cast<DrawableEntity*>(m_entities->at(i))))
				drawEnt->Draw();
		}
	}

	void State::onEnter()
	{
		std::cout << m_name << ": onEnter()" << std::endl;
	}

	void State::onExit()
	{
		std::cout << m_name << ": onExit()" << std::endl;
	}

	std::string State::getName()
	{
		return m_name;
	}

	std::vector<Entity*>* State::getEntities()
	{
		return m_entities;
	}

	std::vector<EState>* State::getNext()
	{
		return m_next;
	}
}