//Log.h

#pragma once

#include <iostream>

namespace Log
{
	void Message(std::string message);
	void Message(char c);
	void Message(float f);
	void Message(sf::Vector2f vector);
	void Message(int i);
	void Message(void * p);
	void Message(bool state);
	void Message(bool state, std::string name);
};