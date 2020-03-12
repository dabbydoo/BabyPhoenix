#pragma once
#include "Scene.h"
#include <iostream>

using namespace std;

//fixture name
enum fixtureName { PLAYER = 1, FOOTSENSOR, HEADSENSOR, SIDESENSOR, GROUND, WALL, PLATFORM, MAGNET, DOORWAY, BULLET};


class Room : public Scene
{
public:
	Room(string name);

	void InitScene(float windowWidth, float windowHeight) override;
	
	void Update() override
	{}
	
private:
	void CreateCamera(float windowWidth, float windowHeight);
	void CreateBackground(string fileName, vec2 size);
	void CreateRoomBoundary();
	void CreateMainPlayer(vec3 position);
	void CreatePlatform(string fileName, vec2 size, vec2 position);
	void CreateMagnet(string fileName, vec2 size, vec2 position);
	void CreateEdge(b2Vec2 point1, b2Vec2 point2, fixtureName fixtureName, bool sensor = false);

	void CreateDoorWay(b2Vec2 position);


	

	unsigned int m_background;

};
