//Tile.cpp

#include "stdafx.h"

#include "Tile.h"

Tile::Tile()
{

}

Tile::~Tile()
{
	
}

//Inherited functions


void Tile::Initialise(sf::Vector2f position, sf::IntRect size, int depth, int movementcost)
{
	m_EntityData.Position = position;

	m_EntityData.Size = size;

	m_EntityData.Depth = depth;

	m_EntityData.MovementCost = movementcost;

	m_Shape = new sf::RectangleShape();
	m_Shape->setSize(sf::Vector2f(size.width, size.height));

	m_Shape->setPosition(position);
}

void Tile::Update(float deltatime)
{

}

void Tile::CleanUp()
{
	//Clean up the visuals
	if (m_Sprite != nullptr)
	{
		delete m_Sprite;
		m_Sprite = nullptr;
	}
	if (m_Shape != nullptr)
	{
		delete m_Shape;
		m_Shape = nullptr;
	}
}

//Access functions
void Tile::SetTileMapPosition(int column, int row)
{
	m_TileMapPosition = std::pair<int, int>(column, row);
}

std::pair<int, int> Tile::GetTileMapPosition()
{
	return m_TileMapPosition;
}

bool Tile::CompareTileMapPosition(std::pair<int, int> OtherPosition)
{
	if (m_TileMapPosition == OtherPosition)
		return true;
	else
		return false;
}