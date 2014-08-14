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

	m_fBaseMovementSpeed = 5;
	m_fJumpForce = 5;

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
	//Check if grounded
	if (m_bGrounded)
		m_bGrounded = CanJump();

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
		break;
	case FLOOR:
		break;
	case FURNITURE:
		break;
	case CEILING:
		break;
	default:
		break;
	}

	//Fix offset
	if (fabs(offset.x) < fabs(offset.y))
	{
		m_EntityData.Position.x += offset.x;
		m_EntityData.Force.x = 0;
	}
	else
	{
		m_EntityData.Position.y += offset.y;
	}

	//If the offset is set to correct upwards, we have hit the ground
	if (offset.y < 0)
	{
		m_bGrounded = true;
		m_EntityData.Force.y = 0;
	}

	//m_Collider->Update(0);
	UpdatePositions();
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
	if (m_world->GetInputManager()->m_Keyboard->KeyIsDown(sf::Keyboard::Space))
	{
		if (m_bGrounded)
		{
			Jump();
		}
	}

	//Gravitation && friction
	if (!m_bGrounded)
	{
		m_EntityData.Force.y += 9.8 * deltatime;
	}
	else
	{
		m_EntityData.Force.x /= 1.1f;
		if (fabs(m_EntityData.Force.x) < 0.01f)
			m_EntityData.Force.x = 0;
	}

	//Calculate movement
	m_EntityData.Position += m_EntityData.Force;

	UpdatePositions();
}

bool PlayerEntity::CanJump()
{
	sf::FloatRect feet;
	feet.top = m_EntityData.Position.y + m_EntityData.Size.y;
	feet.left = m_EntityData.Position.x;
	feet.height = 1;
	feet.width = m_EntityData.Size.x;

	return m_world->Intersect(feet);
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
	m_Sprite->setPosition(m_EntityData.Position);
	m_Collider->SetPosition(m_EntityData.Position);
}

void PlayerEntity::LogPositions()
{
	Log::Message(m_EntityData.Position);
	Log::Message(m_Collider->getPosition());
	Log::Message(m_Shape->getPosition());
}

void PlayerEntity::LogView()
{
	sf::Vector2f view = sf::Vector2f(m_EntityData.Position.x + m_EntityData.Size.x / 2,
		m_EntityData.Position.y + m_EntityData.Size.y / 2);
	Log::Message(view);
}