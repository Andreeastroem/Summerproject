//SceneManager.cpp

#include "stdafx.h"

#include "InputManager.h"
#include "Scene.h"
#include "SceneManager.h"


//Scenes
#include "PlayScene.h"
#include "MenuScene.h"

SceneManager::SceneManager()
{
	//Set pointer(s) to nullptr
	m_CurrentScene = nullptr;
	m_ConfigManager = nullptr;
	m_DrawManager = nullptr;
	m_Window = nullptr;

	m_InputManager = nullptr;
}
SceneManager::~SceneManager()
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

	//Clean up the states
	if (m_CurrentScene != nullptr)
		m_CurrentScene = nullptr;

	std::map<SceneName, Scene*>::iterator it = m_states.begin();
	while (it != m_states.end())
	{
		if (it->second != nullptr)	//Is the state nullified already?
		{
			delete it->second;
			it->second = nullptr;
		}
		it++;
	}

	//Clean up the Inputs
	if (m_InputManager != nullptr)
	{
		m_InputManager = nullptr;
	}
}

void SceneManager::SetScene(const SceneName &Name)
{
	std::map<SceneName, Scene*>::iterator it = m_states.find(Name);

	if (it == m_states.end())
	{
	}
	else
	{
		if (m_CurrentScene != nullptr)
			m_CurrentScene->Exit();

		m_CurrentScene = it->second;
		m_CurrentScene->Enter();
	}
}

void SceneManager::Attach(SceneName Name)
{
	std::map<SceneName, Scene*>::iterator it = m_states.find(Name);

	if (it == m_states.end())
	{
		switch (Name)
		{
		case PLAYSTATE:
			//Insert new PlayScene into map
			m_states.insert(std::pair<SceneName, Scene*>(Name, new PlayScene()));
			break;
		case MENUSTATE:
			//Insert new MenuScene into map
			m_states.insert(std::pair<SceneName, Scene*>(Name, new MenuScene()));
			break;
		}
		//find the newly created state
		std::map<SceneName, Scene*>::iterator it = m_states.find(Name);
		//Initalise it
		it->second->Initialise(m_DrawManager, m_ConfigManager, m_Window, m_InputManager);
	}

	//If there is no active state, set the first attached state to the current state
	if (m_CurrentScene == nullptr)
		SetScene(Name);
}

void SceneManager::Detach(SceneName Name)
{
	std::map<SceneName, Scene*>::iterator it = m_states.find(Name);

	if (it != m_states.end())
	{
		it->second->Exit();
		m_states.erase(it);
	}
}

void SceneManager::Update(float deltatime)
{
	//Update the current scene
	m_CurrentScene->Update(deltatime);

	//If the state is done
	if (m_CurrentScene->IsDone())
	{
		//Set the new state according to the m_sNextScene variable
		SetScene(m_CurrentScene->NextScene());
	}
}

bool SceneManager::Initialise(DrawManager* draw_mgr, ConfigManager* config_mgr, sf::RenderWindow* window, InputManager* inputManager)
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

	return true;
}

void SceneManager::Cleanup()
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

	//Clean up the states
	if (m_CurrentScene != nullptr)
		m_CurrentScene = nullptr;

	std::map<SceneName, Scene*>::iterator it = m_states.begin();
	while (it != m_states.end())
	{
		if (it->second != nullptr)	//Is the state nullified already?
		{
			delete it->second;
			it->second = nullptr;
		}
		it++;
	}

	//Clean up the Inputs
	if (m_InputManager != nullptr)
	{
		m_InputManager = nullptr;
	}
}