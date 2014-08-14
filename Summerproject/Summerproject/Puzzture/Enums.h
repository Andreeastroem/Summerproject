//Enums.h

#pragma once

enum EntityType
{
	PLAYER,
	WALL,
	FLOOR,
	FURNITURE,
	CEILING,
	ENTITYTYPESIZE
};

enum EntityShape
{
	CIRCLE,
	BOX,
	OBJECTSHAPESIZE
};

enum SceneName
{
	PLAYSTATE,
	MENUSTATE,
	STATENAMESIZE
};

enum MouseButton
{
	MB_LEFT,
	MB_RIGHT,
	MOUSEBUTTONSIZE
};

/*
This order is only tested with Xbox 360 wired gamepad
*/
enum GamepadButton
{
	A,
	B,
	X,
	Y,
	LEFTSHOULDER,
	RIGHTSHOULDER,
	BACK,
	START,
	LEFTSTICK,
	RIGHTSTICK,
	GAMEPADBUTTONSIZE
};

/*
Player order with gamepads
*/
enum Player
{
	ONE,
	TWO,
	THREE,
	FOUR,
	PLAYERSIZE
};

class Enums
{

};