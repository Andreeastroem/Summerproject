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

bool Collider::Overlap(Collider* other, sf::Vector2f &offset)
{
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
			//return the difference between the objects
			
			if (m_position.x < other->getPosition().x)
				differencex = -differencex;

			if (m_position.y < other->getPosition().y)
				differencey = -differencey;

			
			offset.x = differencex;
			offset.y = differencey;

			return true;
		}
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