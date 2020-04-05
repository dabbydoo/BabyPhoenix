#pragma once
#include"Scene.h"
#include"BackEnd.h"
#include"Enum.h"

enum class Object {

ENEMY,
OBJECT,
HURT_OBJECT,
FLOOR,
BACKGROUND,

};

class InfoHolder {
	public:
		//Entity ID, Object type
		InfoHolder(unsigned int ID, Object obj) { entityID = ID; object = obj; }

		vec3 GetPos() { return ECS::GetComponent<Transform>(entityID).GetPosition(); }
		b2Body* GetBody(){ return ECS::GetComponent<PhysicsBody>(entityID).GetBody(); }

		void SetPos(vec3 pos) { ECS::GetComponent<Transform>(entityID).SetPosition(pos); }

private:
	Object object;
	unsigned int entityID;
};


class EndlessMode : public Scene {

public:


	EndlessMode(string name) :Scene(name) { ; }

	void InitScene(float windowWidth, float windowHeight) override;

	void GamepadStroke(XInputController* con) override;
	void GamepadUp(XInputController* con) override;
	void GamepadDown(XInputController* con) override;
	void GamepadStick(XInputController* con) override;
	void GamepadTrigger(XInputController* con) override;
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

	//0 is m_playeronground , 1 is m_playerjumping , 2 is m_playerheadcolide, 3 is m_isPlayerOnWall, 4 is m_isPlayerOnCollision, 5 is m_isBroken,
	//6 is m_magnetCollision, 7 is m_isBulletHit, 8 is m_isPlayerSideCollide, 9 is m_moveToMagnet, 10 is m_isMagnetInRange

	bool* Player_Status(unsigned int num)override
	{
		bool* player_status[11] = { &m_isPlayerOnGround ,  &m_isPlayerJumping , &m_isPlayerHeadCollide,  &m_isPlayerOnWall, &m_isPlayerOnCollision,  &m_isBroken, &m_magnetCollision, &m_isBulletHit, &m_isPlayerSideCollide, &m_moveToMagnet,&m_isMagnetInRange };

		return player_status[num];
	}

	void SetInitPlayerPos(vec3 pos) override { }

	void DrawHUD();

	void Update()override;

	void floorUpdate();
	void backgroudUpdate();
	void enemyUpdate();
	void objectUpdate();
	void bulletUpdate();

	void MouseMotion(SDL_MouseMotionEvent evnt) override;
	void MouseClick(SDL_MouseButtonEvent evnt) override;
	void MouseWheel(SDL_MouseWheelEvent evnt) override;


private:

	vector<InfoHolder*>Enemy;
	vector<InfoHolder*>Floor;
	vector<InfoHolder*>Background;
	vector<InfoHolder*>Obstacle;

	vector<InfoHolder*>infoHolder;

	unsigned healthEntity = 0, soulFillerEntity = 0, iconEntity = 0;

	int m_player_health = 4;

	const vec2 min = vec2(-178, -100);

	const vec2 max = vec2(178, 100);

	unsigned int mouse;

	bool m_isPlayerOnGround = true;
	bool m_isPlayerJumping = false;

	//Flag for if player on wall
	bool m_isPlayerOnWall = false;

	//Collision flags
	bool m_isPlayerOnCollision = false; //player collide
	bool m_isPlayerHeadCollide = false; //player head sensor collides
	bool m_isPlayerSideCollide = false; //player side sensor collides

	bool m_initDashOnGround = true; //Flag for if initial dash started on ground
	bool m_initDashOnWall = false; //Flag for if initial dash started on the wall
	bool m_isDashing = false; //Flag for if currently dashing

	//the direction of the character 0/false is right || || 1/true is left
	bool m_character_direction = false;
	//the direction of the character 0/false is right || || 1/true is left

	//Magnet
	bool m_isMagnetInRange = false;
	float m_closestMagnetDistance;
	bool m_magnetCollision = false;
	bool m_moveToMagnet = false;
	

	//Bullet
	bool m_isBulletHit = false;
	unsigned int m_bulletHitUserData;

	//Breakable 
	bool m_isBroken = false;
	unsigned int m_breakableUserData;

};