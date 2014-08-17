//MenuScene.cpp

#include "stdafx.h"

#include "MenuScene.h"

MenuScene::MenuScene()
{
	m_GUIManager = new GUIManager;
}

void MenuScene::Enter()
{
	m_world->ClearLevel();

	m_iAlpha = 255;

	m_world->SetBackgroundRGB(m_iRed, m_iGreen, m_iBlue, m_iAlpha);

	m_world->SetViewToDefault();

	m_GUIManager->Initialise(m_world);
}

void MenuScene::Exit()
{
	m_GUIManager->Cleanup();
}

void MenuScene::Update(float deltatime)
{
	//Keyboard actions
	if (m_world->GetInputManager()->m_Gamepad->ButtonIsDownOnce(0, GamepadButton::START))
	{
		m_NextScene = PLAYSCENE;
		m_bDone = true;
	}
	else if (m_world->GetInputManager()->m_Keyboard->KeyIsDoneOnce(sf::Keyboard::Num1))
	{
		m_NextScene = PLAYSCENE;
		m_bDone = true;
	}
	else if (m_GUIManager->GetChangeScene())
	{
		m_NextScene = m_GUIManager->GetNextSceneName();
		m_bDone = true;
	}
	else if (m_GUIManager->GetExitGame())
	{
		m_world->GetWindow()->close();
	}

	//Game logic
	m_world->UpdateWorld(deltatime);

	m_GUIManager->Update(m_world->GetInputManager()->m_Mouse->GetPosition());

	//Handle drawing
	m_world->DrawGUI(m_GUIManager);
}

void MenuScene::Cleanup()
{
	//Clear the world pointer
	if (m_world != nullptr)
		m_world = nullptr;

	//GUI
	if (m_GUIManager != nullptr)
	{
		m_GUIManager->Cleanup();
		delete m_GUIManager;
		m_GUIManager = nullptr;
	}
}