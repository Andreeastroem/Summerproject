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
	Entity::Initialise(entitydata);

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
	m_fJumpForce = 50;

	m_bGrounded = false;

	return true;
}

void PlayerEntity::Cleanup()
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
		m_Collider->Cleanup();
		delete m_Collider;
		m_Collider = nullptr;
	}
}

void PlayerEntity::Update(float deltatime)
{
	//input
	Movement(deltatime);

	//Update collider/visuals position
	UpdatePositions();

	//Update the view
	m_world->SetView(sf::Vector2f(m_EntityData.Position.x + m_EntityData.Size.x / 2, m_EntityData.Position.y + m_EntityData.Size.y / 2));

	Entity::Update(deltatime);
}

void PlayerEntity::OnCollision(Entity* entity, sf::Vector2f offset)
{
	switch (entity->GetEntityData().entitytype)
	{
	case WALL:
		m_EntityData.Position.x += offset.x;
		m_EntityData.Position.y = m_v2fLastPosition.y;

		UpdatePositions();
		break;
	case FLOOR:
		m_EntityData.Position.y += offset.y;

		UpdatePositions();
		break;
	case FURNITURE:
		//Fix Y offset and then fix X offset in next frame
		if (fabs(offset.y) > 0.01f)
			m_EntityData.Position.y += offset.y;
		else if (fabs(offset.x) > 0.01f)
			m_EntityData.Position.x += offset.x;

		UpdatePositions();

		break;

	case CEILING:
		m_EntityData.Position.y += offset.y;

		UpdatePositions();
		break;
	default:
		break;
	}

	//If there has been just an offset in Y and not X
	if (fabs(offset.x) < 0.0001f && offset.y < 0)
	{
		m_bGrounded = true;

		m_EntityData.Force.y = 0;

		std::cout << "grounded" << std::endl;
	}

	m_Collider->Update(0);
}

//Logic functions
void PlayerEntity::Movement(float deltatime)
{
	m_v2fLastPosition = m_EntityData.Position;

	//Horizontal movement
	if (m_world->GetInputManager()->m_Keyboard->KeyIsDown(sf::Keyboard::Right))
	{
		m_EntityData.Force.x += deltatime * m_fBaseMovementSpeed;
	}
	else if (m_world->GetInputManager()->m_Keyboard->KeyIsDown(sf::Keyboard::Left))
	{
		m_EntityData.Force.x -= deltatime * m_fBaseMovementSpeed;
	}

	//jumping
	if (m_world->GetInputManager()->m_Keyboard->KeyIsDoneOnce(sf::Keyboard::Space))
	{
		if (CanJump())
		{
			Jump();
		}
	}

	//Gravitation && friction
	if (!m_bGrounded)
	{
		m_EntityData.Force.y += 10;
	}
	else
	{
		m_EntityData.Force.x /= 1.1f;
		if (fabs(m_EntityData.Force.x) < 0.01f)
			m_EntityData.Force.x = 0;
	}

	//Calculate movement
	m_EntityData.Position += m_EntityData.Force;
}

bool PlayerEntity::CanJump()
{
	if (m_bGrounded)
		return true;
	else
		return false;
}

void PlayerEntity::Jump()
{
	m_EntityData.Force.y -= m_fJumpForce;
	m_bGrounded = false;
}

//Lazy functions

void PlayerEntity::UpdatePositions()
{
	m_Shape->setPosition(m_EntityData.Position);
	m_Collider->SetPosition(m_EntityData.Position);
}

void PlayerEntity::LogPositions()
{
	std::cout << "Player: " << "\tX: " << m_EntityData.Position.x << "\tY: " << m_EntityData.Position.y << "\n" << std::endl;
	std::cout << "Collider: " << "\tX: " << m_Collider->getPosition().x << "\tY: " << m_Collider->getPosition().y << "\n" << std::endl;
	std::cout << "Shape: " << "\t\tX: " << m_Shape->getPosition().x << "\tY: " << m_Shape->getPosition().y << "\n" << std::endl;
}

void PlayerEntity::LogView()
{
	std::cout << "View: " << "\t\tX: " << m_EntityData.Position.x + m_EntityData.Size.x / 2 <<
		"\tY: " << m_EntityData.Position.y + m_EntityData.Size.y / 2 << "\n" << std::endl;
}