//PlayerEntity.h

#pragma once

#include "Entity.h"

#include "World.h"

class PlayerEntity : public Entity
{
public:
	//Constructor
	PlayerEntity(World* world, sf::Vector2f positionOffset, sf::Vector2f extensionOffset);

	//Inherited functions
	bool Initialise(EntityData entitydata);
	void Update(float deltatime);
	void OnCollision(Entity* entity, sf::Vector2f offset);
	void Cleanup();

	//Logic functions
	void Movement(float deltatime);
	bool CanJump();
	void Jump();
	void Pickup();
	void PutItem();

	//Lazy functions
	void UpdatePositions();

	void LogPositions();
	void LogView();
private:
	World* m_World;

	//movement
	float m_fBaseMovementSpeed;
	Direction m_Facing;

	//jumping
	bool m_bGrounded;
	float m_fJumpForce;

	//Pick up furniture
	bool m_bHoldingItem;
	Entity* m_Entity;
};