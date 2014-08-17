//GUIManager.cpp

#include "stdafx.h"

#include "GUIManager.h"
#include "GUIButton.h"

//Constructors

GUIManager::GUIManager()
{
	m_World = nullptr;
}

//End of constructors

//Essential functions

bool GUIManager::Initialise(World* world)
{
	//Early out
	if (world == nullptr)
		return false;

	m_World = world;

	//Initialise the buttons
	ConfigManager* configmanager = m_World->GetConfigManager();

	configmanager->ReadFile("/GUI/Buttons.txt");

	int number = m_World->GetConfigManager()->ReadInt("amount");

	for (unsigned int i = 0; i < number; i++)
	{
		sf::Vector2f pos = configmanager->ReadVector("button" + std::to_string(i + 1) + "pos");
		GUIElement element = (GUIElement)configmanager->ReadInt("button" + std::to_string(i + 1) + "element");
		std::string texture = configmanager->GetValueFromKey("button" + std::to_string(i + 1) + "texture");

		m_World->GetTextureManager()->LoadTexture(texture);

		AttachButton(element, pos);
	}

	m_bChangeScene = false;
	m_bExitGame = false;
	m_NextScene = MENUSCENE;

	return true;
}

void GUIManager::Cleanup()
{
	if (m_World != nullptr)
		m_World = nullptr;

	//Elements
	for (unsigned int i = 0; i < m_Elements.size(); i++)
	{
		if (m_Elements[i] != nullptr)
		{
			m_Elements[i]->Cleanup();
			delete m_Elements[i];
			m_Elements[i] = nullptr;
		}
	}

	//Font
	if (m_Font != nullptr)
	{
		delete m_Font;
		m_Font = nullptr;
	}
}

void GUIManager::Update(sf::Vector2f mouseLocation)
{
	for (unsigned int i = 0; i < m_Elements.size(); i++)
	{
		if (m_Elements[i]->Contains(mouseLocation))
		{
			m_Elements[i]->OnHover();

			if (m_World->GetInputManager()->m_Mouse->ButtonIsDownOnce(MouseButton::MB_LEFT))
			{
				m_Elements[i]->OnClick();

				if (m_Elements[i]->GetExitGame())
				{
					m_bExitGame = true;
				}
				else if (m_Elements[i]->GetChangeScene())
				{
					m_bChangeScene = true;
					m_NextScene = m_Elements[i]->GetSceneName();
				}
				else if (m_Elements[i]->GetFullscreen())
				{
					m_bSetFullscreen = true;
				}
			}

		}
		else
			m_Elements[i]->ExitHover();
	}
}

void GUIManager::AttachButton(GUIElement element, sf::Vector2f position)
{
	GUIRect::GUISettings settings;
	GUIButton* button = new GUIButton;

	switch (element)
	{
	case STARTBUTTON:
		settings.element = element;
		settings.position = position;

		if (button->Initialise(settings))
		{
			button->SetSpriteTexture(m_World->GetTextureManager()->GetTexture("Start"));
			button->GetSprite()->setPosition(position);

			m_Elements.push_back(button);
		}
		else
		{
			delete button;
			button = nullptr;
		}

		break;
	case EXITBUTTON:
		settings.element = element;
		settings.position = position;

		if (button->Initialise(settings))
		{
			button->SetSpriteTexture(m_World->GetTextureManager()->GetTexture("Exit"));
			button->GetSprite()->setPosition(position);

			m_Elements.push_back(button);
		}
		else
		{
			delete button;
			button = nullptr;
		}


		break;
	default:
		break;
	}
}

//End of essential functions