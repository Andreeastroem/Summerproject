//GUIRect.cpp

#include "stdafx.h"

#include "GUIRect.h"

//Constructors

GUIRect::GUIRect()
{
	m_Sprite = nullptr;
}

//End of constructors

//Essential functions

bool GUIRect::Initialise(GUISettings settings)
{
	m_Sprite = new sf::Sprite();

	//Early out if failed
	if (m_Sprite == nullptr)
		return false;

	m_Settings = settings;

	m_Sprite->setPosition(settings.position);

	return true;
}

void GUIRect::Cleanup()
{
	//Clear up the sprite
	if (m_Sprite != nullptr)
	{
		delete m_Sprite;
		m_Sprite = nullptr;
	}
}

bool GUIRect::Contains(sf::Vector2f point)
{
	return m_Sprite->getGlobalBounds().contains(point);
}

void GUIRect::OnClick()
{

}

void GUIRect::OnHover()
{
	m_Settings.highlighted = true;
}

void GUIRect::ExitHover()
{
	m_Settings.highlighted = false;
}

//End of essential functions