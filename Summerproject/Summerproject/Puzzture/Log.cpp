//Log.cpp

#include "stdafx.h"

#include "Log.h"

//Print specified string
void Log::Message(std::string message)
{
	printf("%s \n", message);
}

//Print specified character
void Log::Message(char character)
{
	printf("Character value: %c \n", character);
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