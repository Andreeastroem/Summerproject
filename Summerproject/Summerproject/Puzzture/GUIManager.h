//GUIManager.h

#pragma once

#include "World.h"

#include "GUIRect.h"

class GUIManager
{
public:
	//Constructors
	GUIManager();

	//Essential functions
	bool Initialise(World* world);
	void Cleanup();

	void Update(sf::Vector2f mouseLocation);

	void AttachButton(GUIElement element, sf::Vector2f position);

	//Access functions
	bool GetChangeScene()
	{
		return m_bChangeScene;
	}
	bool GetExitGame()
	{
		return m_bExitGame;
	}
	bool GetFullscreen()
	{
		return m_bSetFullscreen;
	}
	SceneName GetNextSceneName()
	{
		return m_NextScene;
	}
	std::vector<GUIRect*> GetElements()
	{
		return m_Elements;
	}

private:
	//World pointer
	World* m_World;

	//GUIElements
	std::vector<GUIRect*> m_Elements;

	//GUI text
	sf::Font* m_Font;

	//Scene variables
	bool m_bChangeScene;
	bool m_bExitGame;
	bool m_bSetFullscreen;
	SceneName m_NextScene;
};