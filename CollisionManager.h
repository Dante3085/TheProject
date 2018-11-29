#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <vector>
#include "DrawableEntity.h"

namespace TheProject
{
	class CollisionManager : public Entity
	{
	public:
		CollisionManager(std::vector<DrawableEntity*> drawableEntities);
		~CollisionManager();

		void update(float deltaTime) override;

	private :
		std::vector<DrawableEntity*> m_drawableEntities;
	};
}
#endif