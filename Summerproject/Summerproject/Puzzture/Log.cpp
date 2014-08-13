//Log.cpp

#include "stdafx.h"

#include "Log.h"

//Print specified string
void Log::Message(std::string message)
{
	std::cout << message << std::endl;
}

//Print specified character
void Log::Message(char character)
{
	std::cout << character << std::endl;
}

//Print specified vector
void Log::Message(sf::Vector2f vector)
{
	printf("Vector(%0.2f, %0.2f) \n", vector.x, vector.y);
}

//Print specified float
void Log::Message(float f)
{
	printf("Float value: %0.2f \n");
}

//Print specified integer
void Log::Message(int i)
{
	printf("Integer value: %i \n", i);
}

//Print specified adress
void Log::Message(void *p)
{
	printf("Adress: %p \n", p);
}

//Print specified boolean
void Log::Message(bool state)
{
	switch (state)
	{
	case true:
		std::cout << "True" << std::endl;
		break;

	case false:
		std::cout << "False" << std::endl;
		break;
	}
}

//Print specified name with corresponding boolean value
void Log::Message(bool state, std::string name)
{
	std::cout << name << ": ";
	Message(state);
}