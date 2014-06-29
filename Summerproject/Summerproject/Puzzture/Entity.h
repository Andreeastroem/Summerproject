//Entity.h

#pragma once

class Entity
{
public:
	Entity();

	virtual void Initialise();

	virtual void Update(float deltatime) = 0;

	virtual void CleanUp();

private:
	sf::Vector2f m_Position;

	ObjectType m_ObjectType;

	//Visualisation
	sf::Sprite* m_sprite;
	sf::Shape* m_shape;
};