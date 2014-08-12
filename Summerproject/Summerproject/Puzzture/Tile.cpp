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
	Entity::Initialise(entitydata);

	m_EntityData = entitydata;

	m_Shape = new sf::RectangleShape();
	m_Shape->setSize(m_EntityData.Size);

	m_Shape->setPosition(m_EntityData.Position);

	m_Collider = new Collider(m_EntityData.Position, m_EntityData.Size);

	if (m_Shape == nullptr)
		return false;

	return true;
}

void Tile::Update(float deltatime)
{
	Entity::Update(deltatime);
}

void Tile::OnCollision(Entity* entity, sf::Vector2f offset)
{
	switch (entity->GetEntityData().entitytype)
	{
	default:
		m_EntityData.Position = m_v2fLastPosition;
		break;
	}
	
}

void Tile::Cleanup()
{
	Entity::Cleanup();
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