//Tile.h

#pragma once

#include "Entity.h"
#include "World.h"

class Tile : public Entity
{
public:
	Tile(World* world);
	~Tile();

	bool Initialise(EntityData entitydata);

	void Update(float deltatime);

	void OnCollision(Entity* entity, sf::Vector2f offset);

	void Cleanup();

	void SetTileMapPosition(int column, int row);
	std::pair<int, int> GetTileMapPosition();
	bool CompareTileMapPosition(std::pair<int, int> OtherPosition);

private:
	//Where is tile?
	std::pair<int, int> m_TileMapPosition;

	//Use gravity?
	bool m_bGrounded;
	bool IsOnGround();

	//World pointer
	World* m_World;
};