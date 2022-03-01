#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Board.hpp"


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

	int	bgColor = 0x32A86B;
	bool isRunning = false;
	bool waitingForPlayerInput = false;
	SDL_Window* window;
	SDL_Renderer* renderer;

	void	loadTextures();
};
