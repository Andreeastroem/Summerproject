//EntityManager.h

#pragma once

class World;
class Entity;
class Tile;
class PlayerEntity;
class CollisionManager;

class EntityManager
{
public:
	//Constructors
	EntityManager();

	//Essential functions
	bool Initialise(World* world);

	void ClearEntities();
	void Cleanup();

	bool AttachEntity(EntityType entitytype);
	bool AttachTile(Tile* tile);
	
	void EraseFlaggedEntities();

	void Update(float deltatime);
	
	void SetDrawStatuses(sf::View* viewport);

	//Specified collision
	bool Intersect(sf::FloatRect box);

	//Access functions
	std::vector<Entity*> GetEntites();

	std::vector<Entity*> FindAllEntitiesByType(EntityType entitytype);

private:
	std::vector<Entity*> m_GameEntities;

	World* m_world;

	CollisionManager* m_CollisionManager;
};