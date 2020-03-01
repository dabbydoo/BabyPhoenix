#ifndef __GAME_H__
#define __GAME_H__

#include "BackEnd.h"
#include "Room.h"

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

	//Contact listener
	//What happens at start of collision
	void BeginCollision(b2Fixture* fixtureA, b2Fixture* fixtureB);
	//What happens at end of collision
	void EndCollision(b2Fixture* fixtureA, b2Fixture* fixtureB);
	//Ray collision
	float RayCastCollision(b2Fixture* fixture, b2Vec2 point, float fraction);

	void MagnetPull();
private:
	//The window
	Window *m_window = nullptr;
	
	//The main register for our ECS
	entt::registry* m_register = nullptr;

	//Scenes
	Scene* m_activeScene = nullptr;
	std::vector<Scene*> m_scenes;
	
	//Imgui stuff
	bool m_guiActive = false;

	//Hooks for events
	bool m_close = false;
	bool m_motion = false;
	bool m_click = false;
	bool m_wheel = false;

	XInputManager input;

	//Dashing
	clock_t m_initDashTime; //Initial Player position when dash starts
	int m_dashCounter = 1; //Dash counter

	bool m_initDashOnGround = true; //Flag for if initial dash started on ground
	bool m_initDashOnWall = false; //Flag for if initial dash started on the wall
	bool m_isDashing = false; //Flag for if currently dashing

	//Initial velocity
	b2Vec2 m_initVelocity;

	//Flag for if player on ground
	bool m_isPlayerOnGround = false;

	//Flag for if player on wall
	bool m_isPlayerOnWall = false;

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

