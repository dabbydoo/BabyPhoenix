#pragma once
#include "Game.h"
#include <iostream>


class MyListener : public b2ContactListener
{
	Game* m_theGame;

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

