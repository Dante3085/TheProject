#pragma once
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"
#include "Enums.h"

namespace TheProject
{

	/**
	 * \brief Uses the frames of a SpriteSheet to create a Sprite with Animation
	 * \author mjsch
	 */
	class AnimatedSprite : public DrawableEntity
	{
	public:
		AnimatedSprite(const std::string& spriteSheetLocation, int frameWidth, int frameHeight, const sf::Vector2f& pos,
			float speed = 200.f, float frameDelay = .2f);
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

		/**
		 * \brief Adds a new Animation to this AnimatedSprite
		 * \param name Name of the new Animation
		 * \param numFrames Number of frames of the new Animation
		 * \param yRow Y-coordinate of the row in the SpriteSheet that the frames for the Animation are in
		 * \param indexFirstFrame Index of first frame in row in the SpriteSheet that the frames for the Animation are in
		 */
		void addAnimation(EAnimation name, int numFrames, int yRow, int indexFirstFrame);

		/**
		 * \brief Sets the currentAnimation of this AnimatedSprite to animation
		 * \param animation Animation that the currentAnimation of this AnimatedSprite will be set to
		 */
		inline void setAnimation(EAnimation animation);

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

		/**
		 * \brief SpriteSheet of this AnimatedSprite
		 */
		sf::Texture m_spriteSheet;

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

		/**
		 * \brief All Animations registered on this AnimatedSprite
		 */
		std::map<EAnimation, std::vector<sf::Rect<int>>> m_animations;

		/**
		 * \brief Width of each frame of the SpriteSheet of this AnimatedSprite
		 */
		int m_frameWidth;

		/**
		 * \brief Height of each frame of the SpriteSheet of this AnimatedSprite
		 */
		int m_frameHeight;

		/**
		 * \brief Stores how much time has passed since last setting a frame of the currentAnimation
		 */
		float m_elapsedMillis;

		/**
		 * \brief Duration in seconds each frame stays on screen
		 */
		float m_frameDelay;
	};

	inline void AnimatedSprite::draw(sf::RenderTarget& rt) const
	{
		rt.draw(m_sprite);
	}

	inline void AnimatedSprite::setDirection(const sf::Vector2f& dir)
	{
		m_vel = dir * m_speed;
	}

	inline void AnimatedSprite::setAnimation(EAnimation animation)
	{
		// Do nothing if passed animation is not known to this AnimatedSprite
		if (m_animations.count(animation) == 0)
			return;

		m_currentAnimation = animation;
	}

	inline void AnimatedSprite::setPosition(const sf::Vector2f& position)
	{
		m_pos = position;
	}

	inline const sf::Vector2f& AnimatedSprite::getPosition() const
	{
		return m_pos;
	}

}