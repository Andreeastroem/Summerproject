//MenuScene.h

//The state where you can show options etc

#pragma once

#include "Scene.h"
#include "GUIManager.h"

class MenuScene : public Scene
{
public:
	MenuScene();
	~MenuScene(){};

	bool Initialise(DrawManager* draw_mgr, sf::RenderWindow* window);

	void Enter();

	void Exit();

	void Update(float deltatime);
	
	void Cleanup();

private:
	GUIManager* m_GUIManager;
};