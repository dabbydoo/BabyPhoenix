#pragma once
#include"Scene.h"
#include"BackEnd.h"

enum class Object {

ENEMY,
OBJECT,
FLOOR,
BACKGROUND,

};

class InfoHolder {
	public:
		//Entity ID, Object type
		InfoHolder(unsigned int ID, Object obj) { entityID = ID; object = obj; }

		vec3 GetPos() { ECS::GetComponent<Transform>(entityID).GetPosition(); }
		b2Body* GetBody(){ ECS::GetComponent<PhysicsBody>(entityID).GetBody(); }

private:
	Object object;
	unsigned int entityID;
};


class EndlessMode : public Scene {

public:


	EndlessMode(string name) :Scene(name) { ; }

	void InitScene(float windowWidth, float windowHeight) override;

	void GamepadStroke(XInputController* con) override;
	void GamepadUp(XInputController* con) override;
	void GamepadDown(XInputController* con) override;
	void GamepadStick(XInputController* con) override;
	void GamepadTrigger(XInputController* con) override;
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

	void SetInitPlayerPos(vec3 pos) override {}

	void Update()override;

	void floorUpdate();
	void backgroudUpdate();
	void enemyUpdate();
	void objectUpdate();
	void bulletUpdate();

	void MouseMotion(SDL_MouseMotionEvent evnt) override;
	void MouseClick(SDL_MouseButtonEvent evnt) override;
	void MouseWheel(SDL_MouseWheelEvent evnt) override;


private:

	vector<InfoHolder*>Enemy;
	vector<InfoHolder*>Floor;
	vector<InfoHolder*>Background;
	vector<InfoHolder*>Obstacle;

	vector<InfoHolder*>infoHolder;

	const vec2 min = vec2(-178, -100);

	const vec2 max = vec2(178, 100);

	unsigned int mouse;

};