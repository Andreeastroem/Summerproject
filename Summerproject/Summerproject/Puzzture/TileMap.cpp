//TileMap.cpp

#include "stdafx.h"

#include "World.h"

#include "TileMap.h"

//Constructors
TileMap::TileMap()
{

}

//Essential functions
bool TileMap::Initialise(std::string folder, World* world)
{
	//initalise world
	m_World = world;
	//validate variables existence
	if (m_World == nullptr)
		return false;

	m_sFolder = folder;

	//set the width and height of each tile
	m_World->GetConfigManager()->ReadFile(m_sFolder + "/" + "MapConfig.txt");
	m_tileWidth = m_World->GetConfigManager()->ReadInt("tilewidth");
	m_tileHeight = m_World->GetConfigManager()->ReadInt("tileheight");

	m_LastXCoordinate = 0;
	m_LastYCoordinate = 0;

	return true;
}

bool TileMap::LoadMap(const std::string &FileName, int level)
{
	/*
	* translating .txt file into tiled map
	*/
	
	//read the .txt file
	m_World->GetConfigManager()->LoadLevel(m_sFolder + "/" + FileName + ".txt", level);

	std::vector<std::string> map = m_World->GetConfigManager()->GetLevel(level);

	//for each line
	for (unsigned int i = 0; i < map.size(); i++)
	{
		//For each character in the line
		for (unsigned int j = 0; j < map[i].size(); j++)
		{
			Tile* newtile = new Tile;
			//Set the tiles coordinates and visual representation
			switch (map[i].at(j))
			{
			case 'a':
				newtile->Initialise(sf::Vector2f(m_LastXCoordinate, m_LastYCoordinate), sf::IntRect(0, 0, m_tileWidth, m_tileHeight), 0, 0);
				newtile->GetShape()->setFillColor(sf::Color::Blue);

				m_TileMap.push_back(newtile);
				m_TileMap[m_TileMap.size() - 1]->SetTileMapPosition(j, i);

				m_LastXCoordinate += m_tileWidth;

				//Add to the game entities
				m_World->GetEntityManager()->AttachTile(newtile);
				break;
			case 'b':
				newtile->Initialise(sf::Vector2f(m_LastXCoordinate, m_LastYCoordinate), sf::IntRect(0, 0, m_tileWidth, m_tileHeight), 0, 0);
				newtile->GetShape()->setFillColor(sf::Color::Cyan);

				m_TileMap.push_back(newtile);
				m_TileMap[m_TileMap.size() - 1]->SetTileMapPosition(j, i);

				m_LastXCoordinate += m_tileWidth;

				//Add to the game entities
				m_World->GetEntityManager()->AttachTile(newtile);
				break;
			case 'x':
				newtile->Initialise(sf::Vector2f(m_LastXCoordinate, m_LastYCoordinate), sf::IntRect(0, 0, m_tileWidth, m_tileHeight), 0, -1);
				newtile->GetShape()->setFillColor(sf::Color::Green);

				m_TileMap.push_back(newtile);
				m_TileMap[m_TileMap.size() - 1]->SetTileMapPosition(j, i);

				m_LastXCoordinate += m_tileWidth;

				//Add to the game entities
				m_World->GetEntityManager()->AttachTile(newtile);
				break;
			default:
				break;
			}
		}
		m_LastXCoordinate = 0;
		m_LastYCoordinate += m_tileHeight;
	}

	return true;
}

void TileMap::CleanUp()
{
	if (m_World != nullptr)
		m_World = nullptr;

	//clear the tilemap
	for (int i = 0; i < m_TileMap.size(); i++)
	{
		if (m_TileMap[i] != nullptr)
		{
			m_TileMap[i] = nullptr;
		}
	}
}

//Access functions
std::vector<Tile*> TileMap::GetMap()
{
	return m_TileMap;
}

Tile* TileMap::GetTileAt(int index)
{
	return m_TileMap[index];
}

Tile* TileMap::GetTileAt(std::pair<int, int> at)
{
	for (int i = 0; i < m_TileMap.size(); i++)
	{
		if (m_TileMap[i]->CompareTileMapPosition(at))
		{
			return m_TileMap[i];
		}
	}

	return nullptr;
}