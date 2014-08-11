//PlayScene.cpp

#include "stdafx.h"

#include "PlayScene.h"

void PlayScene::Enter()
{
	std::cout << "PlayScene" << std::endl;

	m_iAlpha = 255;

	m_world->SetBackgroundRGB(m_iRed, m_iGreen, m_iBlue, m_iAlpha);
	m_world->LoadLevel(1);

	m_world->GetEntityManager()->AttachEntity(PLAYER);

	m_world->SetViewSize(sf::Vector2f(256, 256));
}



void PlayScene::Update(float deltatime)
{
	//Keyboard actions
	if (m_world->GetInputManager()->m_Keyboard->KeyIsDoneOnce(sf::Keyboard::Num1))
	{
		m_NextScene = MENUSTATE;
		m_bDone = true;
	}


	//Game logic
	m_world->UpdateWorld(deltatime);

	//Drawing actions
	m_world->DrawWorld();
}

void PlayScene::Cleanup()
{
	//Clear the world pointer
	if (m_world != nullptr)
		m_world = nullptr;
}