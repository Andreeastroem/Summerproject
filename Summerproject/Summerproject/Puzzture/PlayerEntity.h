//PlayerEntity.h

#pragma once

#include "Entity.h"

#include "World.h"

class PlayerEntity : public Entity
{
public:
	//Constructor
	PlayerEntity();

	//Inherited functions
	void Initialise();
	void Update(float deltatime);
	void CleanUp();

	//Logic functions
	void Movement();
private:
	World* m_world;
};