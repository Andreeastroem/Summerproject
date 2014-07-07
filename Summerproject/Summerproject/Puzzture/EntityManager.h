//EntityManager.h

#pragma once

class World;
class Entity;
class Tile;

class EntityManager
{
public:
	//Constructors
	EntityManager();

	//Essential functions
	bool Initialise();

	void CleanUp();

	bool AttachEntity(ObjectType objecttype);
	bool AttachTile(Tile* tile);
	
	void EraseFlaggedEntities();
	

	//Access functions
	std::vector<Entity*> GetEntites();

private:
	std::vector<Entity*> m_GameEntities;
};