#include <iostream>
#include <stdlib.h>
#include <time.h>

typedef int Color;

enum Colors
{
	Color1,
	Color2,
	Color3,
	Color4,
	Color5,
	ColorEnumSize
};

typedef struct Tile {
	bool	isEmpty;
	Color	color;
	int		baseXPos;
	int		baseYPos;
	float	xOffset;
	float	yOffset;
}Tile;

class Board
{
public:
	Board(int boardSize, int comboSize);
	~Board();

	// attempts to swap two tiles.
	// returns true if the swap results in a valid sequence
	// returns false otherwise
	bool tryPlay(int x1, int y1, int x2, int y2);

	// deletes all deletable tiles
	void solve();

	// checks if all slots of the board are filled
	bool isBoardFilled();

	// checks if the board has any possible combos
	// returns false if one or more combos are possible
	bool isBoardSolved();

	// applies 1 level of gravity (tiles drop 1 grid)
	void applyGravity();

	// spawns one row of tiles at the top of the board
	void spawnTiles();

private:
	Tile** board = nullptr;	// game board is a 2d matrix of tiles

	// TODO stage 1, 2, 3. so that changes arent instant
	// do stages outside class?
	
	int comboSize = 0;
	int boardSize = 0;


	// is tile inside a sequence of tiles of the same color
	// the sequence must be >= comboSize
	bool isTileInsideCombo(int x, int y);

	Color generateRandomColor();
};