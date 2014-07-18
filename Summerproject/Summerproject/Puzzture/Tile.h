//Tile.h

#pragma once

#include "Entity.h"

class Tile : public Entity
{
public:
	Tile();
	~Tile();

	bool Initialise(EntityData entitydata);

	void Update(float deltatime);

	void OnCollision(Entity* entity, sf::Vector2f offset);

	void CleanUp();

	void SetTileMapPosition(int column, int row);
	std::pair<int, int> GetTileMapPosition();
	bool CompareTileMapPosition(std::pair<int, int> OtherPosition);

private:
	//Where is tile?
	std::pair<int, int> m_TileMapPosition;
};