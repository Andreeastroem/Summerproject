//DrawManager.h

#pragma once

class DrawManager
{
public:
	DrawManager();

	void DrawShape(sf::RenderWindow* Window, sf::Shape* Shape);
	void DrawSprite(sf::RenderWindow* Window, sf::Sprite* Sprite);

	void ClearScreen(sf::RenderWindow* Window, int Red, int Green, int Blue, int Alpha);

	void DisplayScreen(sf::RenderWindow* Window);
private:

};