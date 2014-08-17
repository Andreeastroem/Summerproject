//EntityManager.cpp

#include "stdafx.h"

#include "World.h"
#include "Entity.h"
#include "Tile.h"
#include "PlayerEntity.h"
#include "CollisionManager.h"
#include "TextureManager.h"

#include "EntityManager.h"

//Constructors
EntityManager::EntityManager()
{

}

//Essential functions
bool EntityManager::Initialise(World* world)
{
	m_CollisionManager = new CollisionManager;
	if (!m_CollisionManager->Initialise())
		return false;

	m_world = world;
	if (m_world == nullptr)
		return false;

	m_world->GetTextureManager()->LoadTexture("mc");

	return true;
}

void EntityManager::ClearEntities()
{
	//Clearing and deleting all pointers to game objects
	for (unsigned int i = 0; i < m_GameEntities.size(); i++)
	{
		if (m_GameEntities[i] != nullptr)
		{
			delete m_GameEntities[i];
			m_GameEntities[i] = nullptr;
		}
	}

	m_GameEntities.clear();
}

void EntityManager::Cleanup()
{
	//Clearing and deleting all pointers to game objects
	for (unsigned int i = 0; i < m_GameEntities.size(); i++)
	{
		if (m_GameEntities[i] != nullptr)
		{
			delete m_GameEntities[i];
			m_GameEntities[i] = nullptr;
		}
	}

	m_GameEntities.clear();

	//Managers
	if (m_CollisionManager != nullptr)
	{
		m_CollisionManager->Cleanup();
		delete m_CollisionManager;
		m_CollisionManager = nullptr;
	}

	if (m_world != nullptr)
	{
		m_world = nullptr;
	}
}

bool EntityManager::AttachEntity(EntityType entityType)
{
	sf::Vector2f pos = sf::Vector2f(2, 4);
	sf::Vector2f ext = sf::Vector2f(-4, -6);

	switch (entityType)
	{
	case PLAYER:
		PlayerEntity* playerentity = new PlayerEntity(m_world, pos, ext);

		Entity::EntityData entitydata;

		entitydata.position = sf::Vector2f(130, 164);
		entitydata.entityType = entityType;
		entitydata.movementCost = 0;
		entitydata.depth = 0;
		entitydata.size = sf::Vector2f(20, 64);

		if (!playerentity->Initialise(entitydata))
			return false;

		playerentity->GetShape()->setFillColor(sf::Color(255, 255, 0, 255));

		playerentity->SetSpriteTexture(m_world->GetTextureManager()->GetTexture("mc"));

		m_GameEntities.push_back(playerentity);

		break;
	}

	return true;
}

bool EntityManager::AttachTile(Tile* tile)
{
	m_GameEntities.push_back(tile);

	return true;
}

void EntityManager::EraseFlaggedEntities()
{
	//look through all the entities
	for (unsigned int i = 0; i < m_GameEntities.size(); i++)
	{
		//If the given entity is flagged
		if (m_GameEntities[i]->IsFlagged())
		{
			//erase it
			if (m_GameEntities[i] != nullptr)
			{
				m_GameEntities[i]->Cleanup();
				delete m_GameEntities[i];
				m_GameEntities[i] = nullptr;
			}

			m_GameEntities.erase(m_GameEntities.begin() + i);
		}
	}
}

void EntityManager::Update(float deltatime)
{
	//Update every entity
	for (unsigned int i = 0; i < m_GameEntities.size(); i++)
	{
		m_GameEntities[i]->Update(deltatime);
	}

	EraseFlaggedEntities();

	//Check collision between entities
	m_CollisionManager->CheckCollision(&m_GameEntities);

	//Erase destroyed objects
	EraseFlaggedEntities();
}

void EntityManager::UpdateDrawStatues(sf::View* viewport)
{
	for (int i = 0; i < m_GameEntities.size(); i++)
	{
		m_GameEntities[i]->SetDrawStatus(m_GameEntities[i]->getCollider()->Overlap(viewport));
	}
}

void EntityManager::SetDrawStatuses(sf::View* viewport)
{
	for (int i = 0; i < m_GameEntities.size(); i++)
	{
		m_GameEntities[i]->SetDrawStatus(m_GameEntities[i]->getCollider()->Overlap(viewport));
	}
}

Entity* EntityManager::Intersect(sf::FloatRect box)
{
	return m_CollisionManager->Intersect(box, &m_GameEntities);
}

//Access functions

std::vector<Entity*> EntityManager::GetEntites()
{
	return m_GameEntities;
}

std::vector<Entity*> EntityManager::FindAllEntitiesByType(EntityType entityType)
{
	std::vector<Entity*> AllEntitiesByType;

	for (int i = 0; i < m_GameEntities.size(); i++)
	{
		if (m_GameEntities[i]->GetEntityData().entityType == entityType)
			AllEntitiesByType.push_back(m_GameEntities[i]);
	}

	return AllEntitiesByType;
}