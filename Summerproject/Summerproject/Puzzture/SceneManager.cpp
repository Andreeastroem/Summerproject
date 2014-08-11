//SceneManager.cpp

#include "stdafx.h"

#include "InputManager.h"
#include "World.h"
#include "Scene.h"
#include "SceneManager.h"


//Scenes
#include "PlayScene.h"
#include "MenuScene.h"

SceneManager::SceneManager()
{
	//Set pointer(s) to nullptr
	m_CurrentScene = nullptr;
	
	m_World = nullptr;
}
SceneManager::~SceneManager()
{
	//Clean up the world
	if (m_World != nullptr)
		m_World = nullptr;

	//Clean up the states
	if (m_CurrentScene != nullptr)
		m_CurrentScene = nullptr;

	std::map<SceneName, Scene*>::iterator it = m_states.begin();
	while (it != m_states.end())
	{
		if (it->second != nullptr)	//Is the state nullified already?
		{
			it->second->Cleanup();
			delete it->second;
			it->second = nullptr;
		}
		it++;
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
		it->second->Initialise(m_World);
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
		//Set the new state according to the m_NextScene variable
		SetScene(m_CurrentScene->NextScene());
	}
}

bool SceneManager::Initialise(World* world)
{
	m_World = world;
	
	//Existence validation
	if (m_World == nullptr)
		return false;

	return true;
}

void SceneManager::Cleanup()
{
	//Clean up World variable
	if (m_World != nullptr)
		m_World = nullptr;

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
}