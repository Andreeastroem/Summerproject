//ConfigManager.h

#pragma once

class ConfigManager
{
public:
	ConfigManager();
	~ConfigManager();

	//Initalise the ConfigManager with a directory path
	bool Initialise(const std::string directory);

	//Read through a file and store keys and values in a std::map
	bool ReadFile(const std::string &FileName);

	//Get the Value from the given key
	std::string GetValueFromKey(std::string Key);

	//Convert methods (optional)
	int ReadInt(std::string Key);
	float ReadFloat(std::string Key);
	sf::Vector2f ReadVector(std::string Key);

	//Levels
	bool LevelExists(int level);
	bool LoadLevel(const std::string &FileName, int level);
	std::vector<std::string> GetLevel(int level);

private:
	std::map<std::string, std::string> FileValues;

	std::map<int, std::vector<std::string>> m_Levels;

	std::string m_sdirectory;

	//
	std::string DeleteSpaces(std::string sentence);
};