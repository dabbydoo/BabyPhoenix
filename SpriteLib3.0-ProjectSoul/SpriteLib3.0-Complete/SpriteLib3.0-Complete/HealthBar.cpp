#include "HealthBar.h"
#include<stdio.h>
#include <iostream>
#include <string>
#include <sstream>
using std::cout;
using std::endl;
using std::cin;
HealthBar::HealthBar()
{
}
HealthBar::HealthBar(float health)
{
	m_health = health;
}

HealthBar::~HealthBar()
{
}

void HealthBar::DisplayHealth()
{
	//std::cout << "Health: " << std::to_string((m_health*100.f)) << "%" << std::endl;

}

float HealthBar::GetHealth() const
{
	return m_health;
}

void HealthBar::SetHealth(float health)
{
	m_health = health>m_max_h?m_max_h:health;
}

void HealthBar::SetMaxHealth(float health)
{
	m_max_h = health;
	m_health = health;
}
