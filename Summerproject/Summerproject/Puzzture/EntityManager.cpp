//EntityManager.cpp

#include "stdafx.h"

#include "World.h"
#include "Entity.h"
#include "Tile.h"

#include "EntityManager.h"

//Constructors
EntityManager::EntityManager()
{

}

//Essential functions
bool EntityManager::Initialise()
{
	return true;
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
}

bool EntityManager::AttachEntity(ObjectType objecttype)
{
	switch (objecttype)
	{

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

//Access functions

std::vector<Entity*> EntityManager::GetEntites()
{
	return m_GameEntities;
}