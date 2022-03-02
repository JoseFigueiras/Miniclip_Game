#include <iostream>
#include <stdlib.h>
#include <map>
#include "SDL.h"
#include "SDL_image.h"

typedef int Color;

enum Colors
{
	Black,
	Silver,
	Pink,
	Blue,
	Orange,
	ColorEnumSize
};

typedef struct Tile {
	bool	isEmpty = true;
	Color	color = Black;
	int		finalXPos = 0;
	int		finalYPos = 0;
	int		currentXPos = 0;
	int		currentYPos = 0;
	float	velocity = 0.0f;
}Tile;

class Board
{
public:
	Board(int boardSize, int comboSize, int screenWidth, int screenHeight);
	~Board();


	// deletes all deletable tiles
	void solve();

	// checks if there are no falling pieces
	bool isBoardStill();

	// checks if all slots of the board are filled
	bool isBoardFilled();

	// checks if the board has any possible combos
	// returns false if one or more combos are possible
	bool isBoardSolved();

	// applies gravity for that frame
	void applyGravity();

	// spawns one row of tiles at the top of the board
	void spawnTiles();

	void startTileMovement(int mouseXPos, int mouseYPos);

	void endTileMovement(int mouseXPos, int mouseYPos);

	// renders the board's tiles
	void renderBoard(SDL_Renderer* renderer, std::map<Color, SDL_Texture*> spriteMap);

	void printBoard();

private:
	Tile** board = nullptr;	// game board is a 2d matrix of tiles

	// TODO stage 1, 2, 3. so that changes arent instant
	// do stages outside class?
	
	int comboSize = 0;
	int boardSize = 0;

	int topLeftX = 0;
	int topLeftY = 0;
	// size of smaller window side
	int screenSize = 0;
	// size of each tile in pixels
	int tileSize = 0;
	int spaceBetweenTiles = 0;

	bool isPlayOngoing = false;



	// inits the 2d matrix board
	void initTiles();

	// attempts to swap two tiles.
	// returns true if the swap results in a valid sequence
	// returns false otherwise
	bool tryPlay(int x1, int y1, int x2, int y2);

	// is tile inside a sequence of tiles of the same color
	// the sequence must be >= comboSize
	bool isTileInsideCombo(int x, int y);

	Color generateRandomColor();
};