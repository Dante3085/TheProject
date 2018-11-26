#include "State.h"
#include "DrawableEntity.h"
#include <iostream>
#include <string>

namespace TheProject
{
	State::State()
		: m_name{ "UNNAMED" }, m_entities{ new std::vector<Entity*>{} }, m_next{ new std::vector<EState>{} }
	{
		m_next->push_back(debugging);
		m_next->push_back(inventory);
	}

	State::State(const std::string& name)
		: m_name{ name }, m_entities(new std::vector<Entity*>{}), m_next{ new std::vector<EState>{} }
	{
		m_next->push_back(debugging);
		m_next->push_back(inventory);
	}

	State::State(const std::string& name, std::vector<Entity*>* entities, std::vector<EState>* next)
		: m_name{name}, m_entities(entities), m_next{ next }
	{
	}

	State::~State()
	{
		// Delete all Entities of this State
		for (int i = 0; i < m_entities->size(); i++)
			delete m_entities->at(i);

		// Delete Entity container of this State
		delete m_entities;

		// Delete next container of this State
		delete m_next;
	}

	void State::update(float gameTime)
	{
		// Habe es nicht hinbekommen einen erweiterten for-loop zum laufen zu bringen
		for (int i = 0; i < m_entities->size(); i++)
			m_entities->at(i)->update(gameTime);
	}

	void State::draw(sf::RenderTarget& rt)
	{
		DrawableEntity* drawEnt;
		for (int i = 0; i < m_entities->size(); i++)
		{
			// Wie checke ich hier, ob die Entity an der Stelle i eine DrawableEntitiy ist ?
			if ((drawEnt = dynamic_cast<DrawableEntity*>(m_entities->at(i))))
				drawEnt->draw(rt);
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

	/*std::string State::getName() const
	{
		return m_name;
	}

	std::vector<Entity*>* State::getEntities() const
	{
		return m_entities;
	}

	std::vector<EState>* State::getNext() const
	{
		return m_next;
	}*/
}