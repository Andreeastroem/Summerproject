//Engine.cpp

//Include the precompiled header first
#include "stdafx.h"

#include "Engine.h"

Engine::Engine()
{
};

bool Engine::Initialise()
{
	//Initialise Managers
	m_DrawManager = new DrawManager;
	m_ConfigManager = new ConfigManager;
	m_InputManager = new InputManager;
	m_SceneManager = new SceneManager;
	m_EntityManager = new EntityManager;
	m_TextureManager = new TextureManager;

	//World
	m_World = new World;
	

	//conditions for continuing (managers)
	if (m_DrawManager == nullptr)
		return false;
	if (!m_ConfigManager->Initialise("../data/"))
		return false;
	if (!m_InputManager->Initialise())
		return false;
	if (!m_TextureManager->Initialise("../data/Textures/", "png"))
		return false;
	

	//Load from Config file
	m_ConfigManager->ReadFile("Config.txt");

	//Time variables
	m_fDeltatime = 0.0f;
	m_GameClock = sf::Clock();
	m_PreviousTime = m_GameClock.restart();

	//Screen
	
	m_iScreenWidth = m_ConfigManager->ReadInt("WindowWidth"); //Screen width

	m_iScreenHeight = m_ConfigManager->ReadInt("WindowHeight");	//Screen height

	if (m_ConfigManager->ReadInt("WindowAntiAliasing") <= 8)
		m_WindowSettings.antialiasingLevel = m_ConfigManager->ReadInt("WindowAntiAliasing");		//Anti aliasing
	else
		m_WindowSettings.antialiasingLevel = 8;
	

	m_Window = new sf::RenderWindow(sf::VideoMode(m_iScreenWidth, m_iScreenHeight),
		"SummerProject", sf::Style::Default, m_WindowSettings);						//New window

	//Validation of the window
	if (m_Window == nullptr)
		return false;

	//Condidition for continuing (world)
	if (!m_World->Initialise(m_Window, m_DrawManager, m_ConfigManager, m_InputManager, m_EntityManager, m_TextureManager))
		return false;

	//Validation of the SceneManager
	if (!m_SceneManager->Initialise(m_World))
		return false;

	//Initalise the states
	m_SceneManager->Attach(MENUSCENE);
	m_SceneManager->Attach(PLAYSCENE);

	//Game conditions
	m_bRunning = true;

	//Extra features
	m_bPause = false;

	//end of function
	return true;
}

void Engine::Run()
{
	m_GameClock.restart();
	//Start the loop
	while (m_bRunning)
	{
		//Any events that has occured?
		sf::Event event;
		while (m_Window->pollEvent(event))
		{
			m_InputManager->Update(&event.type, event);

			//X marks the spot
			if (event.type == sf::Event::Closed 
				|| m_InputManager->ClosedWindow() 
				|| m_InputManager->m_Gamepad->ButtonIsDownOnce(0, GamepadButton::BACK))
			{
				m_Window->close();
				m_bRunning = false;
			}
		}

		//Update the deltatime
		UpdateDeltatime();

		if (!m_bPause)
		{
			//Update the Scene
			m_SceneManager->Update(m_fDeltatime);
			if (!m_Window->isOpen())
				m_bRunning = false;
		}

		if (m_InputManager->m_Keyboard->KeyIsDoneOnce(sf::Keyboard::Space))
		{
			//m_bPause = !m_bPause;
		}

		//Refresh the Input
		m_InputManager->PostUpdate();
	}
}

void Engine::Cleanup()
{
	if (m_Window != nullptr)
	{
		delete m_Window;
		m_Window = nullptr;
	}
	
	if (m_DrawManager != nullptr)
	{
		delete m_DrawManager;
		m_DrawManager = nullptr;
	}

	if (m_ConfigManager != nullptr)
	{
		delete m_ConfigManager;
		m_ConfigManager = nullptr;
	}

	if (m_InputManager != nullptr)
	{
		m_InputManager->Cleanup();
		delete m_InputManager;
		m_InputManager = nullptr;
	}

	if (m_EntityManager != nullptr)
	{
		m_EntityManager->Cleanup();
		delete m_EntityManager;
		m_EntityManager = nullptr;
	}

	if (m_SceneManager != nullptr)
	{
		m_SceneManager->Cleanup();

		delete m_SceneManager;
		m_SceneManager = nullptr;
	}

	if (m_TextureManager != nullptr)
	{
		m_TextureManager->Cleanup();

		delete m_TextureManager;
		m_TextureManager = nullptr;
	}
}

void Engine::UpdateDeltatime()
{
	//create a temporary Time
	sf::Time tempTime;
	tempTime = m_GameClock.getElapsedTime();

	//setting the deltatime
	m_fDeltatime = tempTime.asSeconds() - m_PreviousTime.asSeconds();

	//changing the previous time
	m_PreviousTime = tempTime;
}