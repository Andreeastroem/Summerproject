//MenuScene.h

//The state where you can show options etc

#pragma once

#include "Scene.h"

class MenuScene : public Scene
{
public:
	~MenuScene(){};

	bool Initialise(DrawManager* draw_mgr, sf::RenderWindow* window);

	void Enter();

	void Exit();

	void Update(float deltatime);
	
	void Cleanup();
};