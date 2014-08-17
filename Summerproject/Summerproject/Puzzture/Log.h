//Log.h

#pragma once

#include <iostream>

namespace Log
{
	enum Colour
	{
		BLUE = 1,
		GREEN,
		CYAN,
		RED,
		PURPLE,
		DARKYELLOW,
		DEFAULT,
		GREY,
		BRIGHTBLUE,
		BRIGHTGREEN,
		BRIGHTCYAN,
		BRIGHTRED,
		PINK,
		YELLOW,
		BRIGHTWHITE
	};

	void Message(std::string message);
	void Message(char c);
	void Message(float f);
	void Message(sf::Vector2f vector);
	void Message(int i);
	void MessageAddress(void * p);
	void Message(bool state, std::string name);

	void Error(std::string message);

	void SetColour(int value);
};