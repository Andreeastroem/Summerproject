//Entity.cpp

#include "stdafx.h"

#include "Entity.h"

//Constructors
Entity::Entity()
{

}

//Abstract classes
bool Entity::Initialise(EntityData entitydata)
{
	return true;
}

void Entity::Update(float deltatime)
{
	m_Collider->Update(deltatime);
}

void Entity::OnCollision(Entity* entity, sf::Vector2f offset)
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

	//Clean up collision
	if (m_Collider != nullptr)
	{
		m_Collider->CleanUp();
		delete m_Collider;
		m_Collider = nullptr;
	}
}

//Essential functions
