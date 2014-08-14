//Collider.h

#pragma once

class Collider
{
public:
	//Constructors
	Collider(sf::Vector2f position, sf::Vector2f extension);

	//Essential functions
	bool Overlap(Collider* other, sf::Vector2f &offsetA, sf::Vector2f &offsetB);
	bool SATOverlap(Collider* other, sf::Vector2f &offsetA, sf::Vector2f &offsetB);
	bool Overlap(sf::View* viewport);

	void Cleanup();

	void Update(float deltatime);

	//Access functions
	void SetPosition(sf::Vector2f position)
	{
		m_position = position;
		m_Hitbox.setPosition(m_position);
	}
	void SetExtension(sf::Vector2f extension)
	{
		m_extension = extension;
		m_Hitbox.setSize(m_extension);
	}

	sf::Vector2f getPosition()
	{
		return m_position;
	}
	sf::Vector2f getExtension()
	{
		return m_extension;
	}

	sf::RectangleShape getHitbox()
	{
		return m_Hitbox;
	}

	sf::Vector2f getVelocity()
	{
		return m_velocity;
	}

	sf::Vector2f getLastPosition()
	{
		return m_lastPosition;
	}

private:
	sf::Vector2f m_lastPosition;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	void Velocity(sf::Vector2f val) { m_velocity = val; }
	sf::Vector2f m_extension;

	sf::RectangleShape m_Hitbox;
};