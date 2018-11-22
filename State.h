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
		// TODO: Sollte ich hier immer const refs übergeben ?
		State(const std::string& name);
		State(const std::string& name, std::vector<Entity*>* entities, std::vector<EState>* next);
		~State();


		/**
		 * \brief Updates all Entities of this State
		 */
		virtual void update(float gameTime);


		/**
		 * \brief Draws all DrawableEntities of this State
		 */
		virtual void draw();

		/**
		 * \brief Behaviour when FiniteStateMachine changes to this State
		 */
		virtual void onEnter();

		/**
		 * \brief Behaviour when FiniteStateMachine changes from this State to a different State
		 */
		virtual void onExit();

		/**
		 * \brief Returns Name of this State
		 * \return Name of this State
		 */
		std::string getName() const;

		/**
		 * \brief Returns std::vector with all Entities of this State
		 * \return std::vector wit all Entities of this State
		 */
		std::vector<Entity*>* getEntities() const;


		/**
		 * \brief Returns std::vector with EState "references" of all States that can be reached by this State
		 * \return std::vector with EState "references" of all States that can be reached by this State
		 */
		std::vector<EState>* getNext() const;

	private:

		
		/**
		 * \brief Name of this State
		 */
		std::string m_name;

		/**
		 * \brief Entities that inhabit this State
		 */
		// TODO: Müssen das Heap-Objekte sein ?
		std::vector<Entity*>* m_entities;


		/**
		 * \brief States that can be reached from this State
		 */
		 // TODO: Müssen das Heap-Objekte sein ?
		std::vector<EState>* m_next;
	};
}