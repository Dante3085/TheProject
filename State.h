#pragma once
#include "Entity.h"
#include "Enums.h"
#include <vector>

namespace TheProject
{

	/**
	 * \brief Könnte abstrakt sein
	 */
	class State
	{
	public:
		State();
		State(std::string);
		State(std::string name, std::vector<Entity*>* entities, std::vector<EState>* next);
		~State();


		/**
		 * \brief
		 * \param gameTime Again, GameTime class with more information would be better (elapsed, etc.)
		 */
		void update(float gameTime);


		/**
		 * \brief Draws all DrawableEntities of this State
		 */
		void draw(/* TODO */);

		/**
		 * \brief Behaviour when FiniteStateMachine changes to this State
		 */
		void onEnter();

		/**
		 * \brief Behaviour when FiniteStateMachine changes from this State to a different State
		 */
		void onExit();

		/**
		 * \brief Returns Name of this State
		 * \return Name of this State
		 */
		std::string getName();

		/**
		 * \brief Returns std::vector with all Entities of this State
		 * \return std::vector wit all Entities of this State
		 */
		std::vector<Entity*>* getEntities();


		/**
		 * \brief Returns std::vector with EState "references" of all States that can be reached by this State
		 * \return std::vector with EState "references" of all States that can be reached by this State
		 */
		std::vector<EState>* getNext();

	private:

		
		/**
		 * \brief Name of this State
		 */
		std::string m_name;

		/**
		 * \brief Entities that inhabit this State
		 */
		std::vector<Entity*>* m_entities;


		/**
		 * \brief States that can be reached from this State
		 */
		std::vector<EState>* m_next;
	};
}