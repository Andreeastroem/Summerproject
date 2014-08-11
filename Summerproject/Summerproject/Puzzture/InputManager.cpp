//InputManager.cpp

#include "stdafx.h"

#include "InputManager.h"

//Keyboard related

Keyboard::Keyboard()
{
	for (int i = 0; i < 256; i++)
	{
		m_CurrentKeyboardButtons[i] = false;
		m_PreviousKeyboardButtons[i] = false;
	}
}

Keyboard::~Keyboard()
{

}

bool Keyboard::KeyIsDown(int key) const
{
	return m_CurrentKeyboardButtons[key];
}

bool Keyboard::KeyIsDoneOnce(int key) const
{
	return m_CurrentKeyboardButtons[key] && !m_PreviousKeyboardButtons[key];
}

void Keyboard::PostUpdate()
{
	//Save the key inputs
	for (int i = 0; i < 256; i++)
	{
		m_PreviousKeyboardButtons[i] = m_CurrentKeyboardButtons[i];
	}
}

//End of Keyboard

//Mouse related

Mouse::Mouse()
{
	for (int i = 0; i < MOUSEBUTTONSIZE; i++)
	{
		m_CurrentMouseButtons[i] = false;
		m_PreviousMouseButtons[i] = false;
	}
}

Mouse::~Mouse()
{

}

bool Mouse::ButtonIsDown(MouseButton button)
{
	return m_CurrentMouseButtons[button];
}

bool Mouse::ButtonIsDownOnce(MouseButton button)
{
	return m_CurrentMouseButtons[button] && !m_PreviousMouseButtons[button];
}

void Mouse::PostUpdate()
{
	for (int i = 0; i < MOUSEBUTTONSIZE; i++)
	{
		m_PreviousMouseButtons[i] = m_CurrentMouseButtons[i];
	}
}

void Mouse::UpdatePosition(sf::Vector2f position)
{
	m_position = position;
}

sf::Vector2f Mouse::GetPosition()
{
	return m_position;
}

//End of mouse

InputManager::InputManager()
{
	CloseWindow = false;
}

bool InputManager::ClosedWindow()
{
	return CloseWindow;
}

bool InputManager::Initialise()
{
	m_Mouse = new Mouse;
	if (m_Mouse == nullptr)
		return false;

	m_Keyboard = new Keyboard;
	if (m_Keyboard == nullptr)
		return false;

	return true;
}

void InputManager::Update(sf::Event::EventType* Eventtype, sf::Event &event)
{
	int KeyboardIndex = 0;
	int MouseIndex = 0;
	float x = 0;
	float y = 0;

	switch (*Eventtype)
	{
		//If there has been any actions on the keyboard
	case sf::Event::KeyPressed:
		//Escape key
		if (event.key.code == sf::Keyboard::Escape)
		{
			CloseWindow = true;
		}

		KeyboardIndex = event.key.code & 0xFF;
		m_Keyboard->m_CurrentKeyboardButtons[KeyboardIndex] = true;


		break;
		//If there has been any releases of keyboard inputs
	case sf::Event::KeyReleased:
		KeyboardIndex = event.key.code & 0xFF;
		m_Keyboard->m_CurrentKeyboardButtons[KeyboardIndex] = false;
		break;


		//Mouse events
	case sf::Event::MouseMoved:
		x = event.mouseMove.x;
		y = event.mouseMove.y;

		m_Mouse->UpdatePosition(sf::Vector2f(x, y));
		break;

	case sf::Event::MouseButtonPressed:
		MouseIndex = event.mouseButton.button & MOUSEBUTTONSIZE;
		m_Mouse->m_CurrentMouseButtons[MouseIndex] = true;
		break;

	case sf::Event::MouseButtonReleased:
		MouseIndex = event.mouseButton.button & MOUSEBUTTONSIZE;
		m_Mouse->m_CurrentMouseButtons[MouseIndex] = false;
		break;

	default:
		break;
	}
}

void InputManager::PostUpdate()
{
	m_Mouse->PostUpdate();
	m_Keyboard->PostUpdate();
}

void InputManager::Cleanup()
{
	if (m_Mouse != nullptr)
	{
		delete m_Mouse;
		m_Mouse = nullptr;
	}

	if (m_Keyboard != nullptr)
	{
		delete m_Keyboard;
		m_Keyboard = nullptr;
	}
}