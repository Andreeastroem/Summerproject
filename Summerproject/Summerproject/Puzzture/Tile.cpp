//Tile.cpp

#include "stdafx.h"

#include "Tile.h"

Tile::Tile(World* world)
{
	m_World = world;
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
	m_Shape->setSize(m_EntityData.size);

	m_Shape->setPosition(m_EntityData.position);

	m_Collider = new Collider(m_EntityData.position, m_EntityData.size);

	if (m_Shape == nullptr)
		return false;

	m_bGrounded = false;

	return true;
}

void Tile::Update(float deltatime)
{
	Entity::Update(deltatime);

	if (m_EntityData.entityType == FURNITURE)
	{
		if (!m_bGrounded)
		{
			m_EntityData.force.y += deltatime * 0.98f;
			
			m_EntityData.position += m_EntityData.force;

			UpdatePositions();

		}
		else
		{
			m_bGrounded = IsOnGround();
		}
	}
}

bool Tile::IsOnGround()
{
	sf::FloatRect feet;
	feet.top = m_Collider->getPosition().y + m_Collider->getExtension().y;
	feet.left = m_Collider->getPosition().x;
	feet.height = 1;
	feet.width = m_Collider->getExtension().x;

	if (m_World->Intersect(feet) != nullptr)
		return true;

	return false;
}

void Tile::OnCollision(Entity* entity, sf::Vector2f offset)
{
	switch (m_EntityData.entityType)
	{
	case FURNITURE:
		if (!m_bGrounded)
		{
			//If the offset is set to correct upwards, we have hit the ground
			if (offset.y < 0)
			{
				m_EntityData.position.y += offset.y;
				UpdatePositions();

				m_bGrounded = true;
				m_EntityData.force.y = 0;
			}
		}
		break;
	default:
		m_EntityData.position = m_v2fLastPosition;
		break;
	}
}

void Tile::Cleanup()
{
	Entity::Cleanup();

	if (m_World != nullptr)
		m_World = nullptr;
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