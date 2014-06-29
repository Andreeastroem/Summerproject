//PlayScene.cpp

#include "stdafx.h"

#include "PlayScene.h"

void PlayScene::Enter()
{
	std::cout << "PlayScene" << std::endl;

	m_iRed = 255;
	m_iAlpha = 255;

	m_world->SetBackgroundRGB(m_iRed, m_iGreen, m_iBlue, m_iAlpha);
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

	//Drawing actions
	m_world->DrawWorld();
}