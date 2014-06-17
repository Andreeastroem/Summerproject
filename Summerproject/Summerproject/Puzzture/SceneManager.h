//SceneManager.h

#pragma once

class Scene;
class InputManager;

class SceneManager
{
public:
	//Constructor and destructor
	SceneManager();
	~SceneManager();
	//Change the state
	void SetScene(const SceneName &SceneName);
	//Attach a Scene to the map
	void Attach(SceneName Name);
	//Detach a Scene from the map
	void Detach(SceneName Name);
	//Update the current state
	void Update(float deltatime);

	bool IsRunning();

	bool Initialise(DrawManager* draw_mgr, ConfigManager* config_mgr, sf::RenderWindow* window, InputManager* inputManager);

	void Cleanup();

private:
	//Manager pointers
	ConfigManager* m_ConfigManager;
	DrawManager* m_DrawManager;
	//RenderWindow pointer
	sf::RenderWindow* m_Window;

	//Scene containment
	std::map<SceneName, Scene*> m_states;
	//The current working state
	Scene* m_CurrentScene;

	//Inputs
	InputManager* m_InputManager;
};