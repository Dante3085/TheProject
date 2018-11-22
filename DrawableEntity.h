#pragma once
#include "Entity.h"
#include <SFML/Graphics/RenderTarget.hpp>

namespace TheProject
{
	class DrawableEntity : public Entity
	{
	public:
		virtual ~DrawableEntity() {}
		virtual void draw(sf::RenderTarget& rt) const = 0;

	private:

	};
}
