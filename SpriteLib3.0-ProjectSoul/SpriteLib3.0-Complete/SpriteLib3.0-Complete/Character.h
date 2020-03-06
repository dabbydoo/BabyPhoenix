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
	int getUI();

	b2Body* getBody();

	//setters
	virtual void setEntityID(unsigned int) ;
	virtual void field_of_view();

	bool m_if_alive = true;

private:

	unsigned int m_entity;
};

class Player : public Character 
{
	void field_of_view() override;
	void magnetPull();

	bool m_initDashOnGround = true; //Flag for if initial dash started on ground
	bool m_initDashOnWall = false; //Flag for if initial dash started on the wall
	bool m_isDashing = false; //Flag for if currently dashing

	bool m_isPlayerOnGround = false;

	//Flag for if player on wall
	bool m_isPlayerOnWall = false;

	//Collision flags
	bool m_isPlayerOnCollision = false; //player collide
	bool m_isPlayerHeadCollide = false; //player head sensor collides
	bool m_isPlayerSideCollide = false; //player side sensor collides

	//the direction of the character 0/false is right || || 1/true is left
	bool m_character_direction = false;


private:
	bool can_jump = false;
	bool can_grapple = false;
	bool can_dash = false;
};

class Enemy : public Character {

	Enemy():m_playerEntity(EntityIdentifier::MainPlayer()) { }

	Enemy(unsigned int ID) : m_playerEntity(ID) { }

	void field_of_view() override;

private:

	const unsigned int m_playerEntity;

};