//CollisionManager.cpp

#include "stdafx.h"

#include "Entity.h"
#include "EntityManager.h"

#include "CollisionManager.h"

//Constructors

CollisionManager::CollisionManager()
{

}

//Essential functions

bool CollisionManager::Initialise(EntityManager* entitymanager)
{
	if (entitymanager == nullptr)
		return false;
	m_EntityManager = entitymanager;
	

	//Initialise what can collide with what
	CollisionMap.insert(std::pair<std::pair<EntityType, EntityType>, int>(std::pair<EntityType, EntityType>(PLAYER, WALL), 0));
	CollisionMap.insert(std::pair<std::pair<EntityType, EntityType>, int>(std::pair<EntityType, EntityType>(PLAYER, FLOOR), 0));
	CollisionMap.insert(std::pair<std::pair<EntityType, EntityType>, int>(std::pair<EntityType, EntityType>(PLAYER, FURNITURE), 0));

	//and also in the reversed order
	CollisionMap.insert(std::pair<std::pair<EntityType, EntityType>, int>(std::pair<EntityType, EntityType>(WALL, PLAYER), 0));
	CollisionMap.insert(std::pair<std::pair<EntityType, EntityType>, int>(std::pair<EntityType, EntityType>(FLOOR, PLAYER), 0));
	CollisionMap.insert(std::pair<std::pair<EntityType, EntityType>, int>(std::pair<EntityType, EntityType>(FURNITURE, PLAYER), 0));

	//Same entities
	CollisionMap.insert(std::pair<std::pair<EntityType, EntityType>, int>(std::pair<EntityType, EntityType>(FURNITURE, FURNITURE), 0));

	return true;
}

void CollisionManager::CheckCollision()
{
	//Go through all the entities and check collision
	if (m_EntityManager->GetEntites().size() > 0)
	{
		for (int i = 0; i < (m_EntityManager->GetEntites().size() - 1); i++)
		{
			for (int j = i + 1; j < m_EntityManager->GetEntites().size(); j++)
			{
				//Are they on the same depth?
				if (m_EntityManager->GetEntites().at(i)->GetEntityData().Depth ==
					m_EntityManager->GetEntites().at(j)->GetEntityData().Depth)
				{
					//Check if it is a valid collision
					std::map<std::pair<EntityType, EntityType>, int>::iterator it =
						CollisionMap.find(std::pair<EntityType, EntityType>
						(m_EntityManager->GetEntites().at(i)->GetEntityData().entitytype,
						m_EntityManager->GetEntites().at(j)->GetEntityData().entitytype));

					//Valid collision
					if (it != CollisionMap.end())
					{
						//std::cout << "Entity1: " << m_EntityManager->GetEntites().at(i)->GetEntityData().entitytype << std::endl;
						//std::cout << "Entity2: " << m_EntityManager->GetEntites().at(j)->GetEntityData().entitytype << std::endl;

						sf::Vector2f offset;
						if (m_EntityManager->GetEntites().at(i)->getCollider()->Overlap(m_EntityManager->GetEntites().at(j)->getCollider(), offset))
						{
							//Collision
							m_EntityManager->GetEntites().at(i)->OnCollision(m_EntityManager->GetEntites().at(j), offset);
							m_EntityManager->GetEntites().at(j)->OnCollision(m_EntityManager->GetEntites().at(i), offset);
						}
					}
				}
			}
		}
	}
}

void CollisionManager::CleanUp()
{
	if (m_EntityManager != nullptr)
		m_EntityManager = nullptr;
}