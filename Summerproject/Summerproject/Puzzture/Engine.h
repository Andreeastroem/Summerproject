//Engine.h

#pragma once

#include "DrawManager.h"
#include "ConfigManager.h"
#include "InputManager.h"
#include "SceneManager.h"

class Engine
{
public:
	Engine();

	//Initialise the game components (managers etc)
	bool Initialise();

	//The Gameloop
	void Run();

	//Take care of memoryleaks (aka make sure pointers are deleted)
	void Cleanup();

	//Update the deltatime
	void UpdateDeltatime();

private:
	//Game conditions
	bool m_bRunning;

	//Screen related variables
	sf::RenderWindow* m_Window;
	sf::ContextSettings m_WindowSettings;
	int m_iScreenWidth;
	int m_iScreenHeight;

	//Time variables
	float m_fDeltatime;
	sf::Clock m_GameClock;
	sf::Time m_PreviousTime;

	//Rendering
	DrawManager* m_DrawManager;

	//Reading from files
	ConfigManager* m_ConfigManager;

	//InputHandling
	InputManager* m_InputManager;

	//Scene System
	SceneManager* m_SceneManager;

	//Temp
};