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
		//for (DrawableEntity* d1 : m_drawableEntities)
		//{
		//	for (DrawableEntity* d2 : m_drawableEntities)
		//	{
		//		// std::cout << "adress(d1): " << &d1 << std::endl << "adress(d2): " << &d2 << std::endl;
		//		// TODO: Check Sides, Check for collision with one's self
		//		if (&(*d1) != &(*d2) && d1->getBounds().intersects(d2->getBounds()))
		//		{
		//			// TODO: Call a general collisionHandler
		//			sf::Color red = sf::Color::Red;
		//			d1->setBoundingBoxColor(red);
		//			d2->setBoundingBoxColor(red);
		//		}
		//		else
		//		{
		//			sf::Color blue = sf::Color::Blue;
		//			d1->setBoundingBoxColor(blue);
		//			d2->setBoundingBoxColor(blue);
		//		}
		//	}
		//}

		for (int i = 0; i < m_drawableEntities.size(); i++)
		{
			for (int y = 0; y < m_drawableEntities.size(); y++)
			{
				if (i == y)
					continue;

				sf::Color red = sf::Color::Red;
				sf::Color blue = sf::Color::Blue;


				if (m_drawableEntities[i]->getBounds().intersects(m_drawableEntities[y]->getBounds()))
				{
					m_drawableEntities[i]->setBoundingBoxColor(red);
					m_drawableEntities[y]->setBoundingBoxColor(red);
				}
				else
				{
					m_drawableEntities[i]->setBoundingBoxColor(blue);
					m_drawableEntities[y]->setBoundingBoxColor(blue);
				}
			}
		}
	}
}
