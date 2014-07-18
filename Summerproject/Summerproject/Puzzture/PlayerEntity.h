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
	void CleanUp();

	//Logic functions
	void Movement(float deltatime);
	bool CanJump();
	void Jump();

	//Lazy functions
	void UpdatePositions();

private:
	World* m_world;

	//movement
	float m_fBaseMovementSpeed;

	//jumping
};