#pragma once
#include "Scene.h"
#include <iostream>
#include"Game.h"

using namespace std;

//fixture name
enum fixtureName { PLAYER = 1, FOOTSENSOR, HEADSENSOR, SIDESENSOR, GROUND, WALL, PLATFORM, MAGNET, DOORWAY, BULLET, BREAKABLE};

enum Anim {
	IDLE,
	WALK = 2,
	RUN = 4,
	DASH = 6,
	JUMP_BEGIN = 8,
	JUMP_MIDDLE = 10,
	JUMP_END = 12,
	FALL = 14,
	FLINCH = 16,
	DEATH = 18,
	SHOOT = 20,

};

class Room : public Scene
{
public:
	Room(string name);

	void InitScene(float windowWidth, float windowHeight) override;
	
	void Update(Game* game) override;

	

	void setRoom(const Room room);

	void GamepadStroke(XInputController* con) override;
	void GamepadUp(XInputController* con) override;
	void GamepadDown(XInputController* con) override;
	void GamepadStick(XInputController* con) override;
	void GamepadTrigger(XInputController* con) override;
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

	void MouseMotion(SDL_MouseMotionEvent evnt) override;
	void MouseClick(SDL_MouseButtonEvent evnt) override;
	void MouseWheel(SDL_MouseWheelEvent evnt) override;

	bool can_dash = false, can_magent = false, can_shoot = false;

private:
	void CreateCamera(float windowWidth, float windowHeight);
	void CreateBackground(string fileName, vec2 size);
	void CreateRoomBoundary();
	void CreateMainPlayer(int width, int height, vec3 position);
	void CreatePlatform(string fileName, vec2 size, vec2 position);
	void CreateMagnet(vec2 size, vec2 position);
	void CreateEdge(b2Vec2 point1, b2Vec2 point2, fixtureName fixtureName, bool sensor = false);
	void CreateDestructable(string fileName, vec2 size, vec2 position);
	void CreateDoorWay(b2Vec2 position);

	//the direction of the character 0/false is right || || 1/true is left
	//Flag for if player on ground
	bool m_isPlayerOnGround = true;

	bool m_isPlayerJumping = false;

	//Flag for if player on wall
	bool m_isPlayerOnWall = false;

	//Collision flags
	bool m_isPlayerOnCollision = false; //player collide
	bool m_isPlayerHeadCollide = false; //player head sensor collides
	bool m_isPlayerSideCollide = false; //player side sensor collides

	clock_t m_initDashTime; //Initial Player position when dash starts
	int m_dashCounter = 1; //Dash counter

	bool m_initDashOnGround = true; //Flag for if initial dash started on ground
	bool m_initDashOnWall = false; //Flag for if initial dash started on the wall
	bool m_isDashing = false; //Flag for if currently dashing

	bool m_character_direction = false;

	b2Vec2 m_initVelocity;

	b2Body* m_playerBody;

	vector<Enemy> enemies;
	unsigned int m_background;

};
