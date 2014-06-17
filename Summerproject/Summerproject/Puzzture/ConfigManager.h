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

private:
	std::map<std::string, std::string> FileValues;
	std::string m_sdirectory;
};