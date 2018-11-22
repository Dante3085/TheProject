#pragma once
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"

namespace TheProject
{
	class AnimatedSprite : public DrawableEntity
	{
	public:
		AnimatedSprite(const std::string& spriteSheetLocation, const sf::Vector2f& pos);
		~AnimatedSprite();

		/**
		 * \attention Needs additional Documentation
		 * \brief Updates this AnimatedSprite
		 * \param deltaTime Information about Game Time
		 */
		void update(float deltaTime) override;

		/**
		 * \attention Does inline make sense ?
		 * \note 
		 * \brief Draws this AnimatedSprite on the given RenderTarget
		 * \param rt RenderTarget that this AnimatedSprite is drawn on
		 */
		inline void draw(sf::RenderTarget& rt) const override;

		void setDirection(const sf::Vector2f& dir);

	private:

		/**
		 * \note constexpr: Gibt Compiler Hinweis, dass Wert bereits zur Compilezeit ausgewertet werden kann und nicht erst zur Laufzeit (Performance)
		 * \brief Speed in pps (pixels-per-second)
		 */
		static constexpr float m_speed = 25.0f;
		sf::Sprite m_sprite;
		sf::Texture m_texture;
		sf::Vector2f m_pos;
		sf::Vector2f m_vel = { 0.0f, 0.0f };
	};
}