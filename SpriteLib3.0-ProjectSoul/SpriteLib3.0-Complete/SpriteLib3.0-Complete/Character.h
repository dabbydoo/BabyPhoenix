#pragma once
#include<iostream>
#include"Box2D/Box2D.h"
#include"ECS.h"

using namespace std;

class Character {

public:

	//getters 
	unsigned int getEntityID();
	int getHealth();
	auto getAnimation();
	auto getSprite();
	Character* getCharacter();

	int getUI();

	b2Body* getBody();

	//setters
	virtual void setEntityID(unsigned int) ;
	virtual void field_of_view();

	bool m_if_alive = true;

private:
	unsigned int m_entity;
};

class Enemy : public Character {

public:
	Enemy():m_playerEntity(EntityIdentifier::MainPlayer()) { }

	Enemy(unsigned int ID) : m_playerEntity(ID) { }

	void field_of_view() override;

private:
	
	const unsigned int m_playerEntity;
};