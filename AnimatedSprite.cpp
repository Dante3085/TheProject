#include "AnimatedSprite.h"
#include <iostream>

namespace TheProject
{
	AnimatedSprite::AnimatedSprite()
	{
	}


	AnimatedSprite::~AnimatedSprite()
	{
	}

	void AnimatedSprite::update(float gameTime)
	{
		std::cout << "AnimatedSprite.update()" << std::endl;
	}

	void AnimatedSprite::draw(sf::RenderTarget& rt) const
	{
		rt.draw(m_sprite);
	}
}