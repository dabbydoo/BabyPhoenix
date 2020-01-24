#pragma once
using namespace std;

#include "Scene.h"


class AssignmentScene : public Scene
{
public:
	AssignmentScene(string name);

	void InitScene(float windowWidth, float windowHeight) override;
private:
	unsigned int m_player;
};
