#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <map>
#include "Board.hpp"
#include <string>
#include <windows.h> // for Sleep()


class Game
{
public:
	Game(const char* title, int xpos, int ypos, int width, int height,
		bool fullscreen, int boardSize, int comboSize);
	~Game();

	void	handleEvents();
	void	handleKeyboardEvent(SDL_Event event);
	void	handleMouseEvent(SDL_Event event);

	void	update();
	void	render();
	
	bool	running() { return isRunning; }

private:
	Board* board = nullptr;
	SDL_Texture* backgroundTex = nullptr;
	std::map<Color, SDL_Texture*> spriteMap;

	bool isMousePressed = false;
	int mouseXPos = 0;
	int mouseYPos = 0;

	int counter = 0;
	bool isRunning = false;
	bool waitingForPlayerInput = false;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	void	loadTextures();
};
