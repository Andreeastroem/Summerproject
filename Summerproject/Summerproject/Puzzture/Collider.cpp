//Collider.cpp

#include "stdafx.h"

#include "Collider.h"

//Constructors

Collider::Collider(sf::Vector2f position, sf::Vector2f extension)
{
	m_position = position;
	m_extension = extension;

	m_Hitbox = sf::RectangleShape(m_extension);
	m_Hitbox.setPosition(m_position);

	m_Hitbox.setFillColor(sf::Color(0, 0, 0, 0));
	m_Hitbox.setOutlineColor(sf::Color::Red);
	m_Hitbox.setOutlineThickness(0.5f);
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
		//Calculate self
		bool bOtherFromRight = m_velocity.x < 0;
		bool bOtherFromLeft = m_velocity.x > 0;
		bool bOtherFromUp = m_velocity.y > 0;
		bool bOtherFromDown = m_velocity.y < 0;

		if (bOtherFromLeft)
			offsetA.x = BxMin - AxMax;
		else if (bOtherFromRight)
			offsetA.x = BxMax - AxMin;

		else if (bOtherFromUp)
			offsetA.y = ByMin - AyMax;
		else if (bOtherFromDown)
			offsetA.y = ByMax - AyMin;

		//Calculate Other
		bOtherFromRight = other->getVelocity().x < 0;
		bOtherFromLeft = other->getVelocity().x > 0;
		bOtherFromUp = other->getVelocity().y > 0;
		bOtherFromDown = other->getVelocity().y < 0;

		if (bOtherFromLeft)
		{
			//the majority of Y is overlapping
			if (fabs(AyMin - ByMax) > other->getExtension().y / 2)
				offsetB.x = AxMin - BxMax;
			else if (fabs(AyMax - ByMin) > other->getExtension().y / 2)
				offsetB.x = AxMin - BxMax;
		}
		else if (bOtherFromRight)
		{
			if (fabs(AyMin - ByMax) > other->getExtension().y / 2)
				offsetB.x = AxMax - BxMin;
			else if (fabs(AyMax - ByMin) > other->getExtension().y / 2)
				offsetB.x = AxMax - BxMin;
		}
			
		if (bOtherFromUp)
		{
			offsetB.y = AyMin - ByMax;
		}
		else if (bOtherFromDown)
		{
			offsetB.y = AyMax - ByMin;
		}

		return true;
	}

	return false;
}

bool Collider::SATOverlap(Collider* other, sf::Vector2f &offsetA, sf::Vector2f &offsetB)
{
	//check if it intersects on x coordinates
	float firstwidth = m_extension.x / 2;
	float secondwidth = other->getExtension().x / 2;

	float differencex = (m_position.x + firstwidth) - (other->getPosition().x + secondwidth);

	if (fabs(differencex) < (firstwidth + secondwidth))
	{
		//Check if it intersects on y coordinates
		float firstheight = m_extension.y / 2;
		float secondheight = other->getExtension().y / 2;

		float differencey = (m_position.y + firstheight) - (other->getPosition().y + secondheight);

		if (fabs(differencey) < (firstheight + secondheight))
		{
			if (m_position.x < other->getPosition().x)
			{
				//Set the offset, where A is self
				offsetB.x = differencex + (firstwidth + secondwidth);

				//Set the offset, where B is other
				offsetA.x = -differencex - (firstwidth + secondwidth);

				if (m_position.y < other->getPosition().y)
				{
					//Set the offset, where B is other
					offsetB.y = differencey + (firstheight + secondheight);

					//Set the offset, where A is self
					offsetA.y = -differencey - (firstheight + secondheight);
				}
				else
				{
					//Set the offset, where B is other
					offsetB.y = differencey - (firstheight + secondheight);

					//Set the offset, where A is self
					offsetA.y = -differencey + (firstheight + secondheight);
				}
			}
			else
			{
				//Set the offset, where A is self
				offsetB.x = differencex - (firstwidth + secondwidth);

				//Set the offset, where B is other
				offsetA.x = -differencex + (firstwidth + secondwidth);

				if (m_position.y < other->getPosition().y)
				{
					//Set the offset, where B is other
					offsetB.y = differencey + (firstheight + secondheight);

					//Set the offset, where A is self
					offsetA.y = -differencey - (firstheight + secondheight);
				}
				else
				{
					//Set the offset, where B is other
					offsetB.y = differencey - (firstheight + secondheight);

					//Set the offset, where A is self
					offsetA.y = -differencey + (firstheight + secondheight);
				}
			}

			
			

			return true;
		}
	}

	return false;
}

bool Collider::Overlap(sf::View* viewport)
{
	float AxMin, AxMax, AyMin, AyMax;	//Tile

	float BxMin, BxMax, ByMin, ByMax;	//Viewport

	//

	AxMin = m_position.x;
	AxMax = AxMin + m_extension.x;
	AyMin = m_position.y;
	AyMax = AyMin + m_extension.y;

	BxMin = viewport->getCenter().x - viewport->getSize().x / 2;
	BxMax = viewport->getCenter().x + viewport->getSize().x / 2;
	ByMin = viewport->getCenter().y - viewport->getSize().y / 2;
	ByMax = viewport->getCenter().y + viewport->getSize().y / 2;

	if (AxMin < BxMax && AxMax > BxMin
		&& AyMin < ByMax && AyMax > ByMin)
	{
		return true;
	}

	return false;
}

void Collider::Cleanup()
{
}

void Collider::Update(float deltatime)
{
	m_velocity =  m_position - m_lastPosition;
	m_lastPosition = m_position;
}
