//Tile.h

#pragma once

#include "Entity.h"

class Tile : public Entity
{
public:
	Tile();
	~Tile();

	void Initialise(sf::Vector2f position, sf::IntRect size, int depth, int movementcost);

	void Update(float deltatime);

	void CleanUp();

	void SetTileMapPosition(int column, int row);
	std::pair<int, int> GetTileMapPosition();
	bool CompareTileMapPosition(std::pair<int, int> OtherPosition);

private:
	//Where is tile?
	std::pair<int, int> m_TileMapPosition;
};