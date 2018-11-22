#pragma once
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"

namespace TheProject
{
	class AnimatedSprite : public DrawableEntity
	{
	public:
		AnimatedSprite();
		~AnimatedSprite();


		/**
		 * \attention Needs additional Documentation
		 * \brief Updates this AnimatedSprite
		 * \param gameTime Information about gameTime
		 */
		void update(float gameTime) override;

		/**
		 * \attention Does inline make sense ?
		 * \brief Draws this AnimatedSprite on the given RenderTarget
		 * \param rt RenderTarget that this AnimatedSprite is drawn on
		 */
		inline void draw(sf::RenderTarget& rt) const override;


	private:
		sf::Sprite m_sprite;
		sf::Texture m_texture;
		sf::Vector2f m_pos;
	};
}