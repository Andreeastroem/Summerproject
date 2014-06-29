//SceneManager.h

#pragma once

class World;
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

	bool Initialise(World* world);

	void Cleanup();

private:
	//World
	World* m_World;

	//Scene containment
	std::map<SceneName, Scene*> m_states;
	//The current working state
	Scene* m_CurrentScene;
};