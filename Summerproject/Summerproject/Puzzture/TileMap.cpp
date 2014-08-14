//TileMap.cpp

#include "stdafx.h"

#include "World.h"

#include "TileMap.h"

//Constructors
TileMap::TileMap()
{

}

//Essential functions
bool TileMap::Initialise(std::string folder, World* world, TextureManager* textureManager)
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

	m_TextureManager = textureManager;

	m_TextureManager->LoadTexture("Ceiling");
	m_TextureManager->LoadTexture("Floor");
	m_TextureManager->LoadTexture("Wall");
	m_TextureManager->LoadTexture("Furniture");
	m_TextureManager->LoadTexture("Background");

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
			Tile* tile = new Tile;
			Entity::EntityData entitydata;

			//Set the tiles coordinates and visual representation
			switch (map[i].at(j))
			{
			case 'a':
				entitydata.Position = sf::Vector2f(m_LastXCoordinate, m_LastYCoordinate);
				entitydata.Size = sf::Vector2f(m_tileWidth, m_tileHeight);
				entitydata.Depth = 0;
				entitydata.MovementCost = 0;
				entitydata.entitytype = WALL;

				if (!tile->Initialise(entitydata))
					return false;
					
				tile->GetShape()->setFillColor(sf::Color::Blue);

				
				tile->SetSpriteTexture(m_World->GetTextureManager()->GetTexture("Wall"));


				m_TileMap.push_back(tile);
				m_TileMap[m_TileMap.size() - 1]->SetTileMapPosition(j, i);

				m_LastXCoordinate += m_tileWidth;

				//Add to the game entities
				m_World->GetEntityManager()->AttachTile(tile);
				break;
			case 'b':
				entitydata.Position = sf::Vector2f(m_LastXCoordinate, m_LastYCoordinate);
				entitydata.Size = sf::Vector2f(m_tileWidth, m_tileHeight);
				entitydata.Depth = 0;
				entitydata.MovementCost = 0;
				entitydata.entitytype = FLOOR;

				if (!tile->Initialise(entitydata))
					return false;

				tile->GetShape()->setFillColor(sf::Color::Cyan);

				tile->SetSpriteTexture(m_World->GetTextureManager()->GetTexture("Floor"));

				m_TileMap.push_back(tile);
				m_TileMap[m_TileMap.size() - 1]->SetTileMapPosition(j, i);

				m_LastXCoordinate += m_tileWidth;

				//Add to the game entities
				m_World->GetEntityManager()->AttachTile(tile);
				break;

			case 'c':
				entitydata.Position = sf::Vector2f(m_LastXCoordinate, m_LastYCoordinate);
				entitydata.Size = sf::Vector2f(m_tileWidth, m_tileHeight);
				entitydata.Depth = 0;
				entitydata.MovementCost = 0;
				entitydata.entitytype = CEILING;

				if (!tile->Initialise(entitydata))
					return false;

				tile->GetShape()->setFillColor(sf::Color(192, 192, 192, 255));

				tile->SetSpriteTexture(m_World->GetTextureManager()->GetTexture("Ceiling"));


				m_TileMap.push_back(tile);
				m_TileMap[m_TileMap.size() - 1]->SetTileMapPosition(j, i);

				m_LastXCoordinate += m_tileWidth;

				//Add to the game entities
				m_World->GetEntityManager()->AttachTile(tile);
				break;

			case 'f':
				entitydata.Position = sf::Vector2f(m_LastXCoordinate, m_LastYCoordinate);
				entitydata.Size = sf::Vector2f(m_tileWidth, m_tileHeight);
				entitydata.Depth = 0;
				entitydata.MovementCost = 0;
				entitydata.entitytype = FURNITURE;

				if (!tile->Initialise(entitydata))
					return false;

				tile->GetShape()->setFillColor(sf::Color(184, 134, 11, 255));

				tile->SetSpriteTexture(m_World->GetTextureManager()->GetTexture("Furniture"));


				m_TileMap.push_back(tile);
				m_TileMap[m_TileMap.size() - 1]->SetTileMapPosition(j, i);

				m_LastXCoordinate += m_tileWidth;

				//Add to the game entities
				m_World->GetEntityManager()->AttachTile(tile);
				break;

			case 'x':
				entitydata.Position = sf::Vector2f(m_LastXCoordinate, m_LastYCoordinate);
				entitydata.Size = sf::Vector2f(m_tileWidth, m_tileHeight);
				entitydata.Depth = -1;
				entitydata.MovementCost = 0;
				

				if (!tile->Initialise(entitydata))
					return false;

				tile->GetShape()->setFillColor(sf::Color::Green);

				tile->SetSpriteTexture(m_World->GetTextureManager()->GetTexture("Background"));

				m_TileMap.push_back(tile);
				m_TileMap[m_TileMap.size() - 1]->SetTileMapPosition(j, i);

				m_LastXCoordinate += m_tileWidth;

				//Add to the game entities
				m_World->GetEntityManager()->AttachTile(tile);
				break;
			default:
				break;
			}
		}
		m_LastXCoordinate = 0;
		m_LastYCoordinate += m_tileHeight;
	}

	return LoadEnvironment(level);
}

bool TileMap::LoadEnvironment(int level)
{
	ConfigManager* configmanager = m_World->GetConfigManager();

	configmanager->ReadFile(m_sFolder + "/" + "level" + std::to_string(level) + "objects.txt");

	int NumberOfObjects = configmanager->ReadInt("Amount");
	if (NumberOfObjects <= 0)
		return false;

	for (unsigned int i = 1; i <= NumberOfObjects; i++)
	{
		Tile* tile = new Tile;
		Entity::EntityData entitydata;

		entitydata.Size = configmanager->ReadVector(std::to_string(i) + "size");
		Log::Message(entitydata.Size);

		entitydata.Position = configmanager->ReadVector(std::to_string(i) + "pos");
		entitydata.Position = sf::Vector2f(entitydata.Position.x * entitydata.Size.x, entitydata.Position.y * entitydata.Size.y);
		Log::Message(entitydata.Position);

		entitydata.Depth = configmanager->ReadInt(std::to_string(i) + "depth");
		
		entitydata.entitytype = FURNITURE;
		entitydata.MovementCost = 0;

		if (!tile->Initialise(entitydata))
			return false;

		tile->GetShape()->setFillColor(sf::Color(184, 134, 11, 255));

		tile->GetSprite()->setTexture(*m_World->GetTextureManager()->GetTexture(configmanager->GetValueFromKey(std::to_string(i) + "texture")));

		m_TileMap.push_back(tile);

		//Add to the game entities
		m_World->GetEntityManager()->AttachTile(tile);
	}

	configmanager = nullptr;

	return true;
}

void TileMap::Cleanup()
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

	if (m_TextureManager != nullptr)
		m_TextureManager = nullptr;
}

void TileMap::ClearLevel()
{
	//Reset coordinates
	m_LastXCoordinate = 0;
	m_LastYCoordinate = 0;

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