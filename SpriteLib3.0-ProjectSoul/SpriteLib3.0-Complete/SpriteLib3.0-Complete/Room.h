#pragma once
#include "Scene.h"
#include "BackEnd.h"
#include "Enum.h"
#include "Enemy.h"
//enum fixtureName { PLAYER = 1, FOOTSENSOR, HEADSENSOR, SIDESENSOR, GROUND, WALL, PLATFORM, MAGNET, DOORWAY, BULLET, BREAKABLE, ENEMY };
//
//
//enum Anim {
//	IDLE,
//	WALK = 2,
//	RUN = 4,
//	DASH = 6,
//	JUMP_BEGIN = 8,
//	JUMP_MIDDLE = 10,
//	JUMP_END = 12,
//	FALL = 14,
//	FLINCH = 16,
//	DEATH = 18,
//	SHOOT = 20,
//
//};

class Room : public Scene
{
public:
	Room(string name);

	void InitScene(float windowWidth, float windowHeight) override;
	

	void Update() override;

	bool CanShoot() override { return can_shoot; }
	 bool CanMagent()  override { return can_magent; }
	 bool CanDash()  override { return can_dash; }
	  void SetAction(bool dash = false, bool magnet = false, bool shoot = false) override;

	void SetRoom(Scene* room) override;
	void DashUpdate();


	//0 is m_playeronground , 1 is m_playerjumping , 2 is m_playerheadcolide, 3 is m_isPlayerOnWall, 4 is m_isPlayerOnCollision, 5 is m_isBroken, 6 is m_magnetCollision, 7 is m_isBulletHit, 8 is m_isPlayerSideCollide, 9 is m_moveToMagnet, 10 is m_isMagnetInRange

	 bool* Player_Status(unsigned int num)override
	 {
		 bool* player_status[11] = { &m_isPlayerOnGround ,  &m_isPlayerJumping , &m_isPlayerHeadCollide,  &m_isPlayerOnWall, &m_isPlayerOnCollision,  &m_isBroken, &m_magnetCollision, &m_isBulletHit, &m_isPlayerSideCollide, &m_moveToMagnet,&m_isMagnetInRange };

		 return player_status[num];
	 }
	 bool PlayerDirection() override { return m_character_direction; }
	 void SetBreakableUserData(unsigned int ID) override { m_breakableUserData = ID; }
	 void SetBulletHitUserData(unsigned int ID)  override { m_bulletHitUserData = ID; }
	 void SetClosestMagnetDistance(float dist) override { m_closestMagnetDistance = dist; }
	 float GetClosestMagnetDistance() override { return m_closestMagnetDistance; }

	 void SetClosestMagnet(b2Fixture* x) { m_closestMagnet = x; }
	 b2Fixture* GetClosestMagnet() override { return m_closestMagnet; }
	 bool GetIfMagentInRange()override { return m_isMagnetInRange; }

	 void SetIfMagentInRange(bool range)override { m_isMagnetInRange = range; }
	 void SetBody(b2Body* body)override { m_playerBody = body; }
	 b2Body* GetBody() override { return m_playerBody; };
	 void SetInitPlayerPos(vec3 pos) override { m_initPlayerPos = pos; }


	void ProjectileUpdate();
	void BreakableUpdate();

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

	//Enemy
	void SetEnemyBulletHit(bool isHit) override { m_isEnemyBulletHit = isHit; };
	void SetEnemyBulletHitUserData(unsigned int ID) override { m_enemyBulletHitUserData = ID; };
	void SetEnemyBeingHit(b2Body* enemyBody) override { m_enemyBeingHit = enemyBody; };

	//ACCESSSING THE IT IN THE GAME

	//the direction of the character 0/false is right || || 1/true is left
	//Flag for if player on ground

	

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

	void ShootBullet(float velocity);
	vec2 ConvertToGl(vec2 clickCoord);

 bool can_dash = false, can_magent = false, can_shoot = false;


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

 //the direction of the character 0/false is right || || 1/true is left
 bool m_character_direction = false;

 b2Vec2 m_initVelocity;

 //Player
 b2Body* m_playerBody;
 vec3 m_initPlayerPos = vec3(-43, -18, 50);

 //Magnet
 bool m_isMagnetInRange = false;
 float m_closestMagnetDistance;
 bool m_magnetCollision = false;
 bool m_moveToMagnet = false;
 b2Fixture* m_closestMagnet;

 //Bullet
 bool m_isBulletHit = false;
 unsigned int m_bulletHitUserData;

 //Breakable 
 bool m_isBroken = false;
 unsigned int m_breakableUserData;


 unsigned int m_background;
 float m_playerGravity = 7;

 //Enemy
 vector<Enemy> m_enemies;
 b2Body* m_enemyBeingHit;
 bool m_isEnemyBulletHit = false;
 unsigned int m_enemyBulletHitUserData;
 
bool m_firstTime = true;
};
