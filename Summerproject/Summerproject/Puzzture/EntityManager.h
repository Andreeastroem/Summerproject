//EntityManager.h

#pragma once

class World;
class Entity;

class EntityManager
{
public:
	EntityManager();


private:
	std::vector<Entity*> m_GameEntities;
};