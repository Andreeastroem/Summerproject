//TextureManager.h

#pragma once

class TextureManager
{
public:
	TextureManager();

	//Clean up the textures
	void Cleanup();

	//Set the texture directory
	bool Initialise(const std::string directory, const std::string fileformat);

	//Load texture
	bool LoadTexture(std::string filename);

	//Access functions
	sf::Texture* GetTexture(std::string texturename);

private:
	bool TextureExists(std::string texturename);

	std::map<std::string, sf::Texture*> m_Textures;

	std::string m_sDirectory;
	std::string m_sFileFormat;
};