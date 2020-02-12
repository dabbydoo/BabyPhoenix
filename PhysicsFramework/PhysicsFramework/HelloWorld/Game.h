#ifndef __GAME_H__
#define __GAME_H__

#include "BackEnd.h"
#include "HelloWorld.h"
#include "Xinput.h"
#include "AssignmentScene.h"
#include "time.h"
#include <cstdlib>

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

	//Check if main player grounded
	bool isPlayerOnGround();

	//Check if player collide with anything
	bool isPlayerOnCollision();

	void BeginCollision(b2Fixture* fixtureA, b2Fixture* fixtureB);

	void EndCollision(b2Fixture* fixtureA, b2Fixture* fixtureB);


	
private:
	//The window
	Window *m_window = nullptr;

	//Scene name
	std::string m_name;
	//Clear color for when we clear the window
	vec4 m_clearColor;
	
	//The main register for our ECS
	entt::registry* m_register;

	//Scenes
	Scene* m_activeScene;
	std::vector<Scene*> m_scenes;
	
	//Imgui stuff
	bool m_guiActive = false;

	//Hooks for events
	bool m_close = false;
	bool m_motion = false;
	bool m_click = false;
	bool m_wheel = false;

	//Dashing
	clock_t m_initDashTime; //Initial Player position when dash starts
	int m_dashCounter = 1; //Dash counter
	bool m_initDashOnGround = true; //Flag for if initial dash started on ground
	bool m_isDashing = false; //Flag for if currently dashing

	//Flag for if player on ground
	bool m_isPlayerOnGround = false;

	//Collision flags
	bool m_isPlayerOnCollision = false; //player collide
	bool m_isPlayerHeadCollide = false; //player head sensor collides
	bool m_isPlayerSideCollide = false; //player side sensor collides

	//Player gravity scale
	float m_playerGravity = 7;

	//Player body
	b2Body* m_playerBody;
};

#endif // !__GAME_H__
