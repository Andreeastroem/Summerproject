//PlayScene.cpp

#include "stdafx.h"

#include "PlayScene.h"

void PlayScene::Enter()
{
	std::cout << "PlayScene" << std::endl;

	m_iRed = 255;
	m_iAlpha = 255;

	m_world->SetBackgroundRGB(m_iRed, m_iGreen, m_iBlue, m_iAlpha);
	m_world->LoadLevel(1);

	m_world->GetEntityManager()->AttachEntity(PLAYER);

	//Getting the position of the player to put into pointer
	
	//sf::Vector2f tempposition;

	//tempposition = m_world->GetEntityManager()->FindAllEntitiesByType(PLAYER).at(0)->GetEntityData().Position;

	m_GameView = new sf::View();
	m_world->GetWindow()->setView(m_world->GetWindow()->getDefaultView());
}



void PlayScene::Update(float deltatime)
{
	//Keyboard actions
	if (m_world->GetInputManager()->m_Keyboard->KeyIsDoneOnce(sf::Keyboard::Num1))
	{
		m_sNextScene = MENUSTATE;
		m_bDone = true;
	}


	//Game logic
	m_world->UpdateWorld(deltatime);

	//Drawing actions
	m_world->DrawWorld();
}

void PlayScene::CleanUp()
{
	//Clear the world pointer
	if (m_world != nullptr)
		m_world = nullptr;

	//Clear the camera
	if (CameraPosition != nullptr)
	{
		delete CameraPosition;
		CameraPosition = nullptr;
	}

	//Clear the view
	if (m_GameView != nullptr)
	{
		delete m_GameView;
		m_GameView = nullptr;
	}
}