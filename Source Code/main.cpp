#include "Game.h"


int main(int argc, char** args)
{
	Uint32 frameStart;
	int frameTime;

	Game* game = new Game();

	game->init();

	while (game->running())  // GAME LOOP
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart; // time each frame takes in millisec

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}

	game->quit();
	delete game;
	game = nullptr;

	return 0;
}