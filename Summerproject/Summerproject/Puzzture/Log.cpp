//Log.cpp

#include "stdafx.h"

#include "Log.h"

#include <Windows.h>

//Print specified string
void Log::Message(std::string message)
{
	std::cout << message << std::endl;
}

//Print specified character
void Log::Message(char character)
{
	SetColour(Log::BRIGHTBLUE);
	std::cout << character << std::endl;
	SetColour(Log::DEFAULT);
}

//Print specified vector
void Log::Message(sf::Vector2f vector)
{
	SetColour(Log::BRIGHTCYAN);
	printf("Vector(%0.2f, %0.2f) \n", vector.x, vector.y);
	SetColour(Log::DEFAULT);
}

//Print specified float
void Log::Message(float f)
{
	SetColour(Log::GREEN);
	printf("Float value: %0.2f \n");
	SetColour(Log::DEFAULT);
}

//Print specified integer
void Log::Message(int i)
{
	SetColour(Log::GREEN);
	printf("Integer value: %i \n", i);
	SetColour(Log::DEFAULT);
}

//Print specified adress
void Log::Message(void *p)
{
	SetColour(Log::YELLOW);
	printf("Adress: %p \n", p);
	SetColour(Log::DEFAULT);
}

//Print specified boolean
void Log::Message(bool state)
{
	SetColour(Log::PINK);
	switch (state)
	{
	case true:
		std::cout << "True" << std::endl;
		break;

	case false:
		std::cout << "False" << std::endl;
		break;
	}
	SetColour(Log::DEFAULT);
}

//Print specified name with corresponding boolean value
void Log::Message(bool state, std::string name)
{
	SetColour(Log::PINK);
	std::cout << name << ": ";
	Message(state);
}

//Print error message
void Log::Error(std::string message)
{
	SetColour(Log::BRIGHTRED);
	Message(message);
	SetColour(Log::DEFAULT);
}



/*
Change the command prompt colour
1. Blue
2. Green
3. Cyan
4. Red
5. Purple
6. Dark yellow
7. Default white
8. Grey
9. Bright blue
10. Bright green
11. Bright cyan
12. Bright red
13. Pink/Magenta
14. Yellow
15. Bright white
*/
void Log::SetColour(int value)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}