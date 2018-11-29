#ifndef SCENE_STATE_H
#define SCENE_STATE_H

#include "State.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace TheProject
{
	/**
	 * \brief State with background image
	 */
	class SceneState : public State
	{
	public:
		SceneState(const std::string& name, const std::string& backgroundLocation, int screenWidth, int screenHeight);
		SceneState(const std::string& name, std::vector<Entity*>* entities, std::vector<EState>* next,
			const std::string& backgroundLocation, int screenWidth, int screenHeight);
		~SceneState();

		void draw(sf::RenderTarget& rt) override;

	private:
		sf::Sprite m_background;
		sf::Texture m_backgroundTex;
	};
}
#endif