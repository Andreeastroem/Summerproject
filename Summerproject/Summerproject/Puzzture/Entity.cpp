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

}

void Entity::OnCollision(Entity* entity)
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