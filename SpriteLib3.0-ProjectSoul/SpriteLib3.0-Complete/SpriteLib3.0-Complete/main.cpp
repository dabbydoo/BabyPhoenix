#include "Game.h"
#include "GPCSound.h"

#undef main
int main()
{
	//Create the Game
	Game theGame;
	//SoundManager::init("./assets/sounds/");
	//Sound2D _test("ChronoRuin.wav", "group1");
	//_test.play();

	//Initialize the game
	theGame.InitGame();

	//Runs the game until it returns :)
	return theGame.Run();
}