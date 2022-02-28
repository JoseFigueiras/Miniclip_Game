#include "Game.hpp"


Game::Game(const char* title, int xpos, int ypos, int width, int height,
	bool fullscreen, int boardSize, int comboSize)
{
	int	flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)		// if unsuccesful
	{
		std::cout << "Could not init Subsystems." << std::endl;
		return;
	}
	else
	{
		std::cout << "Sybsystems Initialised..." << std::endl;
		
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (!window)
		{
			std::cout << "Could not create window." << std::endl;
			return;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (!renderer)
		{
			std::cout << "Could not create renderer." << std::endl;
			return;
		}

		isRunning = true;
	}

	board = new Board(boardSize, comboSize);

	backgroundTex = IMG_LoadTexture(renderer, "D:\\Dev\\Miniclip\\assets\\Backdrop13.png");


	waitingForPlayerInput = false;
}

Game::~Game()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	delete board;

	std::cout << "Game cleaned" << std::endl;
}

void	Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			handleKeyboardEvent(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEMOTION:
			handleMouseEvent(event);
			break;
		default:
			break;
		}
	}
}

void	Game::update()
{
	if (waitingForPlayerInput)
	{
		
	}
	else
	{
		
	}

}

void	Game::render()
{
	SDL_RenderClear(renderer);

	// draws background
	SDL_SetRenderDrawColor(renderer,
		bgColor >> 16, bgColor >> 8, bgColor, 0xFF);

	SDL_RenderCopy(renderer, backgroundTex, NULL, NULL);

	SDL_RenderPresent(renderer);
}
