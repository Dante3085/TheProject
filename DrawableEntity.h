#ifndef DRAWABLE_ENTITY_H
#define DRAWABLE_ENTITY_H

#include "Entity.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <iostream>

namespace TheProject
{
	class DrawableEntity : public Entity
	{
	public:

		virtual ~DrawableEntity() {}
		virtual void draw(sf::RenderTarget& rt) const = 0;
		virtual sf::FloatRect getBounds() = 0;
		virtual sf::Color getBoundingBoxColor() = 0;
		virtual void setBoundingBoxColor(sf::Color color) = 0;
		virtual void handleCollision() = 0;

		/**
		 * \brief Draws an outline of the given bounds on the given RenderTarget (Useful for seeing SpriteBounds / CollisionDection)
		 * \param rt 
		 * \param bounds 
		 * \param lines 
		 */
		static void drawBounds(sf::RenderTarget& rt, sf::FloatRect bounds, std::vector<sf::RectangleShape> lines,
			sf::Color color)
		{
			if (lines.size() != 4)
			{
				std::cout << "@drawBounds(): 4 lines have to be passed!" << std::endl;
				return;
			}

			// Problem: {zahl, zahl} erstellt einen Vector2f

			// left
			lines[0].setFillColor(color);
			lines[0].setPosition(bounds.left, bounds.top);
			lines[0].setSize({ 2.f, bounds.height });

			// top
			lines[1].setFillColor(color);
			lines[1].setPosition(bounds.left, bounds.top);
			lines[1].setSize({ bounds.width, 2.f });

			// right
			lines[2].setFillColor(color);
			lines[2].setPosition(bounds.left + bounds.width, bounds.top);
			lines[2].setSize({ 2.f, bounds.height + 2 });

			// bottom
			lines[3].setFillColor(color);
			lines[3].setPosition(bounds.left, bounds.top + bounds.height);
			lines[3].setSize({ bounds.width, 2.f });

			for (sf::RectangleShape r : lines)
				rt.draw(r);
		}
	};
}
#endif