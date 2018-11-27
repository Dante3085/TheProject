#pragma once
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"
#include "Enums.h"
#include <iostream>

namespace TheProject
{
	struct Animation
	{
		int indexSpriteSheet;
		std::vector<sf::Rect<int>> frames;
		float frameDelay;
		bool mirror;
		bool reverse;

		Animation()
			: indexSpriteSheet{0}, frames{std::vector<sf::Rect<int>>{}}, frameDelay{.2f}, mirror{false},
		reverse{false}
		{
		}

		Animation(int indexSpriteSheet, const std::vector<sf::Rect<int>>& frames, float frameDelay = .2f, bool mirror = false,
			bool reverse = false)
			: indexSpriteSheet{indexSpriteSheet}, frames{frames}, frameDelay{frameDelay}, mirror{mirror}, reverse{reverse}
		{
		}
	};

	/**
	 * \brief Uses the frames of a SpriteSheet to create a Sprite with Animation
	 * \author mjsch
	 */
	class AnimatedSprite : public DrawableEntity
	{
	public:
		AnimatedSprite(const std::vector<std::string> spriteSheetLocations, const sf::Vector2f& pos, float speed = 200.f);
		~AnimatedSprite();

		/**
		 * \attention Needs additional Documentation
		 * \brief Updates this AnimatedSprite
		 * \param deltaTime Information about Game Time
		 */
		void update(float deltaTime) override;

		/**
		 * \attention Does inline make sense ?
		 * \brief Draws this AnimatedSprite on the given RenderTarget
		 * \param rt RenderTarget that this AnimatedSprite is drawn on
		 */
		inline void draw(sf::RenderTarget& rt) const override;

		/**
		 * \attention Inaccurate Documentation
		 * \brief Manipulates this AnimatedSprite's velocity so that it goes in the passed direction
		 * \param dir Direction the AnimatedSprite will face
		 */
		inline void setDirection(const sf::Vector2f& dir);

		
		void addAnimation(EAnimation name, int indexSpriteSheet, int frameWidth, int frameHeight, int yRow, int xCol,
			int numFrames, float frameDelay = .2f, bool mirror = false, bool reverse = false);

		/**
		 * \brief Sets the currentAnimation of this AnimatedSprite to animation
		 * \param animation Animation that the currentAnimation of this AnimatedSprite will be set to
		 */
		void setAnimation(EAnimation animation);

		/**
		 * \brief Sets this AnimatedSprite's position to passed position
		 * \param position Position this AnimatedSprite will be set to
		 */
		inline void setPosition(const sf::Vector2f& position);

		/**
		 * \brief Returns this AnimatedSprite's position.
		 * \return This AnimatedSprite's position
		 */
		inline const sf::Vector2f& getPosition() const;

		inline void setDrawBounds(bool drawBounds);
		inline bool getDrawBounds() const;

		inline void setScaleFactor(float scaleFactor);
		inline float getScaleFactor() const;

		inline void setAnimationFrameDelay(EAnimation name, float frameDelay);
		inline float getAnimationFrameDelay(EAnimation name);

		inline void setAnimationMirror(EAnimation name, bool mirror);
		inline bool getAnimationMirror(EAnimation name);

		inline void setAnimationReverse(EAnimation name, bool reverse);
		inline bool getAnimationReverse(EAnimation name);

	private:

		/**
		 * \brief Plays the currentAnimation of this AnimatedSprite
		 * \param deltaTime
		 */
		void playAnimation(float deltaTime);

		/**
		 * \note constexpr: Gibt Compiler Hinweis, dass Wert bereits zur Compilezeit ausgewertet werden kann und nicht erst zur Laufzeit (Performance)
		 * \brief Speed of this AnimatedSprite in pps (pixels-per-second)
		 */
		float m_speed;

		/**
		 * \brief Sprite of this AnimatedSprite
		 */
		sf::Sprite m_sprite;

		std::vector<sf::Texture> m_spriteSheets;

		/**
		 * \brief Position of this AnimatedSprite
		 */
		sf::Vector2f m_pos;

		/**
		 * \brief Velocity of this AnimatedSprite
		 */
		sf::Vector2f m_vel;

		/**
		 * \brief Stores on which frame of the currentAnimation the AnimatedSprite currently is
		 */
		int m_currentFrameIndex;

		/**
		 * \brief Current Animation of this AnimatedSprite
		 */
		EAnimation m_currentAnimation;

		std::map<EAnimation, Animation> m_animations;

		/**
		 * \brief Stores how much time has passed since last setting a frame of the currentAnimation
		 */
		float m_elapsedSeconds;

		/**
		 * \brief Lines for drawing this AnimatedSprite's bounds
		 */
		std::vector<sf::RectangleShape> m_lines;

		bool m_drawBounds;

		float m_scaleFactor;
	};

	inline void AnimatedSprite::draw(sf::RenderTarget& rt) const
	{
		rt.draw(m_sprite);
		if (m_drawBounds)
			DrawableEntity::drawBounds(rt, m_sprite.getGlobalBounds(), m_lines);
	}

	inline void AnimatedSprite::setDirection(const sf::Vector2f& dir)
	{
		m_vel = dir * m_speed;
	}

	inline void AnimatedSprite::setPosition(const sf::Vector2f& position)
	{
		m_pos = position;
	}

	inline const sf::Vector2f& AnimatedSprite::getPosition() const
	{
		return m_pos;
	}

	inline void AnimatedSprite::setDrawBounds(bool drawBounds)
	{
		m_drawBounds = drawBounds;
	}

	inline bool AnimatedSprite::getDrawBounds() const
	{
		return m_drawBounds;
	}

	inline void AnimatedSprite::setScaleFactor(float scaleFactor)
	{
		m_scaleFactor = scaleFactor;
		m_animations[m_currentAnimation].mirror ? m_sprite.setScale(-1.f * m_scaleFactor, m_scaleFactor) :
			m_sprite.setScale(m_scaleFactor, m_scaleFactor);
	}

	inline float AnimatedSprite::getScaleFactor() const
	{
		return m_scaleFactor;
	}

	inline void AnimatedSprite::setAnimationFrameDelay(EAnimation name, float frameDelay)
	{
		m_animations[name].frameDelay = frameDelay;
	}

	inline float AnimatedSprite::getAnimationFrameDelay(EAnimation name)
	{
		return m_animations[name].frameDelay;
	}

	inline void AnimatedSprite::setAnimationMirror(EAnimation name, bool mirror)
	{
		m_animations[name].mirror = mirror;
	}

	inline bool AnimatedSprite::getAnimationMirror(EAnimation name)
	{
		return m_animations[name].mirror;
	}

	inline void AnimatedSprite::setAnimationReverse(EAnimation name, bool reverse)
	{
		m_animations[name].reverse = reverse;
	}

	inline bool AnimatedSprite::getAnimationReverse(EAnimation name)
	{
		return m_animations[name].reverse;
	}

}
