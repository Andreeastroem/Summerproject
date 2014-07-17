//MenuScene.cpp

#include "stdafx.h"

#include "MenuScene.h"

void MenuScene::Enter()
{
	std::cout << "Menustate" << std::endl;

	m_world->ClearLevel();

	m_iAlpha = 255;

	m_world->SetBackgroundRGB(m_iRed, m_iGreen, m_iBlue, m_iAlpha);

	m_GameView = new sf::View();
	m_world->GetWindow()->setView(m_world->GetWindow()->getDefaultView());
}

void MenuScene::Exit()
{
	
}

void MenuScene::Update(float deltatime)
{
	//Keyboard actions
	if (m_world->GetInputManager()->m_Keyboard->KeyIsDoneOnce(sf::Keyboard::Num1))
	{
		m_sNextScene = PLAYSTATE;
		m_bDone = true;
	}

	if (m_world->GetInputManager()->m_Mouse->ButtonIsDownOnce(MB_LEFT))
	{
		m_sNextScene = PLAYSTATE;
		m_bDone = true;
	}

	//Game logic
	m_world->UpdateWorld(deltatime);

	//Handle drawing
	m_world->DrawWorld();
}

void MenuScene::CleanUp()
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