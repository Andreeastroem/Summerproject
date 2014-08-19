//TileMap.h

#pragma once

#include "Tile.h"
#include "Entity.h"
#include "TextureManager.h"

class World;

class TileMap
{
public:
	//Constructor
	TileMap();

	//Essential functions
	bool Initialise(std::string folder, World* world);
	bool LoadMap(const std::string &FileName, int level);
	bool LoadEnvironment(int level);
	void Cleanup();
	void ClearLevel();

	//Access functions
	std::vector<Tile*> GetMap();
	Tile* GetTileAt(int index);
	Tile* GetTileAt(std::pair<int, int> at);

private:
	std::vector<Tile*> m_TileMap;
	std::vector<Tile*> m_Furnitures;

	std::string m_sFolder;
	World* m_World;

	//Reading map from file variables
	int m_tileWidth;
	int m_tileHeight;

	int m_LastXCoordinate;
	int m_LastYCoordinate;
};