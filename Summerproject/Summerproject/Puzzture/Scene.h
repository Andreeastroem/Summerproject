//Scene.h

//Abstract base class for the different states

#pragma once

#include "World.h"

class Scene
{
public:
	virtual ~Scene();
	//initialise the state, create objects etc
	bool Initialise(World* world);
	//Enters the state in question
	virtual void Enter() = 0;
	//Leaves the state in question
	void Exit();
	//Updates the state and its components
	virtual void Update(float deltatime) = 0;

	//Clean up any pointers laying about
	virtual void Cleanup() = 0;

	//Access methods
	bool IsDone();
	SceneName NextScene();

protected:
	//Scene RGB and alpha values
	int m_iRed, m_iGreen, m_iBlue, m_iAlpha;

	//World
	World* m_world;

	//Lifetime variables
	bool m_bDone;

	//Setting new state
	SceneName m_NextScene;
};