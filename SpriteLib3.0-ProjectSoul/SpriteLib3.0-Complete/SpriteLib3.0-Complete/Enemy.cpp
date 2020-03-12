/*
#include "Enemy.h"

b2Body* Enemy::getBody()
{
	return ECS::GetComponent<PhysicsBody>(enemyID).GetBody();
}

vec3 Enemy::getPos()
{
	return ECS::GetComponent<Transform>(enemyID).GetPosition();
}

vec3 Enemy::getPlayerPos()
{
	return ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
}

void Enemy::SetPostion(b2Vec2 mov)
{
	getBody()->SetLinearVelocity(mov);
}

void Enemy::SetAnim(unsigned int anim)
{
	ECS::GetComponent<AnimationController>(enemyID).SetActiveAnim(anim);
}

void Enemy::SetID(unsigned int ID)
{
	enemyID = ID;
}

void Enemy::Update()
{
}
*/