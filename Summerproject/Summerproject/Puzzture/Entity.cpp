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
	m_Sprite = new sf::Sprite();
	m_Sprite->setPosition(entitydata.position);

	m_bDrawStatus = true;

	return true;
}

void Entity::Update(float deltatime)
{
	m_Collider->Update(deltatime);
}

void Entity::OnCollision(Entity* entity, sf::Vector2f offset)
{

}

void Entity::Cleanup()
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
		m_Collider->Cleanup();
		delete m_Collider;
		m_Collider = nullptr;
	}
}

//Essential functions
