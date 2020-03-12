#pragma once
#include "Room.h"

class Projectile 
{
public:
	virtual void update() { };
private:

	//Projectile Entity ID
	int m_projectileID;

	//Projectile position
	b2Vec2 m_projectilePos;

	//Velocity
	float m_velocity;
};

class Gun
{
public:

private:
	int m_fireRate;
};