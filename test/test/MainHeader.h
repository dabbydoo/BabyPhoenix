#pragma once

#include "Scene.h"

class test :public Scene
{

public:
	test(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

private:
	unsigned int m_player;
};
