//CollisionManager.h

#pragma once

class EntityManager;

class CollisionManager
{
public:
	//Constructors
	CollisionManager();

	//Essential functions
	bool Initialise();
	void CheckCollision(std::vector<Entity*> *gameentities);

	void Cleanup();

private:
	std::map<std::pair<EntityType, EntityType>, int> CollisionMap;
};