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
	void Initialise(sf::Vector2f position, sf::IntRect size, int depth, int movementcost);
	void Update(float deltatime);
	void CleanUp();

	//Logic functions
	void Movement();
private:
	World* m_world;
};