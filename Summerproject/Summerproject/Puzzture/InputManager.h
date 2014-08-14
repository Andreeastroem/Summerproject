//InputManager.h

#pragma once

//Keyboard related actions

class Keyboard
{
	friend class InputManager;
public:
	Keyboard();
	~Keyboard();

	bool KeyIsDoneOnce(int key) const;
	bool KeyIsDown(int key) const;

	void PostUpdate();

private:
	bool m_CurrentKeyboardButtons[256];
	bool m_PreviousKeyboardButtons[256];
};

//Mouse related actions

class Mouse
{
	friend class InputManager;
public:
	Mouse();
	~Mouse();

	void UpdatePosition(sf::Vector2f position);
	sf::Vector2f GetPosition();

	bool ButtonIsDownOnce(MouseButton button);
	bool ButtonIsDown(MouseButton button);

	void PostUpdate();
private:
	bool m_CurrentMouseButtons[MOUSEBUTTONSIZE];
	bool m_PreviousMouseButtons[MOUSEBUTTONSIZE];

	sf::Vector2f m_position;
};

//Gamepad related actions

/*
XY - Left stick
PovXY - Dpad
RU - rightstick
Z+ - left trigger
Z- - right trigger
*/
class Gamepad
{
	friend class InputManager;
public:
	Gamepad();
	~Gamepad();

	//Essential functions
	void PostUpdate();

	//Access methods
	float GetJoystickValue(int controller, int stick);
	bool ButtonIsDownOnce(int controller, int button);
	bool ButtonIsDown(int controller, int button);

private:
	bool m_CurrentGamepadButtons[4][10];
	bool m_PreviousGamepadButtons[4][10];

	std::vector<std::map<int, float>> m_Joysticks;
	 
	int m_JoysticksConnected = 0;
};

//InputManager
class InputManager
{
public:
	InputManager();

	bool ClosedWindow();

	bool Initialise();

	void Update(sf::Event::EventType* Eventtype, sf::Event &event);

	void PostUpdate();

	void Cleanup();

	Mouse* m_Mouse;
	Keyboard* m_Keyboard;
	Gamepad* m_Gamepad;

private:
	bool CloseWindow;
};