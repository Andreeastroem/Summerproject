//World.cpp

#include "stdafx.h"

#include "World.h"

#include "Entity.h"

//Constructors

World::World()
{

}

//Start and Stop functions

bool World::Initialise(sf::RenderWindow* window, DrawManager* drawManager, 
	ConfigManager* configManager, InputManager* inputManager,
	EntityManager* entityManager)
{
	//Initialisation
	m_Window = window;

	m_DrawManager = drawManager;

	m_ConfigManager = configManager;

	m_InputManager = inputManager;

	m_EntityManager = entityManager;

	m_Level = new TileMap;

	//Validation
	if (m_Window == nullptr)
		return false;

	if (m_DrawManager == nullptr)
		return false;

	if (m_ConfigManager == nullptr)
		return false;

	if (m_InputManager == nullptr)
		return false;

	if (!m_EntityManager->Initialise(this))
		return false;

	if (!m_Level->Initialise("Maps", this))
		return false;

	//Everything went OK
	return true;
}

void World::CleanUp()
{
	//Clearing up the managers
	if (m_Window != nullptr)
		m_Window = nullptr;

	if (m_DrawManager != nullptr)
		m_DrawManager = nullptr;
	

	if (m_ConfigManager != nullptr)
		m_ConfigManager = nullptr;

	if (m_InputManager != nullptr)
		m_ConfigManager = nullptr;

	if (m_EntityManager != nullptr)
		m_EntityManager = nullptr;

	if (m_Level != nullptr)
	{
		delete m_Level;
		m_Level = nullptr;
	}
}

//Essential functions

void World::DrawWorld()
{
	//Clear the screen from previous frame
	m_DrawManager->ClearScreen(m_Window, m_iR, m_iG, m_iB, m_iA);

	//Handle drawing
	
	for (unsigned int i = 0; i < m_EntityManager->GetEntites().size(); i++)
	{
		m_DrawManager->DrawShape(m_Window, m_EntityManager->GetEntites().at(i)->GetShape());
	}

	//Display the current frame
	m_DrawManager->DisplayScreen(m_Window);
}

void World::UpdateWorld(float deltatime)
{
	m_EntityManager->Update(deltatime);
}

void World::LoadLevel(int level)
{
	std::string map = "level" + std::to_string(level);

	m_Level->LoadMap(map, level);
}

void World::ClearLevel()
{
	m_EntityManager->ClearEntities();
	m_Level->ClearLevel();
}

void World::ClearWorld()
{
	m_EntityManager->CleanUp();
}

//Access functions

void World::SetBackgroundRGB(int R, int G, int B, int Alpha)
{
	m_iR = R;
	m_iG = G;
	m_iB = B;

	m_iA = Alpha;
}

InputManager* World::GetInputManager()
{
	return m_InputManager;
}

ConfigManager* World::GetConfigManager()
{
	return m_ConfigManager;
}

EntityManager* World::GetEntityManager()
{
	return m_EntityManager;
}

DrawManager* World::GetDrawManager()
{
	return m_DrawManager;
}

TileMap* World::GetLevel()
{
	return m_Level;
}