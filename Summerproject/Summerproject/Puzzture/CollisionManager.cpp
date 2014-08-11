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

void CollisionManager::CheckCollision(std::vector<Entity*> *gameentities)
{
	//Go through all the entities and check collision
	if (gameentities->size() > 0)
	{
		for (int i = 0; i < (gameentities->size() - 1); i++)
		{
			for (int j = i + 1; j < gameentities->size(); j++)
			{
				//Are they on the same depth?
				if (gameentities->at(i)->GetEntityData().Depth ==
					gameentities->at(j)->GetEntityData().Depth)
				{
					//Check if it is a valid collision
					std::map<std::pair<EntityType, EntityType>, int>::iterator it =
						CollisionMap.find(std::pair<EntityType, EntityType>
						(gameentities->at(i)->GetEntityData().entitytype,
						gameentities->at(j)->GetEntityData().entitytype));

					//Valid collision
					if (it != CollisionMap.end())
					{
						sf::Vector2f offsetSelf, offsetOther;
						if (gameentities->at(i)->getCollider()->Overlap(gameentities->at(j)->getCollider(), offsetSelf, offsetOther))
						{
							//Collision
							gameentities->at(i)->OnCollision(gameentities->at(j), offsetSelf);
							gameentities->at(j)->OnCollision(gameentities->at(i), offsetOther);
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