#ifndef __GAME_H__
#define __GAME_H__

#include "BackEnd.h"
#include "Projectile.h"
#include"Room.h"
#include"Start.h"


enum RoomName {
	STARTING,
	HALLWAY,
	STORAGE
};

//Our main class for running our game
class Game
{
public:
	//Empty constructor
	Game() { };
	//Deconstructor for game
	//*Unloads window
	~Game();

	//Initiaiizes game
	//*Seeds random
	//*Initializes SDL
	//*Creates Window
	//*Initializes GLEW
	//*Create Main Camera Entity
	//*Creates all other entities and adds them to register
	void InitGame();

	//Runs the game
	//*While window is open
	//*Clear window
	//*Update 
	//*Draw
	//*Poll events
	//*Flip window
	//*Accept input
	bool Run();
	
	//Updates the game
	//*Update timer
	//*Update the rendering system
	//*Update the animation system
	void Update();

	void DrawPause();

	//Runs the GUI
	//*Uses ImGUI for this
	void GUI();

	//Check events
	//*Checks the results of the events that have been polled
	void CheckEvents();

	/*Input Functions*/
	void AcceptInput();
	void GamepadInput();

	void GamepadStroke(XInputController* con);
	void GamepadUp(XInputController* con);
	void GamepadDown(XInputController* con);
	void GamepadStick(XInputController* con);
	void GamepadTrigger(XInputController* con);
	void KeyboardHold();
	void KeyboardDown();
	void KeyboardUp();

	//Mouse input
	void MouseMotion(SDL_MouseMotionEvent evnt);
	void MouseClick(SDL_MouseButtonEvent evnt);
	void MouseWheel(SDL_MouseWheelEvent evnt);

	//Contact listener

	void MagnetScan();

	//What happens at start of collision
	void BeginCollision(b2Fixture* fixtureA, b2Fixture* fixtureB);
	//What happens at end of collision
	void EndCollision(b2Fixture* fixtureA, b2Fixture* fixtureB);

	
	float RayCastCollision(b2Fixture* fixture, b2Vec2 point, float fraction);

	Scene* m_activeScene = nullptr;

private:

	bool inMenu = true;

	//Change room sccene
	void ChangeRoom(RoomName room, vec3 pos);
	void ChangeRoomUpdate();

	bool in_Menu = true;

	unsigned int m_pauseID = 0;

	//The window
	Window *m_window = nullptr;
	
	//The main register for our ECS
	entt::registry* m_register = nullptr;

	//Scenes
	
	std::vector<Scene*> m_scenes;
	
	//Imgui stuff
	bool m_guiActive = false;

	//Hooks for events
	bool m_close = false;
	bool m_motion = false;
	bool m_click = false;
	bool m_wheel = false;

	XInputManager input;

	//Player gravity scale
	float m_playerGravity = 7;
	
	//for pause
	bool m_isPaused = false;
	bool m_pause_drawn = false;

	//Scene
	bool m_changeScene = false;

	b2Vec2 m_playerPreviousPos;
	
};

#endif // !__GAME_H__

