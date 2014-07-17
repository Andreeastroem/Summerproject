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


bool Tile::Initialise(EntityData entitydata)
{
	m_EntityData = entitydata;

	m_Shape = new sf::RectangleShape();
	m_Shape->setSize(sf::Vector2f(m_EntityData.Size.width, m_EntityData.Size.height));

	m_Shape->setPosition(m_EntityData.Position);

	if (m_Shape == nullptr)
		return false;

	return true;
}

void Tile::Update(float deltatime)
{

}

void Tile::OnCollision(Entity* entity)
{
	switch (entity->GetEntityData().entitytype)
	{
	default:
		m_EntityData.Position = m_v2fLastPosition;
		break;
	}
	
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