//DrawManager.cpp

#include "stdafx.h"

#include "DrawManager.h"

DrawManager::DrawManager()
{
}

void DrawManager::DrawShape(sf::RenderWindow* Window, sf::Shape* Shape)
{
	Window->draw(*Shape);
}

void DrawManager::DrawSprite(sf::RenderWindow* Window, sf::Sprite* Sprite)
{
	Window->draw(*Sprite);
}

void DrawManager::ClearScreen(sf::RenderWindow* Window, int Red, int Green, int Blue, int Alpha)
{
	Window->clear(sf::Color(Red, Green, Blue, Alpha));
}

void DrawManager::DisplayScreen(sf::RenderWindow* Window)
{
	Window->display();
}