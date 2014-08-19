//World.cpp

#include "stdafx.h"

#include "World.h"

#include "Entity.h"
#include "GUIManager.h"

//Constructors

World::World()
{

}

//Start and Stop functions

bool World::Initialise(sf::RenderWindow* window, DrawManager* drawManager, 
	ConfigManager* configManager, InputManager* inputManager,
	EntityManager* entityManager, TextureManager* textureManager)
{
	//Initialisation
	m_Window = window;

	m_DrawManager = drawManager;

	m_ConfigManager = configManager;

	m_InputManager = inputManager;

	m_EntityManager = entityManager;

	m_TextureManager = textureManager;

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

	m_GameView = new sf::View(m_Window->getDefaultView());

	m_bDrawHitboxes = false;

	//Everything went OK
	return true;
}

void World::Cleanup()
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

	if (m_TextureManager != nullptr)
		m_TextureManager = nullptr;

	if (m_Level != nullptr)
	{
		delete m_Level;
		m_Level = nullptr;
	}

	//Clear the view
	if (m_GameView != nullptr)
	{
		delete m_GameView;
		m_GameView = nullptr;
	}
}

//Essential functions

void World::Clear()
{
	m_DrawManager->ClearScreen(m_Window, m_iR, m_iG, m_iB, m_iA);
}

void World::DrawEntities()
{
	

	//Clear the screen from previous frame
	Clear();

	//Handle drawing
	std::vector<Entity*> gameEntities = m_EntityManager->GetEntites();

	for (unsigned int i = 0; i < gameEntities.size(); i++)
	{
		if (gameEntities[i]->GetDrawStatus())
		{
			m_DrawManager->DrawSprite(m_Window, m_EntityManager->GetEntites().at(i)->GetSprite());
		}
	}

	if (m_bDrawHitboxes)
	{
		for (unsigned int i = 0; i < gameEntities.size(); i++)
		{
			if (gameEntities[i]->GetDrawStatus())
				m_DrawManager->DrawShape(m_Window, &m_EntityManager->GetEntites().at(i)->getCollider()->getHitbox());
		}
	}

	//Display the current frame
	Display();
}

void World::DrawGUI(GUIManager* guimanager)
{
	Clear();

	std::vector<GUIRect*> guielements = guimanager->GetElements();

	for (int i = 0; i < guielements.size(); i++)
	{
		m_DrawManager->DrawSprite(m_Window, guielements[i]->GetSprite());
	}

	Display();
}

void World::Display()
{
	m_DrawManager->DisplayScreen(m_Window);
}

//END of drawing

void World::UpdateWorld(float deltatime)
{
	//show hitboxes?
	if (m_InputManager->m_Keyboard->KeyIsDoneOnce(sf::Keyboard::F2) ||
		m_InputManager->m_Gamepad->ButtonIsDownOnce(Player::ONE, GamepadButton::RIGHTSHOULDER))
	{
		if (m_bDrawHitboxes)
			m_bDrawHitboxes = false;
		else
			m_bDrawHitboxes = true;
	}

	m_EntityManager->Update(deltatime);

	m_EntityManager->SetDrawStatuses(m_GameView);
}

void World::LoadLevel(int level)
{
	std::string map = "level" + std::to_string(level);

	m_Level->LoadMap(map, level);
	m_Level->LoadEnvironment(level);
}

void World::ClearLevel()
{
	m_EntityManager->ClearEntities();
	m_Level->ClearLevel();
}

void World::ClearWorld()
{
	m_EntityManager->Cleanup();
}

Entity* World::Intersect(sf::FloatRect box)
{
	return m_EntityManager->Intersect(box);
}

//Access functions

void World::SetBackgroundRGB(int R, int G, int B, int Alpha)
{
	m_iR = R;
	m_iG = G;
	m_iB = B;

	m_iA = Alpha;
}