#pragma once

namespace TheProject
{
	class Entity
	{
	public:
		virtual ~Entity() {}
		virtual void update(float gameTime) = 0;

	private:
	};
}