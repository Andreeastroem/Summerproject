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

bool CollisionManager::Initialise()
{
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

void CollisionManager::CheckCollision(std::vector<Entity*> gameentities)
{
	//Go through all the entities and check collision
	if (gameentities.size() > 0)
	{
		for (int i = 0; i < (gameentities.size() - 1); i++)
		{
			for (int j = i + 1; j < gameentities.size(); j++)
			{
				//Are they on the same depth?
				if (gameentities[i]->GetEntityData().Depth ==
					gameentities[j]->GetEntityData().Depth)
				{
					//Check if it is a valid collision
					std::map<std::pair<EntityType, EntityType>, int>::iterator it =
						CollisionMap.find(std::pair<EntityType, EntityType>
						(gameentities[i]->GetEntityData().entitytype,
						gameentities[j]->GetEntityData().entitytype));

					//Valid collision
					if (it != CollisionMap.end())
					{
						//std::cout << "Entity1: " << m_EntityManager->GetEntites().at(i)->GetEntityData().entitytype << std::endl;
						//std::cout << "Entity2: " << m_EntityManager->GetEntites().at(j)->GetEntityData().entitytype << std::endl;

						sf::Vector2f offset;
						if (gameentities[i]->getCollider()->Overlap(gameentities[j]->getCollider(), offset))
						{
							//Collision
							gameentities[i]->OnCollision(gameentities[j], offset);
							gameentities[j]->OnCollision(gameentities[i], offset);
						}
					}
				}
			}
		}
	}
}

void CollisionManager::CleanUp()
{
}