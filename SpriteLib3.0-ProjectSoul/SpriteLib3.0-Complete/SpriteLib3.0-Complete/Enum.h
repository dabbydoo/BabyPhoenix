#pragma once

enum fixtureName 
{ 
	PLAYER = 1, 
	FOOTSENSOR, 
	HEADSENSOR, 
	SIDESENSOR, 
	GROUND, 
	WALL, 
	PLATFORM, 
	MAGNET, 
	DOORWAY, 
	BULLET, 
	BREAKABLE, 
	ENEMY, 
	ENEMYBULLET
};


enum Anim 
{
	IDLE,
	WALK = 2,
	RUN = 4,
	DASH = 6,
	JUMP_BEGIN = 8,
	JUMP_MIDDLE = 10,
	JUMP_END = 12,
	FALL = 14,
	FLINCH = 16,
	DEATH = 18,
	SHOOT = 20,

};

enum Direction 
{
	LEFT,
	RIGHT
};