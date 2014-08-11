//PlayerEntity.h

#pragma once

#include "Entity.h"

#include "World.h"

class PlayerEntity : public Entity
{
public:
	//Constructor
	PlayerEntity(World* world);

	//Inherited functions
	bool Initialise(EntityData entitydata);
	void Update(float deltatime);
	void OnCollision(Entity* entity, sf::Vector2f offset);
	void Cleanup();

	//Logic functions
	void Movement(float deltatime);
	bool CanJump();
	void Jump();

	//Lazy functions
	void UpdatePositions();

	void LogPositions();
	void LogView();

private:
	World* m_world;

	//movement
	float m_fBaseMovementSpeed;

	//jumping
	bool m_bGrounded;
	float m_fJumpForce;
};