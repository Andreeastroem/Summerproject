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
	m_Shape->setSize(m_EntityData.size);

	m_Shape->setPosition(m_EntityData.position);

	m_Collider = new Collider(m_EntityData.position, m_EntityData.size);

	m_Shape->setFillColor(sf::Color::Black);

	if (m_world == nullptr)
		return false;

	if (m_Shape == nullptr)
		return false;

	m_fBaseMovementSpeed = 5;
	m_fJumpForce = 5;
	m_fGamepadSpeed = 10;

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
	m_world->SetView(sf::Vector2f(m_EntityData.position.x + m_EntityData.size.x / 2, m_EntityData.position.y + m_EntityData.size.y / 2));

	Entity::Update(deltatime);
}

void PlayerEntity::OnCollision(Entity* entity, sf::Vector2f offset)
{
	switch (entity->GetEntityData().entityType)
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
		m_EntityData.position.x += offset.x;
		m_EntityData.force.x = 0;
	}
	else
	{
		m_EntityData.position.y += offset.y;
	}

	//If the offset is set to correct upwards, we have hit the ground
	if (offset.y < 0)
	{
		m_bGrounded = true;
		m_EntityData.force.y = 0;
	}

	//m_Collider->Update(0);
	UpdatePositions();
}

//Logic functions
void PlayerEntity::Movement(float deltatime)
{
	m_v2fLastPosition = m_EntityData.position;

	float gamepadMovement = m_world->GetInputManager()->m_Gamepad->GetJoystickValue(Player::ONE, sf::Joystick::X);

	//Horizontal movement
	if (fabs(gamepadMovement) > 0)
	{
		m_EntityData.force.x += deltatime * (gamepadMovement / m_fGamepadSpeed);
	}
	else if(m_world->GetInputManager()->m_Keyboard->KeyIsDown(sf::Keyboard::Right))
	{
		m_EntityData.force.x += deltatime * m_fBaseMovementSpeed;
	}
	else if (m_world->GetInputManager()->m_Keyboard->KeyIsDown(sf::Keyboard::Left))
	{
		m_EntityData.force.x -= deltatime * m_fBaseMovementSpeed;
	}

	//jumping
	if (m_world->GetInputManager()->m_Keyboard->KeyIsDown(sf::Keyboard::Space) || 
		m_world->GetInputManager()->m_Gamepad->ButtonIsDown(Player::ONE, GamepadButton::A))
	{
		if (m_bGrounded)
		{
			Jump();
		}
	}

	//Gravitation && friction
	if (!m_bGrounded)
	{
		m_EntityData.force.y += 9.8 * deltatime;
	}
	else
	{
		m_EntityData.force.x /= 1.1f;
		if (fabs(m_EntityData.force.x) < 0.01f)
			m_EntityData.force.x = 0;
	}

	//Calculate movement
	m_EntityData.position += m_EntityData.force;

	UpdatePositions();
}

bool PlayerEntity::CanJump()
{
	sf::FloatRect feet;
	feet.top = m_EntityData.position.y + m_EntityData.size.y;
	feet.left = m_EntityData.position.x;
	feet.height = 1;
	feet.width = m_EntityData.size.x;

	return m_world->Intersect(feet);
}

void PlayerEntity::Jump()
{
	m_EntityData.force.y -= m_fJumpForce;
	m_bGrounded = false;
}

//Lazy functions

void PlayerEntity::UpdatePositions()
{
	m_Shape->setPosition(m_EntityData.position);
	m_Sprite->setPosition(m_EntityData.position);
	m_Collider->SetPosition(m_EntityData.position);
}

void PlayerEntity::LogPositions()
{
	Log::Message(m_EntityData.position);
	Log::Message(m_Collider->getPosition());
	Log::Message(m_Shape->getPosition());
}

void PlayerEntity::LogView()
{
	sf::Vector2f view = sf::Vector2f(m_EntityData.position.x + m_EntityData.size.x / 2,
		m_EntityData.position.y + m_EntityData.size.y / 2);
	Log::Message(view);
}