//Tile.cpp

#include "stdafx.h"

#include "Tile.h"

Tile::Tile()
{

}

Tile::~Tile()
{
	if (m_Shape != nullptr)
	{
		delete m_Shape;
		m_Shape = nullptr;
	}

	if (m_Sprite != nullptr)
	{
		delete m_Sprite;
		m_Sprite = nullptr;
	}
}

//Inherited functions

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	
}

void Tile::Initialise(int xCord, int yCord, int width, int height, int depth, int movementcost)
{
	m_Tile.X_Coordinate = xCord;
	m_Tile.Y_Coordinate = yCord;

	m_Tile.Width = width;
	m_Tile.Height = height;

	m_Tile.Depth = depth;

	m_Tile.MovementCost = movementcost;

	m_Shape = new sf::RectangleShape();
	m_Shape->setSize(sf::Vector2f(width, height));

	m_Shape->setPosition(m_Tile.X_Coordinate, m_Tile.Y_Coordinate);
}

//Access functions

sf::Shape* Tile::GetShape()
{
	return m_Shape;
}

sf::Sprite* Tile::GetSprite()
{
	return m_Sprite;
}

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