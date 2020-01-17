#include "healthbar.h"
#include<iostream>
#include<string>

using namespace std;

healthbar::healthbar()
{
}

healthbar::healthbar(float health)
{
	m_health = health;
}

healthbar::~healthbar()
{
}

void healthbar::displayhealth()
{
 //cout << "Health: " << to_string((m_health * 100.f)) << "%" << endl;

}

float healthbar::GetHealth() const
{
	return m_health;
}

void healthbar::SetHealth(float health)
{
	m_health = health;
}
