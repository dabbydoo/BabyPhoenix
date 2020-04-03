#include "EndlessMode.h"

void EndlessMode::InitScene(float windowWidth, float windowHeight)
{
}

void EndlessMode::GamepadStroke(XInputController* con)
{
}

void EndlessMode::GamepadUp(XInputController* con)
{
}

void EndlessMode::GamepadDown(XInputController* con)
{
}

void EndlessMode::GamepadStick(XInputController* con)
{
}

void EndlessMode::GamepadTrigger(XInputController* con)
{
}

void EndlessMode::KeyboardHold()
{
}

void EndlessMode::KeyboardDown()
{
}

void EndlessMode::KeyboardUp()
{
}

void EndlessMode::Update()
{
	backgroudUpdate();
	floorUpdate();
	bulletUpdate();

}

void EndlessMode::floorUpdate()
{
}

void EndlessMode::backgroudUpdate()
{
}

void EndlessMode::enemyUpdate()
{
}

void EndlessMode::objectUpdate()
{
}

void EndlessMode::bulletUpdate()
{
}

void EndlessMode::MouseMotion(SDL_MouseMotionEvent evnt)
{
}

void EndlessMode::MouseClick(SDL_MouseButtonEvent evnt)
{
}

void EndlessMode::MouseWheel(SDL_MouseWheelEvent evnt)
{
}
