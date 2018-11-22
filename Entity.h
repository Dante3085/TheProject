#pragma once

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