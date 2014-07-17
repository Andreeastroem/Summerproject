//CollisionManager.h

#pragma once

class EntityManager;

class CollisionManager
{
public:
	//Constructors
	CollisionManager();

	//Essential functions
	bool Initialise(EntityManager* entitymanager);
	void CheckCollision();

	void CleanUp();

private:
	EntityManager* m_EntityManager;

	std::map<std::pair<EntityType, EntityType>, int> CollisionMap;
};