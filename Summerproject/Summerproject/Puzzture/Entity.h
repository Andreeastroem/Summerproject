//Entity.h

#pragma once

class Entity
{
public:
	struct EntityData
	{
		sf::Vector2f Position;

		sf::IntRect Size;

		//The depth in the game, 1 represents the front and -1 the back
		int Depth;

		//Movement penalties
		int MovementCost;

		EntityType entitytype;
	};


	Entity();

	virtual bool Initialise(EntityData entitydata);

	virtual void Update(float deltatime) = 0;

	virtual void OnCollision(Entity* entity);

	virtual void CleanUp();

	//Access functions
	sf::Shape* GetShape()
	{
		return m_Shape;
	}

	sf::Sprite* GetSprite()
	{
		return m_Sprite;
	}

	EntityData GetEntityData()
	{
		return m_EntityData;
	}

	bool IsFlagged()
	{
		return m_bFlagged;
	}

	void SetFlagged(bool state)
	{
		m_bFlagged = state;
	}

protected:
	//Size and position of the entity
	EntityData m_EntityData;
	sf::Vector2f m_v2fLastPosition;

	//Visualisation
	sf::Sprite* m_Sprite;
	sf::RectangleShape* m_Shape;

	//Is entity alive or dead?
	bool m_bFlagged;
};