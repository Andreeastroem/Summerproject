//PlayScene.cpp

#include "stdafx.h"

#include "PlayScene.h"

void PlayScene::Enter()
{
	m_iAlpha = 255;

	m_world->SetBackgroundRGB(m_iRed, m_iGreen, m_iBlue, m_iAlpha);
	m_world->LoadLevel(1);

	m_world->GetEntityManager()->AttachEntity(PLAYER);

	float tilewidth = m_world->GetConfigManager()->ReadFloat("tilewidth");
	float tileheight = m_world->GetConfigManager()->ReadFloat("tileheight");

	m_world->SetViewSize(sf::Vector2f(tilewidth * 8, tileheight * 4.5f));
}



void PlayScene::Update(float deltatime)
{
	//Keyboard actions
	if (m_world->GetInputManager()->m_Gamepad->ButtonIsDownOnce(0, GamepadButton::START))
	{
		m_NextScene = MENUSCENE;
		m_bDone = true;
	}
	else if (m_world->GetInputManager()->m_Keyboard->KeyIsDoneOnce(sf::Keyboard::Num1))
	{
		m_NextScene = MENUSCENE;
		m_bDone = true;
	}


	//Game logic
	m_world->UpdateWorld(deltatime);

	//Drawing actions
	m_world->DrawEntities();
}

void PlayScene::Cleanup()
{
	//Clear the world pointer
	if (m_world != nullptr)
		m_world = nullptr;
}