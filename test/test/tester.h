#pragma once

#include "Scene.h"

class tester :public Scene
{

public:
	tester(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;
};
