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
	};


	Entity();

	virtual void Initialise(sf::Vector2f position, sf::IntRect size, int depth, int movementcost);

	virtual void Update(float deltatime) = 0;

	virtual void CleanUp();

	//Access functions
	sf::Shape* GetShape();
	sf::Sprite* GetSprite();

	bool IsFlagged();
	void SetFlagged(bool state);

protected:
	//Size and position of the entity
	EntityData m_EntityData;

	ObjectType m_ObjectType;

	//Visualisation
	sf::Sprite* m_Sprite;
	sf::RectangleShape* m_Shape;

	//Is entity alive or dead?
	bool m_bFlagged;
};