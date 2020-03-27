#pragma once
#include"Scene.h"

class Start : public Scene
{
public:
	Start(string name);

	void InitScene(float windowWidth, float windowHeight) override;

	void Update() override;

	 void GamepadStroke(XInputController* con) override;
	 void GamepadUp(XInputController* con) override;
	 void GamepadDown(XInputController* con) override;
	 void GamepadStick(XInputController* con) override;
	 void GamepadTrigger(XInputController* con) override;
	 void KeyboardHold() override;
	 void KeyboardDown() override;
	 void KeyboardUp() override;

	  void MouseMotion(SDL_MouseMotionEvent evnt) override;
	  void MouseClick(SDL_MouseButtonEvent evnt) override;
	  void MouseWheel(SDL_MouseWheelEvent evnt) override;
private:
	
	unsigned int Start_entity, instruction_entity, exit_entity, endlessMode_entity;

};
