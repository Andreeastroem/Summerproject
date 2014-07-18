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

bool Collider::Overlap(Collider* other, sf::Vector2f &offsetA, sf::Vector2f &offsetB)
{
	float AxMin = m_position.x;
	float AxMax = AxMin + m_extension.x;
	float AyMin = m_position.y;
	float AyMax = AyMin + m_extension.y;

	float BxMin = other->getPosition().x;
	float BxMax = BxMin + other->getExtension().x;
	float ByMin = other->getPosition().y;
	float ByMax = ByMin + other->getExtension().y;

	//Check for collision
	if (AxMin < BxMax && AxMax > BxMin
		&& AyMin < ByMax && AyMax > ByMin)
	{

		//Calculate Other
		bool bOtherFromRight = other->getVelocity().x < 0;
		bool bOtherFromLeft = other->getVelocity().x > 0;
		bool bOtherFromUp = other->getVelocity().y > 0;
		bool bOtherFromDown = other->getVelocity().y < 0;

		if (bOtherFromLeft)
			offsetB.x = AxMin - BxMax;
		else if (bOtherFromRight)
			offsetB.x = AxMax - BxMin;

		else if (bOtherFromUp)
			offsetB.y = AyMin - ByMax;
		else if (bOtherFromDown)
			offsetB.y = AyMax - ByMin;

		return true;
	}

	return false;
}

void Collider::CleanUp()
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
	m_velocity =  m_position - m_lastPosition;
	m_lastPosition = m_position;
}
