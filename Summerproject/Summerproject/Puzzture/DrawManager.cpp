//DrawManager.cpp

#include "stdafx.h"

#include "DrawManager.h"

DrawManager::DrawManager()
{
}

void DrawManager::SetView(sf::RenderWindow* window, sf::View view)
{
	window->setView(view);
}

void DrawManager::DrawShape(sf::RenderWindow* window, sf::Shape* Shape)
{
	window->draw(*Shape);
}

void DrawManager::DrawSprite(sf::RenderWindow* window, sf::Sprite* Sprite)
{
	window->draw(*Sprite);
}

void DrawManager::DrawText(sf::RenderWindow* window, sf::Text* text)
{
	window->draw(*text);
}

void DrawManager::ClearScreen(sf::RenderWindow* window, int Red, int Green, int Blue, int Alpha)
{
	window->clear(sf::Color(Red, Green, Blue, Alpha));
}

void DrawManager::DisplayScreen(sf::RenderWindow* window)
{
	window->display();
}