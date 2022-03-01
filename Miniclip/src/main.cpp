#include "SDL.h"
#include "Game.hpp"

int main(int argc, char* argv[])
{
	Game* game = new Game("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							1200, 1000, false, 8, 3);

	while (game->running())
	{
		game->handleEvents();
		game->update();
		game->render();
	}

	delete game;
	return 0;
}