//MenuScene.cpp

#include "stdafx.h"

#include "MenuScene.h"

void MenuScene::Enter()
{
	std::cout << "Menustate" << std::endl;

	m_iAlpha = 255;
}

void MenuScene::Exit()
{
}

void MenuScene::Update(float deltatime)
{
	//Keyboard actions
	if (m_InputManager->m_Keyboard->KeyIsDoneOnce(sf::Keyboard::Num1))
	{
		m_sNextScene = PLAYSTATE;
		m_bDone = true;
	}

	if (m_InputManager->m_Mouse->ButtonIsDownOnce(MB_LEFT))
	{
		m_sNextScene = PLAYSTATE;
		m_bDone = true;
	}

	//Game logic

	//Handle drawing
	m_DrawManager->ClearScreen(m_Window, m_iRed, m_iGreen, m_iBlue, m_iAlpha);

	m_DrawManager->DisplayScreen(m_Window);
}