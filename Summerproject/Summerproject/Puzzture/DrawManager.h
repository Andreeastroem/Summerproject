//DrawManager.h

#pragma once

class DrawManager
{
public:
	DrawManager();

	void SetView(sf::RenderWindow* window, sf::View);

	void DrawShape(sf::RenderWindow* window, sf::Shape* Shape);
	void DrawSprite(sf::RenderWindow* window, sf::Sprite* Sprite);

	void ClearScreen(sf::RenderWindow* window, int Red, int Green, int Blue, int Alpha);

	void DisplayScreen(sf::RenderWindow* window);
private:

};