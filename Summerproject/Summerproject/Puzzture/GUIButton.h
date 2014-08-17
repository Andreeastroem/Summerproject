//GUIButton.h

#pragma once

#include "GUIRect.h"

class GUIButton : public GUIRect
{
public:
	//Constructors
	GUIButton();

	//Inherited functions
	bool Initialise(GUISettings settings);
	void Cleanup();
	void OnClick();
	void OnHover();
	void ExitHover();

	//Essential functions

private:

};