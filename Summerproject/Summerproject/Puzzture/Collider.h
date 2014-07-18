//Collider.h

#pragma once

class Collider
{
public:
	//Constructors
	Collider(sf::Vector2f position, sf::Vector2f extension);

	//Essential functions
	bool Overlap(Collider* other, sf::Vector2f &offset);
	void CleanUp();

	//Access functions
	void SetPosition(sf::Vector2f position)
	{
		m_position = position;
		m_Hitbox->setPosition(m_position);
	}
	void SetExtension(sf::Vector2f extension)
	{
		m_extension = extension;
		m_Hitbox->setSize(m_extension);
	}

	sf::Vector2f getPosition()
	{
		return m_position;
	}
	sf::Vector2f getExtension()
	{
		return m_extension;
	}

	sf::RectangleShape* getHitbox()
	{
		return m_Hitbox;
	}

private:
	sf::Vector2f m_position;
	sf::Vector2f m_extension;

	sf::RectangleShape* m_Hitbox;
};