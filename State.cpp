#include "State.h"
#include "DrawableEntity.h"


State::State()
	: m_entities(new std::vector<Entity*>{}), 
	  m_next(new std::vector<EState>{})
{
}


State::State(std::vector<Entity*>* entities, std::vector<EState>* next)
	: m_entities(entities), m_next{next}
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

std::vector<Entity*>* State::getEntities()
{
	return m_entities;
}

std::vector<EState>* State::getNext()
{
	return m_next;
}
