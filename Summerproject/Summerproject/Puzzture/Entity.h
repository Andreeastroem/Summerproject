//Entity.h

#pragma once

#include "Collider.h"

class Entity
{
public:
	struct EntityData
	{
		sf::Vector2f position;

		sf::Vector2f size;

		sf::Vector2f force = sf::Vector2f();

		//The depth in the game, 1 represents the front and -1 the back
		int depth;

		//Movement penalties
		int movementCost;

		EntityType entityType;
	};


	Entity();

	virtual bool Initialise(EntityData entitydata);

	virtual void Update(float deltatime) = 0;

	virtual void OnCollision(Entity* entity, sf::Vector2f offset);

	virtual void Cleanup();

	//Access functions
	void SetPosition(sf::Vector2f position)
	{
		m_EntityData.position = position;
		UpdatePositions();
	}

	sf::Shape* GetShape()
	{
		return m_Shape;
	}

	sf::Sprite* GetSprite()
	{
		return m_Sprite;
	}

	void SetSpriteTexture(sf::Texture* texture)
	{
		m_Sprite->setTexture(*texture);
	}
	
	void SetSpriteTextureRect(sf::IntRect textRect)
	{
		m_Sprite->setTextureRect(textRect);
	}

	EntityData GetEntityData()
	{
		return m_EntityData;
	}

	Collider* getCollider()
	{
		return m_Collider;
	}
	void SetCollider(Collider* collider)
	{
		m_Collider = collider;
	}

	bool IsFlagged()
	{
		return m_bFlagged;
	}

	void SetFlagged(bool state)
	{
		m_bFlagged = state;
	}

	bool GetDrawStatus()
	{
		return m_bDrawStatus;
	}

	void SetDrawStatus(bool state)
	{
		m_bDrawStatus = state;
	}

	void UpdatePositions()
	{
		m_Shape->setPosition(m_EntityData.position);
		m_Sprite->setPosition(m_EntityData.position);
		m_Collider->SetPosition(m_EntityData.position);
	}

protected:
	//Size and position of the entity
	EntityData m_EntityData;
	sf::Vector2f m_v2fLastPosition;

	//Visualisation
	sf::Sprite* m_Sprite;
	sf::RectangleShape* m_Shape;

	//Collision
	Collider* m_Collider;

	//Is entity alive or dead?
	bool m_bFlagged;

	//Draw status
	//Is entity set to be drawn
	bool m_bDrawStatus;
};