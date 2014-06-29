//Tile.h

#pragma once

class Tile : public sf::Drawable, public sf::Transformable
{
	struct TileData
	{
		int X_Coordinate, Y_Coordinate;

		int Width, Height;

		//The depth in the game, 1 represents the front and -1 the back
		int Depth;

		//Movement penalties
		int MovementCost;
	};
public:
	Tile();
	~Tile();

	void Initialise(int xCord, int yCord, int width, int height, int depth, int movementcost);

	sf::Shape* GetShape();
	sf::Sprite* GetSprite();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void SetTileMapPosition(int column, int row);
	std::pair<int, int> GetTileMapPosition();
	bool CompareTileMapPosition(std::pair<int, int> OtherPosition);

private:
	//Size and position of the tile
	TileData m_Tile;

	//Visual representation of tile
	sf::RectangleShape* m_Shape;
	sf::Sprite* m_Sprite;

	//Where is tile?
	std::pair<int, int> m_TileMapPosition;
};