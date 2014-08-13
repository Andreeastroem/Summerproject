//TextureManager.cpp

#include "stdafx.h"

#include "TextureManager.h"

// Constructors

TextureManager::TextureManager()
{

}

//End of constructors

//Essential functions

bool TextureManager::Initialise(const std::string directory, const std::string fileformat)
{
	m_sDirectory = directory;
	m_sFileFormat = fileformat;

	return true;
}

bool TextureManager::LoadTexture(std::string filename)
{
	if (!TextureExists(filename))
	{
		std::string path = m_sDirectory + filename + "." + m_sFileFormat;
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile(path);

		//failsafe
		if (texture == nullptr)
		{
			Log::Error("There is no such image file. Note that fileformat is set to: " + m_sFileFormat);
			return false;
		}

		m_Textures.insert(std::pair<std::string, sf::Texture*>(filename, texture));
		return true;
	}
}

void TextureManager::Cleanup()
{
	std::map<std::string, sf::Texture*>::iterator it = m_Textures.begin();

	while (it != m_Textures.end())
	{
		delete it->second;
		it->second = nullptr;
		++it;
	}
}

//End of essential functions

//Access functions

sf::Texture* TextureManager::GetTexture(std::string texturename)
{
	//have we precached?
	if (TextureExists(texturename))
	{
		std::map<std::string, sf::Texture*>::iterator it = m_Textures.find(texturename);

		return it->second;
	}
	//maybe forgot to precache
	else if (LoadTexture(texturename))
	{
		std::map<std::string, sf::Texture*>::iterator it = m_Textures.find(texturename);

		return it->second;
	}
	//There is no such file
	else
	{
		Log::Error("No such file exists");
		return nullptr;
	}
}

//private functions

bool TextureManager::TextureExists(std::string texturename)
{
	std::map<std::string, sf::Texture*>::iterator it = m_Textures.find(texturename);

	if (it != m_Textures.end())
	{
		return true;
	}
	else
		return false;
}