//PlayScene.h

//The state where you play the actual game

#pragma once

#include "Scene.h"

class PlayScene : public Scene
{
public:
	~PlayScene(){};

	void Enter();

	void Update(float deltatime);

	void Cleanup();

private:
	
};