#include "SceneState.h"


namespace TheProject
{
	SceneState::SceneState(const std::string& name, const std::string& backroundLocation, int screenWidth, int screenHeight)
		:State{name}, m_backgroundTex{sf::Texture{}}
	{
		m_backgroundTex.loadFromFile(backroundLocation);
		m_background = sf::Sprite{ m_backgroundTex };
		m_background.setScale(screenWidth / m_background.getLocalBounds().width,
			screenHeight / m_background.getLocalBounds().height);
	}

	SceneState::SceneState(const std::string& name, std::vector<Entity*>* entities, std::vector<EState>* next,
		const std::string& backgroundLocation, int screenWidth, int screenHeight)
		: State{name, entities, next}, m_backgroundTex{sf::Texture{}}
	{
		m_backgroundTex.loadFromFile(backgroundLocation);
		m_background = sf::Sprite{ m_backgroundTex };
		m_background.setScale(screenWidth / m_background.getLocalBounds().width,
			screenHeight / m_background.getLocalBounds().height);
	}

	SceneState::~SceneState()
	{
	}

	void SceneState::draw(sf::RenderTarget& rt)
	{
		rt.draw(m_background);
		State::draw(rt);
	}
}
