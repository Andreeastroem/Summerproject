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
	CollisionMap.insert(std::pair<std::pair<EntityType, EntityType>, int>(std::pair<EntityType, EntityType>(PLAYER, CEILING), 0));

	//and also in the reversed order
	CollisionMap.insert(std::pair<std::pair<EntityType, EntityType>, int>(std::pair<EntityType, EntityType>(WALL, PLAYER), 0));
	CollisionMap.insert(std::pair<std::pair<EntityType, EntityType>, int>(std::pair<EntityType, EntityType>(FLOOR, PLAYER), 0));
	CollisionMap.insert(std::pair<std::pair<EntityType, EntityType>, int>(std::pair<EntityType, EntityType>(FURNITURE, PLAYER), 0));
	CollisionMap.insert(std::pair<std::pair<EntityType, EntityType>, int>(std::pair<EntityType, EntityType>(CEILING, PLAYER), 0));

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
				if (gameentities->at(i)->GetEntityData().depth ==
					gameentities->at(j)->GetEntityData().depth)
				{

					//Check if it is a valid collision
					std::map<std::pair<EntityType, EntityType>, int>::iterator it =
						CollisionMap.find(std::pair<EntityType, EntityType>
						(gameentities->at(i)->GetEntityData().entityType,
						gameentities->at(j)->GetEntityData().entityType));

					//Valid collision
					if (it != CollisionMap.end())
					{

						sf::Vector2f offsetA, offsetB;
						if (gameentities->at(i)->getCollider()->SATOverlap(gameentities->at(j)->getCollider(), offsetA, offsetB))
						{
							//Collision
							gameentities->at(i)->OnCollision(gameentities->at(j), offsetA);
							gameentities->at(j)->OnCollision(gameentities->at(i), offsetB);
						}
					}
				}

			}
		}
	}
}

bool CollisionManager::Intersect(sf::FloatRect box, std::vector<Entity*>* gameentities)
{
	for (int i = 0; i < gameentities->size(); i++)
	{
		if (gameentities->at(i)->GetDrawStatus())
		{
			if (gameentities->at(i)->GetEntityData().depth == 0)
			{
				if (box.intersects(gameentities->at(i)->GetSprite()->getGlobalBounds()))
					return true;
			}
		}
	}

	return false;
}

void CollisionManager::Cleanup()
{
}