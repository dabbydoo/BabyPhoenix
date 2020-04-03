#pragma once
#include"Scene.h"
#include "BackEnd.h"


class Start : public Scene
{
public:

	Start():Scene("Title") {}

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

	 void SetInMenu(bool* inMenu) { menu=inMenu; }
	 
	 void SetEndlessSelected(bool* end) { endless = end; }

	 void MakeTransparent();

	 void UndoTransparent();

	 vec2 ConvertToGl(vec2 clickCoord);
	  void MouseMotion(SDL_MouseMotionEvent evnt) override;
	  void MouseClick(SDL_MouseButtonEvent evnt) override;
	  void MouseWheel(SDL_MouseWheelEvent evnt) override;
private:

	unsigned int index=0;

	bool* menu = nullptr;

	bool* endless = nullptr;

	vector<unsigned int>all_components;

	unsigned int Start_entity, controls_entity, exit_entity, endlessMode_entity,arrow_entity;

};
