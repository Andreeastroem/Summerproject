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
	m_Shape->setSize(m_EntityData.Size);

	m_Shape->setPosition(m_EntityData.Position);

	m_Collider = new Collider(m_EntityData.Position, m_EntityData.Size);

	m_Shape->setFillColor(sf::Color::Black);

	if (m_world == nullptr)
		return false;

	if (m_Shape == nullptr)
		return false;

	m_fBaseMovementSpeed = 20;

	return true;
}

void PlayerEntity::CleanUp()
{
	if (m_world != nullptr)
		m_world = nullptr;

	//Clean up visuals
	if (m_Shape != nullptr)
	{
		delete m_Shape;
		m_Shape = nullptr;
	}
	if (m_Sprite != nullptr)
	{
		delete m_Sprite;
		m_Sprite = nullptr;
	}

	//Clean up collider
	if (m_Collider != nullptr)
	{
		m_Collider->CleanUp();
		delete m_Collider;
		m_Collider = nullptr;
	}
}

void PlayerEntity::Update(float deltatime)
{
	//input
	Movement(deltatime);

	std::cout << deltatime << std::endl;

	//Update collider/visuals position
	UpdatePositions();
	
	//Update the view
	m_world->SetView(sf::Vector2f(m_EntityData.Position.x + m_EntityData.Size.x/2, m_EntityData.Position.y + m_EntityData.Size.y/2));
}

void PlayerEntity::OnCollision(Entity* entity, sf::Vector2f offset)
{
	std::cout << "x: " << offset.x << std::endl;
	std::cout << "y: " << offset.y << std::endl;

	//std::cout << "spelar collision" << std::endl;
	switch (entity->GetEntityData().entitytype)
	{
	case WALL:
		m_EntityData.Position += offset;
		UpdatePositions();
		break;
	case FLOOR:
		m_EntityData.Position += offset;
		UpdatePositions();
		break;
	case FURNITURE:
		m_EntityData.Position += offset;
		UpdatePositions();
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

//Lazy functions

void PlayerEntity::UpdatePositions()
{
	m_Shape->setPosition(m_EntityData.Position);
	m_Collider->SetPosition(m_EntityData.Position);
}