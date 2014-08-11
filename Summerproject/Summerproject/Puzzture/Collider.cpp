//Collider.cpp

#include "stdafx.h"

#include "Collider.h"

//Constructors

Collider::Collider(sf::Vector2f position, sf::Vector2f extension)
{
	m_position = position;
	m_extension = extension;

	m_Hitbox = new sf::RectangleShape(m_extension);
	m_Hitbox->setPosition(m_position);

	m_Hitbox->setFillColor(sf::Color(0, 0, 0, 0));
	m_Hitbox->setOutlineColor(sf::Color::Red);
	m_Hitbox->setOutlineThickness(0.5f);
}

//Essential functions

bool Collider::Overlap(Collider* other, sf::Vector2f &offsetSelf, sf::Vector2f &offsetOther)
{
	/*
		Collision check with SAT, seperating axis theorem
	

	//check if it intersects on x coordinates
	float firstwidth = m_extension.x/2;
	float secondwidth = other->getExtension().x/2;

	float differencex = (m_position.x + firstwidth) - (other->getPosition().x + secondwidth);

	if (fabs(differencex) <= (firstwidth + secondwidth))
	{
		//Check if it intersects on y coordinates
		float firstheight = m_extension.y/2;
		float secondheight = other->getExtension().y/2;

		float differencey = (m_position.y + firstheight) - (other->getPosition().y + secondheight);

		if (fabs(differencey) <= (firstheight + secondheight))
		{
			return true;
		}
	}

	return false;
	*/

	

}

bool Collider::Overlap(sf::View* viewport)
{
	float AxMin, AxMax, AyMin, AyMax;
	float BxMin, BxMax, ByMin, ByMax;

	AxMax = m_position.x + m_extension.x;
	AxMin = m_position.x;
	AyMax = m_position.y + m_extension.y;
	AyMin = m_position.y;

	BxMax = viewport->getCenter().x + viewport->getSize().x / 2;
	BxMin = viewport->getCenter().x - viewport->getSize().x / 2;
	ByMax = viewport->getCenter().y + viewport->getSize().y / 2;
	ByMin = viewport->getCenter().y - viewport->getSize().y / 2;

	if (AxMin < BxMax && AxMax > BxMin
		&& AyMin < ByMax && AyMax > ByMin)
	{
		return true;
	}
	else
		return false;
}

void Collider::Cleanup()
{
	//hitbox visualisation
	if (m_Hitbox != nullptr)
	{
		delete m_Hitbox;
		m_Hitbox = nullptr;
	}
}

void Collider::Update(float deltatime)
{
	m_velocity = m_position - m_lastPosition;
	m_lastPosition = m_position;
}