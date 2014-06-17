//Scene.cpp

//Abstract parent class for states

#include "stdafx.h"

#include "Scene.h"

Scene::~Scene()
{
	//clean up drawmanager
	if (m_DrawManager != nullptr)
	{
		m_DrawManager = nullptr;
	}

	//clean up the configmanager
	if (m_ConfigManager != nullptr)
	{
		m_ConfigManager = nullptr;
	}

	//clean up the window
	if (m_Window != nullptr)
	{
		m_Window = nullptr;
	}

	//Player inputs
	if (m_InputManager != nullptr)
	{
		m_InputManager = nullptr;
	}
}

bool Scene::Initialise(DrawManager* draw_mgr, ConfigManager* config_mgr, sf::RenderWindow* window, InputManager* inputManager)
{
	m_DrawManager = draw_mgr;
	//Existence validation
	if (m_DrawManager == nullptr)
		return false;

	m_ConfigManager = config_mgr;
	//Existence validation
	if (m_ConfigManager == nullptr)
		return false;

	m_Window = window;
	//Existence validation
	if (m_Window == nullptr)
		return false;

	m_InputManager = inputManager;
	if (m_InputManager == nullptr)
		return false;

	//Change state variables
	m_bDone = false;
	m_sNextScene = MENUSTATE;

	//Background colours
	m_iRed = 0;
	m_iGreen = 0;
	m_iBlue = 0;

	return true;
}

void Scene::Enter()
{
	
}

void Scene::Exit()
{
	m_bDone = false;
}

void Scene::Update(float deltatime)
{
	
}

bool Scene::IsDone()
{
	return m_bDone;
}

SceneName Scene::NextScene()
{
	return m_sNextScene;
}