//PlayerEntity.cpp

#include "stdafx.h"

#include "PlayerEntity.h"

//Constructors
PlayerEntity::PlayerEntity(World* world, sf::Vector2f positionOffset, sf::Vector2f extensionOffset)
{
	m_World = world;

	m_PositionOffset = positionOffset;
	m_ExtensionOffset = extensionOffset;
}

//Inherited functions
bool PlayerEntity::Initialise(EntityData entitydata)
{
	Entity::Initialise(entitydata);

	m_EntityData = entitydata;

	m_Shape = new sf::RectangleShape();
	m_Shape->setSize(m_EntityData.size);

	m_Shape->setPosition(m_EntityData.position);

	m_Collider = new Collider(m_EntityData.position + m_PositionOffset, m_EntityData.size + m_ExtensionOffset);

	m_Shape->setFillColor(sf::Color::Black);

	if (m_World == nullptr)
		return false;

	if (m_Shape == nullptr)
		return false;

	m_fBaseMovementSpeed = 0.5;
	m_fJumpForce = 0.4;
	m_fGamepadSpeed = 10;

	m_bGrounded = false;

	m_Facing = RIGHT;
	m_bHoldingItem = false;

	return true;
}

void PlayerEntity::Cleanup()
{
	if (m_World != nullptr)
		m_World = nullptr;

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

	//Entity clean up
	if (m_Entity != nullptr)
		m_Entity = nullptr;
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
	m_World->SetView(sf::Vector2f(m_EntityData.position.x + m_EntityData.size.x / 2, m_EntityData.position.y + m_EntityData.size.y / 2));

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

	float gamepadMovement = m_World->GetInputManager()->m_Gamepad->GetJoystickValue(Player::ONE, sf::Joystick::X);

	//Horizontal movement
	/*
	Only adjust movement with gamepad if the movement is big
	*/
	if (fabs(gamepadMovement) > 10)
	{
		m_EntityData.force.x += deltatime * ((gamepadMovement / 100) * m_fBaseMovementSpeed);

		if (gamepadMovement < 0)
			m_Facing = LEFT;
		else
			m_Facing = RIGHT;
	}
	else if (m_World->GetInputManager()->m_Keyboard->KeyIsDown(sf::Keyboard::Right))
	{
		m_EntityData.force.x += deltatime * m_fBaseMovementSpeed;
		m_Facing = RIGHT;
	}
	else if (m_World->GetInputManager()->m_Keyboard->KeyIsDown(sf::Keyboard::Left))
	{
		m_EntityData.force.x -= deltatime * m_fBaseMovementSpeed;
		m_Facing = LEFT;
	}

	//jumping
	if (m_World->GetInputManager()->m_Keyboard->KeyIsDown(sf::Keyboard::Space) ||
		m_World->GetInputManager()->m_Gamepad->ButtonIsDown(Player::ONE, GamepadButton::A))
	{
		if (m_bGrounded)
		{
			Jump();
		}
	}

	//Items
	if (m_World->GetInputManager()->m_Keyboard->KeyIsDoneOnce(sf::Keyboard::Z) ||
		m_World->GetInputManager()->m_Gamepad->ButtonIsDownOnce(Player::ONE, GamepadButton::B))
	{
		if (!m_bHoldingItem)
			Pickup();
		else
			PutItem();
	}

	//Gravitation && friction
	if (!m_bGrounded)
	{
		m_EntityData.force.y += 0.98 * deltatime;
	}
	else
	{
		m_EntityData.force.x *= 0.995;
		if (fabs(m_EntityData.force.x) < 0.0001f)
			m_EntityData.force.x = 0;
	}

	//Calculate movement
	m_EntityData.position += m_EntityData.force;

	UpdatePositions();
}

bool PlayerEntity::CanJump()
{
	sf::FloatRect feet;
	feet.top = m_Collider->getPosition().y + m_Collider->getExtension().y;
	feet.left = m_Collider->getPosition().x;
	feet.height = 1;
	feet.width = m_Collider->getExtension().x;

	if (m_World->Intersect(feet) != nullptr)
		return true;

	return false;
}

void PlayerEntity::Jump()
{
	m_EntityData.force.y -= m_fJumpForce;
	m_bGrounded = false;
}

void PlayerEntity::Pickup()
{
	sf::FloatRect hand;

	if (m_Facing == RIGHT)
	{
		hand.top = m_Collider->getPosition().y + (m_Collider->getExtension().y * 0.3);
		hand.left = m_Collider->getPosition().x + m_Collider->getExtension().x;
	}
	else if (m_Facing == LEFT)
	{
		hand.top = m_Collider->getPosition().y + (m_Collider->getExtension().y * 0.3);
		hand.left = m_Collider->getPosition().x - m_Collider->getExtension().x;
	}

	hand.height = m_Collider->getExtension().y * 0.5;
	hand.width = m_Collider->getExtension().x;

	Entity* object = m_World->Intersect(hand);

	if (object != nullptr)
	{
		if (object->GetEntityData().entityType == FURNITURE)
		{
			if (!m_bHoldingItem)
			{
				m_Entity = object;
				m_Entity->SetPosition(sf::Vector2f(0, -64));
				m_Entity->UpdatePositions();

				m_bHoldingItem = true;
			}
		}
	}

	object = nullptr;
}

void PlayerEntity::PutItem()
{
	sf::FloatRect box;

	if (m_Facing == RIGHT)
	{
		box.top = m_Collider->getPosition().y + (m_Collider->getExtension().y * 0.3);
		box.left = m_Collider->getPosition().x + m_Collider->getExtension().x;
		box.height = m_Entity->getCollider()->getExtension().x;
		box.width = m_Entity->getCollider()->getExtension().x;
	}
	else if (m_Facing == LEFT)
	{
		box.top = m_Collider->getPosition().y + (m_Collider->getExtension().y * 0.3);
		box.left = m_Collider->getPosition().x - m_Entity->getCollider()->getExtension().x;
		box.height = m_Entity->getCollider()->getExtension().x;
		box.width = m_Entity->getCollider()->getExtension().x;
	}

	Entity* object = m_World->Intersect(box);

	if (object == nullptr)
	{
		m_Entity->SetPosition(sf::Vector2f(box.left, box.top));
		m_Entity->GetEntityData().force = sf::Vector2f(0, 0);

		m_Entity->UpdatePositions();

		m_bHoldingItem = false;
	}
	else
	{
		Log::Message("An entity was detected. Position:");
		Log::Message(object->getCollider()->getPosition());
	}

	object = nullptr;
}

//Lazy functions

void PlayerEntity::UpdatePositions()
{
	m_Shape->setPosition(m_EntityData.position);
	m_Sprite->setPosition(m_EntityData.position);
	m_Collider->SetPosition(m_EntityData.position + m_PositionOffset);
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