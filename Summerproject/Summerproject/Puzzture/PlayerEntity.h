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
	void OnCollision(Entity* entity);
	void CleanUp();

	//Logic functions
	void Movement(float deltatime);
	bool CanJump();
	void Jump();
private:
	World* m_world;

	//movement
	float m_fBaseMovementSpeed;

	//jumping
};