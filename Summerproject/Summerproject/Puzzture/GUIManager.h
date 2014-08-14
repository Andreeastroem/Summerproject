//GUIManager.h

#pragma once

#include "World.h"

#include "GUIRect.h"

class GUIManager
{
public:
	//Constructors
	GUIManager();

	//Essential functions
	bool Initialise(World* world);

	void AttachButton(GUIElement element);

private:
	//World pointer
	World* m_World;

};