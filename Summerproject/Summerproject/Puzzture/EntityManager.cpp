//EntityManager.cpp

#include "stdafx.h"

#include "World.h"
#include "Entity.h"
#include "Tile.h"
#include "PlayerEntity.h"
#include "CollisionManager.h"

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

void EntityManager::CleanUp()
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
		m_CollisionManager->CleanUp();
		delete m_CollisionManager;
		m_CollisionManager = nullptr;
	}

	if (m_world != nullptr)
	{
		m_world = nullptr;
	}
}

bool EntityManager::AttachEntity(EntityType entitytype)
{
	switch (entitytype)
	{
	case PLAYER:
		PlayerEntity* playerentity = new PlayerEntity(m_world);

		Entity::EntityData entitydata;

		entitydata.Position = sf::Vector2f(130, 100);
		entitydata.entitytype = entitytype;
		entitydata.MovementCost = 0;
		entitydata.Depth = 0;
		entitydata.Size = sf::Vector2f(64, 128);

		if (!playerentity->Initialise(entitydata))
			return false;

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
				m_GameEntities[i]->CleanUp();
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
	for (int i = 0; i < m_GameEntities.size(); i++)
	{
		m_GameEntities[i]->Update(deltatime);
	}

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

//Access functions

std::vector<Entity*> EntityManager::GetEntites()
{
	return m_GameEntities;
}

std::vector<Entity*> EntityManager::FindAllEntitiesByType(EntityType entitytype)
{
	std::vector<Entity*> AllEntitiesByType;

	for (int i = 0; i < m_GameEntities.size(); i++)
	{
		if (m_GameEntities[i]->GetEntityData().entitytype == entitytype)
			AllEntitiesByType.push_back(m_GameEntities[i]);
	}

	return AllEntitiesByType;
}