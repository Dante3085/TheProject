#include "AnimatedSprite.h"
#include <iostream>

namespace TheProject
{
	AnimatedSprite::AnimatedSprite(const std::string& spriteSheetLocation, const sf::Vector2f& pos)
		: m_pos{pos}
	{
		m_texture.loadFromFile(spriteSheetLocation);
		m_sprite = sf::Sprite{ m_texture };
		m_sprite.setTextureRect({ 50, 37, 50, 37 });
	}


	AnimatedSprite::~AnimatedSprite()
	{
	}

	void AnimatedSprite::update(float deltaTime)
	{
		m_pos += m_vel * deltaTime;
		m_sprite.setPosition(m_pos);
	}

	void AnimatedSprite::draw(sf::RenderTarget& rt) const
	{
		rt.draw(m_sprite);
	}

	void AnimatedSprite::setDirection(const sf::Vector2f& dir)
	{
		m_vel = dir * m_speed;
	}
}
