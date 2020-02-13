#pragma once
using namespace std;

#include "Scene.h"

#include <iostream>

//fixture name
enum fixtureName { PLAYER = 1, FOOTSENSOR, HEADSENSOR, SIDESENSOR, GROUND, WALL, PLATFORM, OBJECT };

class AssignmentScene : public Scene
{
public:
	AssignmentScene(string name);

	void InitScene(float windowWidth, float windowHeight) override;
private:
	unsigned int m_background;
};


