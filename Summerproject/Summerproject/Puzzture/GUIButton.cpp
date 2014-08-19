//GUIButton.cpp

#include "stdafx.h"

#include "GUIButton.h"

//Constructors

GUIButton::GUIButton()
{

}

//End of Constructors

//Inherited functions

bool GUIButton::Initialise(GUISettings settings)
{
	//Go through base class first
	GUIRect::Initialise(settings);

	//Add more
	m_Settings.clickAble = true;

	return true;
}

void GUIButton::Cleanup()
{
	//Go through base class first
	GUIRect::Cleanup();

	//Add more

}

void GUIButton::OnClick()
{
	switch (m_Settings.element)
	{
	case STARTBUTTON:
		m_bChangeScene = true;
		m_SceneName = PLAYSCENE;
		break;
	case EXITBUTTON:
		m_bExitGame = true;
	default:
	case FULLSCREENBUTTON:
		m_bFullscreen = !m_bFullscreen;
		break;
	}
}

void GUIButton::OnHover()
{
	GUIRect::OnHover();
}

void GUIButton::ExitHover()
{
	GUIRect::ExitHover();
}

//End of inherited functions

//Essential functions

//End of essential functions