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

	loadTextures();

	board = new Board(boardSize, comboSize, width, height);

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
	//counter++;
	//printf("counter: %d\n", counter);
	if (!waitingForPlayerInput && board->isBoardSolved())
	{
		// wait(1000);
	}
	if (waitingForPlayerInput)
	{
		if (isMousePressed)
		{
			board->startTileMovement(mouseXPos, mouseYPos);
		}
		else
		{
			board->endTileMovement(mouseXPos, mouseYPos);
		}

		// if tile movement resulted in a valid play
		// the board will no longer be solved
		if (!board->isBoardSolved())
			waitingForPlayerInput = false;
	}
	else
	{
		//printf("is still: %d\n", board->isBoardStill());
		//printf("is filled: %d\n", board->isBoardFilled());
		//board->printBoard();
		if (board->isBoardStill())
		{
			if (board->isBoardFilled())
				board->solve();
			else
				board->spawnTiles();
		}
		board->applyGravity();

		if (board->isBoardStill() && board->isBoardFilled() && board->isBoardSolved())
			waitingForPlayerInput = true;
	}
	//board->updateFrameTime();
	Sleep(15);
}

void	Game::render()
{
	SDL_RenderClear(renderer);

	// draws background
	// SDL_SetRenderDrawColor(renderer, bgColor >> 16, bgColor >> 8, bgColor, 0xFF);

	SDL_RenderCopy(renderer, backgroundTex, NULL, NULL);

	board->renderBoard(renderer, spriteMap);

	SDL_RenderPresent(renderer);
}

void	Game::loadTextures()
{
	backgroundTex = IMG_LoadTexture(renderer, "assets/Backdrop13.png");

	SDL_Texture* tileSprite = nullptr;

	// should do this in a for loop
	// but had trouble formatting a string
	tileSprite = IMG_LoadTexture(renderer, "assets/Color-1.png");
	spriteMap.insert(std::pair<Color, SDL_Texture*>(Black, tileSprite));
	tileSprite = IMG_LoadTexture(renderer, "assets/Color-2.png");
	spriteMap.insert(std::pair<Color, SDL_Texture*>(Silver, tileSprite));
	tileSprite = IMG_LoadTexture(renderer, "assets/Color-3.png");
	spriteMap.insert(std::pair<Color, SDL_Texture*>(Pink, tileSprite));
	tileSprite = IMG_LoadTexture(renderer, "assets/Color-4.png");
	spriteMap.insert(std::pair<Color, SDL_Texture*>(Blue, tileSprite));
	tileSprite = IMG_LoadTexture(renderer, "assets/Color-5.png");
	spriteMap.insert(std::pair<Color, SDL_Texture*>(Orange, tileSprite));
}

void	Game::handleMouseEvent(SDL_Event event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
		isMousePressed = true;
	if (event.type == SDL_MOUSEBUTTONUP)
		isMousePressed = false;
	if (event.type == SDL_MOUSEMOTION)
	{
		mouseXPos = event.motion.x;
		mouseYPos = event.motion.y;
	}
}

void	Game::handleKeyboardEvent(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
	}
}