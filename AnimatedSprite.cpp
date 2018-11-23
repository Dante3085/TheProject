#include "AnimatedSprite.h"
#include <iostream>
#include <vector>

namespace TheProject
{

	AnimatedSprite::AnimatedSprite(const std::string& spriteSheetLocation, int frameWidth, int frameHeight, const sf::Vector2f& pos,
		float speed, float frameDelay)
		: m_pos{ pos }, m_currentAnimation{Idle}, m_frameWidth{ frameWidth }, m_frameHeight{ frameHeight },
		m_currentFrameIndex{ 0 },  m_vel({ 0.0f, 0.0f }), m_elapsedMillis{ 0 }, m_speed{ speed }, m_frameDelay{ frameDelay }
	{
		m_spriteSheet.loadFromFile(spriteSheetLocation);
		m_sprite = sf::Sprite{ m_spriteSheet };
		m_sprite.setTextureRect({ 0, 0, frameWidth, frameHeight });
		m_sprite.setScale(3.f, 3.f);
	}


	AnimatedSprite::~AnimatedSprite()
	{
	}

	void AnimatedSprite::update(float deltaTime)
	{
		m_pos += m_vel * deltaTime;
		m_sprite.setPosition(m_pos);
		playAnimation(deltaTime);
	}

	void AnimatedSprite::addAnimation(EAnimation name, int numFrames, int yRow, int indexFirstFrame)
	{
		std::vector<sf::Rect<int>> animation;

		for (int i = 0; i < numFrames; i++)
			animation.push_back(sf::Rect<int>{ (i + indexFirstFrame) * m_frameWidth, yRow, m_frameWidth, m_frameHeight });
		
		m_animations[name] = animation;
	}

	void AnimatedSprite::playAnimation(float deltaTime)
	{
		if (m_currentFrameIndex > m_animations[m_currentAnimation].size() - 1)
			m_currentFrameIndex = 0;

		if (m_elapsedMillis >= m_frameDelay)
		{
			m_sprite.setTextureRect(m_animations[m_currentAnimation][m_currentFrameIndex++]);
			m_elapsedMillis = 0;
		}

		m_elapsedMillis += deltaTime;

		std::cout << "Elapsed-Seconds: " << m_elapsedMillis << std::endl;
	}
}
