#include <iostream>
#include <stdlib.h>
#include <time.h>

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
	bool	isEmpty;
	Color	color;
	int		finalXPos;
	int		finalYPos;
	int		currentYPos;
	float	velocity;

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
	// checks if all tiles are where they should be (not falling from gravity
	bool isBoardFilled();

	// checks if the board has any possible combos
	// returns false if one or more combos are possible
	bool isBoardSolved();

	// applies gravity for that frame
	void applyGravity();

	// spawns one row of tiles at the top of the board
	void spawnTiles();

	// self explanatory tbqh
	void updateFrameTime();

	// renders the board's tiles
	void renderBoard(renderer, spriteMap);
private:
	Tile** board = nullptr;	// game board is a 2d matrix of tiles

	// TODO stage 1, 2, 3. so that changes arent instant
	// do stages outside class?
	
	int comboSize = 0;
	int boardSize = 0;

	int frameTime = 0;
	Time timeLastFrame = 0;

	// is tile inside a sequence of tiles of the same color
	// the sequence must be >= comboSize
	bool isTileInsideCombo(int x, int y);

	Color generateRandomColor();
};