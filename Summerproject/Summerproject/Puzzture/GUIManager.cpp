//GUIManager.cpp

#include "stdafx.h"

#include "GUIManager.h"

//Constructors

GUIManager::GUIManager()
{

}

//End of constructors

//Essential functions

bool GUIManager::Initialise(World* world)
{
	//Early out
	if (world == nullptr)
		return false;

	m_World = world;
}

//End of essential functions