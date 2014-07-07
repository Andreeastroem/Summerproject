//Entity.cpp

#include "stdafx.h"

#include "Entity.h"

//Constructors
Entity::Entity()
{

}

//Abstract classes
void Entity::Initialise(sf::Vector2f position, sf::IntRect size, int depth, int movementcost)
{

}

void Entity::Update(float deltatime)
{

}

void Entity::CleanUp()
{
	//Clean up the visuals
	if (m_Sprite != nullptr)
	{
		delete m_Sprite;
		m_Sprite = nullptr;
	}
	if (m_Shape != nullptr)
	{
		delete m_Shape;
		m_Shape = nullptr;
	}
}

//Essential functions

//Access functions

sf::Shape* Entity::GetShape()
{
	return m_Shape;
}

sf::Sprite* Entity::GetSprite()
{
	return m_Sprite;
}

bool Entity::IsFlagged()
{
	return m_bFlagged;
}

void Entity::SetFlagged(bool state)
{
	m_bFlagged = state;
}