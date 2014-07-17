//World.h

#pragma once

#include "DrawManager.h"
#include "ConfigManager.h"
#include "InputManager.h"
#include "EntityManager.h"
#include "TileMap.h"

class World
{
public:
	World();

	//Initialise the managers
	bool Initialise(sf::RenderWindow* window, DrawManager* drawManager, 
		ConfigManager* configManager, InputManager* inputManager,
		EntityManager* entityManager);

	//Clearing up possible memory leakages
	void CleanUp();

	//Drawing the parts of the world that is meant to be drawn
	void DrawWorld();

	//Updating the managers
	void UpdateWorld(float deltatime);

	//Starting and clearing levels
	void LoadLevel(int level);
	void ClearLevel();

	//Clear the world
	void ClearWorld();

	/*
	Access functions
	*/
	void SetBackgroundRGB(int R, int G, int B, int Alpha);

	sf::RenderWindow* GetWindow()
	{
		return m_Window;
	}

	void SetView(sf::View view)
	{
		m_DrawManager->SetView(m_Window, view);
	}

	InputManager* GetInputManager();

	ConfigManager* GetConfigManager();

	EntityManager* GetEntityManager();

	DrawManager* GetDrawManager();

	TileMap* GetLevel();

private:
	//Managers and consistent variables
	DrawManager* m_DrawManager;
	ConfigManager* m_ConfigManager;
	InputManager* m_InputManager;
	EntityManager* m_EntityManager;

	TileMap* m_Level;

	sf::RenderWindow* m_Window;

	//State dependent variables
	int m_iR, m_iG, m_iB, m_iA;
};