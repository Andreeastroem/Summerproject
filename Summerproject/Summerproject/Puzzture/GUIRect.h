//GUIRect.h

#pragma once


class GUIRect
{
public:

	struct GUISettings
	{
		GUIElement element;

		sf::Vector2f position;
		
		bool clickAble = false;

		bool highlighted = false;
	};

	//Constructors
	GUIRect();

	//Essential functions
	virtual bool Initialise(GUISettings settings);
	
	virtual void Cleanup();

	virtual bool Contains(sf::Vector2f point);

	virtual void OnClick();

	virtual void OnHover();

	virtual void ExitHover();

	//Access functions
	void SetText(std::string text)
	{
		m_Text.setString(text);
	}
	sf::Text GetText()
	{
		return m_Text;
	}

	void SetSpriteTexture(sf::Texture* texture)
	{
		m_Sprite->setTexture(*texture);
	}
	sf::Sprite* GetSprite()
	{
		return m_Sprite;
	}

	bool GetChangeScene()
	{
		return m_bChangeScene;
	}
	bool GetExitGame()
	{
		return m_bExitGame;
	}
	bool GetFullscreen()
	{
		return m_bFullscreen;
	}
	SceneName GetSceneName()
	{
		return m_SceneName;
	}

protected:
	sf::Text m_Text;
	sf::Sprite* m_Sprite;

	GUISettings m_Settings;

	//Changeable variables
	bool m_bChangeScene = false;;
	bool m_bExitGame = false;;
	bool m_bFullscreen = false;
	SceneName m_SceneName;
};