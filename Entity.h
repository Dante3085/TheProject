#ifndef ENTITY_H
#define ENTITY_H

namespace TheProject
{
	class Entity
	{
	public:
		virtual ~Entity() {}
		virtual void update(float deltaTime) = 0;

	private:
	};
}
#endif