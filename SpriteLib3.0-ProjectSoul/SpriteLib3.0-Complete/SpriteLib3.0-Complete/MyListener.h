#pragma once
#include "Game.h"
#include <iostream>

//Pointer for the game
Game* m_theGame;

class MyContactListener : public b2ContactListener
{
	
public:

	//Set reference to game object
	void SetGame(Game* _game)
	{
		m_theGame = _game;
	}

	//BeginContact listener
	void BeginContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();
		m_theGame->BeginCollision(fixtureA, fixtureB);

	}

	//EndContact listener
	void EndContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		m_theGame->EndCollision(fixtureA, fixtureB);
	}
	
};

class RayCastClosestCallback : public b2RayCastCallback
{

public:
	//Set reference to game object
	void SetGame(Game* _game)
	{
		m_theGame = _game;
	}

	//Constructor
	RayCastClosestCallback()
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
		if ((int)userData == PLAYER || (int)userData == FOOTSENSOR || (int)userData == HEADSENSOR || (int)userData == SIDESENSOR)
		{
			return -1.f;
		}

		//Call back in m_theGame
		m_theGame->RayCastCollision(fixture, point, fraction);

		m_hit = true; 
		m_point = point; 
		m_normal = normal; 

		//By returning the current fraction, we instruct the calling code to clip the ray and
		// continue the ray-cast to the next fixture. WARNING: do not assume that fixtures
		// are reported in order. However, by clipping, we can always get the closest fixture.
		return fraction; //Return fraction of ray
	}

	bool m_hit; //Ray hit fixture
	b2Vec2 m_point; //Point of where ray hit fixture
	b2Vec2 m_normal; //Normal of where ray hit fixture
};

