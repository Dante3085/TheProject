#include "CollisionManager.h"


namespace TheProject
{
	CollisionManager::CollisionManager(std::vector<DrawableEntity*> drawableEntities)
		: m_drawableEntities{drawableEntities}
	{
	}

	CollisionManager::~CollisionManager()
	{
	}

	void CollisionManager::update(float deltaTime)
	{
		for (DrawableEntity* d1 : m_drawableEntities)
		{
			for (DrawableEntity* d2 : m_drawableEntities)
			{
				// std::cout << "adress(d1): " << &d1 << std::endl << "adress(d2): " << &d2 << std::endl;
				// TODO: Check Sides, Check for collision with one's self
				if (&(*d1) != &(*d2) && d1->getBounds().intersects(d2->getBounds()))
				{
					// TODO: Call a general collisionHandler
					sf::Color red = sf::Color::Red;
					d1->setBoundingBoxColor(red);
					d2->setBoundingBoxColor(red);
				}
				else
				{
					sf::Color blue = sf::Color::Blue;
					d1->setBoundingBoxColor(blue);
					d2->setBoundingBoxColor(blue);
				}
			}
		}
	}
}
