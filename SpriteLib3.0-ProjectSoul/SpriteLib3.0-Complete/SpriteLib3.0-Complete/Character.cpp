#include "Character.h"

unsigned int Character::getEntityID()
{
	return m_entity;
}

int Character::getHealth()
{
	return ECS::GetComponent<HealthBar>(m_entity).GetHealth();
}

auto Character::getAnimation()
{
	return ECS::GetComponent<AnimationController>(m_entity);
}

auto Character::getSprite()
{
	return ECS::GetComponent<Sprite>(m_entity);
}

Character* Character::getCharacter()
{
	return this;
}

int Character::getUI()
{
	return 0;
}

b2Body* Character::getBody()
{
	return ECS::GetComponent<PhysicsBody>(m_entity).GetBody();
}

void Character::setEntityID(unsigned int entity)
{
	m_entity = entity;
}

void Enemy::field_of_view()
{
}

