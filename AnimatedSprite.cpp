#include "AnimatedSprite.h"
#include <iostream>
#include <vector>

namespace TheProject
{
	AnimatedSprite::AnimatedSprite(const std::vector<std::string> spriteSheetLocations, const sf::Vector2f& pos, float speed)
		: m_pos{pos}, m_speed{speed}, m_currentFrameIndex{0}, m_currentAnimation{None}, m_animations{std::map<EAnimation, Animation>{}},
	m_spriteSheets{std::vector<sf::Texture>{}}, m_vel{sf::Vector2f{0.f, 0.f}}, m_elapsedSeconds{0}, m_lines{std::vector<sf::RectangleShape>{sf::RectangleShape{}, sf::RectangleShape{},
	sf::RectangleShape{}, sf::RectangleShape{}}}, m_drawBounds{true}
	{
		// Create / Load SpriteSheet Textures
		for (std::string s : spriteSheetLocations)
		{
			sf::Texture tex{};
			tex.loadFromFile(s);
			m_spriteSheets.push_back(tex);
		}

		// Default Spritesheet is first
		if (!m_spriteSheets.empty())
			m_sprite = sf::Sprite{ m_spriteSheets[0] };
		m_sprite.setScale(2.f, 2.f);
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

	/*void AnimatedSprite::addAnimation(EAnimation name, int indexSpriteSheet, int frameWidth, int frameHeight, int yRow, int indexFirstFrame,
		int numFrames, float frameDelay, bool mirror)
	{
		if (indexSpriteSheet < 0 || indexSpriteSheet >= m_spriteSheets.size())
		{
			std::cout << "@AnimatedSprite.addAnimation(): indexSpriteSheet is invalid!" << std::endl;
			return;
		}
		std::vector<sf::Rect<int>> frames;
		for (int i = 0; i < numFrames; i++)
			frames.push_back(sf::Rect<int>{ (i + indexFirstFrame) * frameWidth, yRow, frameWidth, frameHeight });
		m_animations[name] = Animation{indexSpriteSheet, frames, frameDelay, mirror};
	}*/

	void AnimatedSprite::addAnimation(EAnimation name, int indexSpriteSheet, int frameWidth, int frameHeight, int yRow, int xCol,
		int numFrames, float frameDelay, bool mirror)
	{
		if (indexSpriteSheet < 0 || indexSpriteSheet >= m_spriteSheets.size())
		{
			std::cout << "@AnimatedSprite.addAnimation(): indexSpriteSheet is invalid!" << std::endl;
			return;
		}
		std::vector<sf::Rect<int>> frames;

		int frame = 0;
		int spriteSheetWidth = m_spriteSheets[indexSpriteSheet].getSize().x;

		while(frame++ < numFrames)
		{
			if ((xCol * frameWidth) == spriteSheetWidth)
			{
				yRow++;
				xCol = 0;
			}
			frames.push_back(sf::Rect<int>{ xCol++ * frameWidth, yRow * frameHeight, frameWidth, frameHeight});
		}

		m_animations[name] = Animation{ indexSpriteSheet, frames, frameDelay, mirror };
	}

	void AnimatedSprite::playAnimation(float deltaTime)
	{
		// Reset frameIndex if it has exceeded number of frames
		if (m_currentFrameIndex > m_animations[m_currentAnimation].frames.size() - 1)
			m_currentFrameIndex = 0;

		// Go to next frame if frameDelay has passed, reset timer
		if (m_elapsedSeconds > m_animations[m_currentAnimation].frameDelay)
		{
			std::cout << "Frame: " << m_currentFrameIndex << std::endl;
			m_sprite.setTextureRect(m_animations[m_currentAnimation].frames[m_currentFrameIndex++]);
			m_elapsedSeconds = 0;
		}

		// increment timer
		m_elapsedSeconds += deltaTime;
	}

	void AnimatedSprite::setAnimation(EAnimation name)
	{
		// Do nothing if passed animation is not known to this AnimatedSprite or is already set as currentAnimation
		if (m_currentAnimation == name || m_animations.count(name) == 0)
			return;

		m_currentAnimation = name;

		m_sprite.setTexture(m_spriteSheets[m_animations[m_currentAnimation].indexSpriteSheet]);
		m_sprite.setTextureRect(m_animations[m_currentAnimation].frames[1]);

		if (m_animations[m_currentAnimation].mirror)
			m_sprite.setScale(-2.f, 2.f);
		else
			m_sprite.setScale(2.f, 2.f);

		m_elapsedSeconds = 0;
		m_currentFrameIndex = 0;
	}
}
