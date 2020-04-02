#pragma once
#include "Box2D/Box2D.h"
#include "BackEnd.h"
#include "Enum.h"

class Enemy	
{
public:
	Enemy() {};
	void CreateBody(vec2 size, b2Vec2 position, b2World* physicsWorld, float speed = 10);

	//Update
	void Update();

	//Get entity ID
	unsigned int GetID() { return m_enemyID; };

	
	void SetViewDirection(Direction dir);
	
	//Positive distance is right, negative is left, and 0 distance means it doesn't move 
	void Patrol(float distance);
	//Kepps patrol within patrol zone based on m_patrolDistance
	void PatrolUpdate();

	b2Body* GetBody() { return m_body; };
	//Get current position
	b2Vec2 GetPosition() { return m_body->GetPosition(); };

	void Move(Direction dir);
	void StopMoving() { m_body->SetLinearVelocity(b2Vec2(0, 0)); };
	void EngagePlayer();
	void ShootBullet(Direction dir);
	void SetHealth(int health) { m_health = health; };
	int GetHealth() { return m_health; };
	void Delete();

	//Flag for dead enemy
	bool m_isDead = false;

private:
	//Scan for player in range to shoot. 
	bool checkPlayerInSight();

	// -1 = player found on left
	//  0 = no player found
	//  1 = player found on right
	int m_playerInSight = 0;

	b2World* m_physicsWorld;

	//Enemy body
	b2Body* m_body;

	//Initial position
	b2Vec2 m_initPos;

	//Enemy ID
	unsigned int m_enemyID;	

	//Enemy speed
	float m_speed;

	//The distance the enemy wants to maintain with the player
	float m_targetDistance = 15;

	//Bullets speed
	float m_bulletSpeed = 30;

	//Distance of patrol defaulted to zero
	float m_patrolDistance = 0; 

	//Direction enemy is facing
	Direction m_faceDir;

	//Enemy fireRate
	int m_bulletFireRate = 40;
	int m_bulletCounter = 0;

	//Enemy fire range
	float m_fireDistance = 30;

	//Health
	int m_health = 3;

	

};

class RayCastEnemyFOV : public b2RayCastCallback
{

public:
	RayCastEnemyFOV()
	{
		m_hit = false;
	}

	//Fixture call back
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
	{
		//b2Body* body = fixture->GetBody();
		fixture->GetUserData();
		void* userData = fixture->GetUserData();//body->GetUserData();

		//Ignore callbacks
		if ((int)userData == ENEMY || (int)userData == ENEMYBULLET || (int)userData == HEADSENSOR || (int)userData == SIDESENSOR || (int)userData == FOOTSENSOR)
		{
			return -1.f;
		}

		m_hit = true;
		m_point = point;
		m_normal = normal;
		m_userData = (int)userData;
		m_fraction = fraction;

		//By returning the current fraction, we instruct the calling code to clip the ray and
		// continue the ray-cast to the next fixture. WARNING: do not assume that fixtures
		// are reported in order. However, by clipping, we can always get the closest fixture.
		return fraction; //Return fraction of ray
	}

	bool m_hit; //Ray hit fixture
	b2Vec2 m_point; //Point of where ray hit fixture
	b2Vec2 m_normal; //Normal of where ray hit fixture
	int m_userData; //User data of fixture hit
	float m_fraction;
};