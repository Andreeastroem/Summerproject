//ConfigManager.cpp

#include "stdafx.h"

#include <fstream>
#include <string>
#include "ConfigManager.h"

ConfigManager::ConfigManager()
{
}

ConfigManager::~ConfigManager()
{
}

bool ConfigManager::Initialise(const std::string directory)
{
	m_sdirectory = directory;
	if (m_sdirectory == "")
		return false;
	else
		return true;
}

//öppna filen och lagra värdena i en std::Map
bool ConfigManager::ReadFile(const std::string &FileName)
{
	//Stream that reads through the file
	std::ifstream stream;

	//Open the stream
	stream.open(m_sdirectory + FileName);

	//Validation if the stream was able to open the file
	if (!stream.is_open())
	{
		return false;
	}

	//A dynamic array to store all the lines in the file
	std::vector<std::string>FileLines;

	//Segment the files content into seperate lines
	if (stream.is_open())
	{
		while (!stream.eof())
		{
			std::string Line;
			std::getline(stream, Line, '\n');
			FileLines.push_back(Line);
		}
		//If there were no lines, then just skip
		if (FileLines.size() < 1)
		{
		}
		//Otherwise read through the lines one by one and look for "=" signs
		else
		{
			for (int i = 0; i < FileLines.size(); i++)
			{
				std::string Key;
				std::string Value;
				std::size_t WordLength = FileLines[i].find('=');
				//If there was a "=" sign on that line
				if (WordLength != std::string::npos)
				{
					//Key is the string from position 0 to the position of the "=" sign
					Key = FileLines[i].substr(0, WordLength);
					//Value is the string from the "=" sign and to the end of the line
					Value = FileLines[i].substr(WordLength + 1);

					//Insert the Key and the Value in the map
					FileValues.insert(std::pair<std::string, std::string>(Key, Value));
				}
			}
		}
	}

	//Close the stream
	stream.close();

	return true;
}

std::string ConfigManager::GetValueFromKey(std::string Key)
{
	//Find the key
	auto it = FileValues.find(Key);

	//If the iterator went through the array without finding the key
	if (it == FileValues.end())
	{
		//Return nothing
		return "";
	}
	//Otherwise return the Value linked with the key
	else
	{
		return it->second;
	}
}

int ConfigManager::ReadInt(std::string Key)
{
	//First get the value
	std::string TempValue = GetValueFromKey(Key);
	//return its int
	return std::stoi(TempValue);
}

float ConfigManager::ReadFloat(std::string Key)
{
	//First get the value
	std::string TempValue = GetValueFromKey(Key);
	//Return its float
	return std::stof(TempValue);
}