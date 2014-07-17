//Scene.cpp

//Abstract parent class for states

#include "stdafx.h"

#include "Scene.h"

Scene::~Scene()
{
	
}

bool Scene::Initialise(World* world)
{
	m_world = world;
	//Existence validation
	if (m_world == nullptr)
		return false;

	m_GameView = new sf::View();
	m_world->GetWindow()->setView(m_world->GetWindow()->getDefaultView());

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

void Scene::CleanUp()
{
	//Clear the world pointer
	if (m_world != nullptr)
		m_world = nullptr;

	//Clear the view
	if (m_GameView != nullptr)
	{
		delete m_GameView;
		m_GameView = nullptr;
	}
}

bool Scene::IsDone()
{
	return m_bDone;
}

SceneName Scene::NextScene()
{
	return m_sNextScene;
}