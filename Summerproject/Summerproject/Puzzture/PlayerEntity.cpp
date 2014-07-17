//PlayerEntity.cpp

#include "stdafx.h"

#include "PlayerEntity.h"

//Constructors
PlayerEntity::PlayerEntity(World* world)
{
	m_world = world;
}

//Inherited functions
bool PlayerEntity::Initialise(EntityData entitydata)
{
	m_EntityData = entitydata;

	m_Shape = new sf::RectangleShape();
	m_Shape->setSize(sf::Vector2f(m_EntityData.Size.width, m_EntityData.Size.height));

	m_Shape->setPosition(m_EntityData.Position);

	m_Shape->setFillColor(sf::Color::Black);

	if (m_world == nullptr)
		return false;

	if (m_Shape == nullptr)
		return false;

	m_fBaseMovementSpeed = 100;

	return true;
}

void PlayerEntity::CleanUp()
{
	if (m_world != nullptr)
		m_world = nullptr;
}

void PlayerEntity::Update(float deltatime)
{
	//input
	Movement(deltatime);

	//Update sprite/shapes position
	m_Shape->setPosition(m_EntityData.Position);
}

void PlayerEntity::OnCollision(Entity* entity)
{
	std::cout << "collision" << std::endl;
	switch (entity->GetEntityData().entitytype)
	{
	case WALL:
		m_EntityData.Position = m_v2fLastPosition;
		break;
	case FLOOR:
		m_EntityData.Position = m_v2fLastPosition;
		break;
	case FURNITURE:
		m_EntityData.Position = m_v2fLastPosition;
		break;
	default:
		break;
	}
}

//Logic functions
void PlayerEntity::Movement(float deltatime)
{
	m_v2fLastPosition = m_EntityData.Position;

	//Gravitation
	//m_EntityData.Position.y += 9.8f * deltatime;

	//Horizontal movement
	if (m_world->GetInputManager()->m_Keyboard->KeyIsDown(sf::Keyboard::Right))
	{
		m_EntityData.Position.x += deltatime * m_fBaseMovementSpeed;
	}
	else if (m_world->GetInputManager()->m_Keyboard->KeyIsDown(sf::Keyboard::Left))
	{
		m_EntityData.Position.x -= deltatime * m_fBaseMovementSpeed;
	}

	//Temporary vertical movement
	if (m_world->GetInputManager()->m_Keyboard->KeyIsDown(sf::Keyboard::Up))
	{
		m_EntityData.Position.y -= deltatime * m_fBaseMovementSpeed;
	}
	else if (m_world->GetInputManager()->m_Keyboard->KeyIsDown(sf::Keyboard::Down))
	{
		m_EntityData.Position.y += deltatime * m_fBaseMovementSpeed;
	}

	//jumping
	if (m_world->GetInputManager()->m_Keyboard->KeyIsDoneOnce(sf::Keyboard::Space))
	{
		if (CanJump())
		{
			Jump();
		}
	}
}

bool PlayerEntity::CanJump()
{
	return true;
}

void PlayerEntity::Jump()
{

}