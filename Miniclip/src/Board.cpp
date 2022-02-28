#include "Board.hpp"

Board::Board(int boardSize, int comboSize)
{
	Board::boardSize = boardSize;
	Board::comboSize = comboSize;

	// init board as a boardSize x boardSize 2d Matrix of type Tile
	board = new Tile*[boardSize];
	for (int i = 0; i < boardSize; i++)
		board[i] = new Tile[boardSize];
}

Board::~Board()
{
	for (int i = 0; i < boardSize; i++)
		delete board[i];
	delete board;
}

bool Board::tryPlay(int x1, int y1, int x2, int y2)
{
	for (int x = 0; x < boardSize; x++)
		for (int y = 0; y < boardSize; y++)
			if (isTileInsideCombo(x, y))
				return true;
	return false;
}

void Board::solve()
{
	for (int x = 0; x < boardSize; x++)
		for (int y = 0; y < boardSize; y++)
			if (isTileInsideCombo(x, y))
				board[x][y].isEmpty = true;
}

bool Board::isBoardFilled()
{
	for (int x = 0; x < boardSize; x++)
		for (int y = 0; y < boardSize; y++)
			if (board[x][y].isEmpty || board[x][y].currentYPos != board[x][y].finalYPos)
				return false;
	return true;
}

bool Board::isBoardSolved()
{
	for (int x = 0; x < boardSize; x++)
		for (int y = 0; y < boardSize; y++)
			if (isTileInsideCombo(x, y))
				return false;
	return true;
}

void Board::applyGravity()
{
	// loop row by row starting from the bottom
	// does not look at the last (top) row
	for (int x = 0; x < boardSize - 1; x++)
	{
		for (int y = 0; y < boardSize; y++)
		{
			if (board[x][y].isEmpty)
			{
				// swap current (empty) tile with tile above
				Tile temp = board[x][y];

				board[x][y] = board[x + 1][y];
				board[x + 1][y] = temp;
			}
			// is tile in free fall
			else if (board[x][y].currentYPos != board[x][y].finalYPos)
			{
				board[x][y].currentYPos += velocity * frameTime;
				if (board[x][y].currentYPos >= board[x][y].finalYPos)
					board[x][y].currentYPos = board[x][y].finalYPos;
				velocity = velocity * 1.1f;
			}
		}
	}
}

void Board::spawnTiles()
{
	// y index for the top row
	int y = boardSize - 1;

	// loop through top row, spawn tiles if empty space found
	for (int x = 0; x < boardSize; x++)
	{
		if (board[x][y].isEmpty)
		{
			board[x][y].color = generateRandomColor();
			board[x][y].isEmpty = false;
		}
	}
}

bool Board::isTileInsideCombo(int x, int y)
{
	Tile startTile = board[x][y];

	// init as 1 to account for the starting tile
	int	matchingHorizontal = 1;

	// loop forward and count ocurrences
	for (int i = x + 1; 0 <= i && i < boardSize && board[i][y].color != startTile.color; i++)
		matchingHorizontal++;
	// loop backwards and count ocurrences
	for (int i = x - 1; 0 <= i && i < boardSize && board[i][y].color != startTile.color; i--)
		matchingHorizontal++;

	if (matchingHorizontal >= comboSize)
		return true;

	// init as 1 to account for the starting tile
	int	matchingVertical = 1;

	// loop up and count ocurrences
	for (int i = y + 1; 0 <= i && i < boardSize && board[x][i].color != startTile.color; i++)
		matchingVertical++;
	// loop down and count ocurrences
	for (int i = y - 1; 0 <= i && i < boardSize && board[x][i].color != startTile.color; i--)
		matchingVertical++;

	if (matchingVertical >= comboSize)
		return true;

	return false;
}

Color Board::generateRandomColor()
{
	int randomNum;

	// initialize random seed
	srand(time(NULL));

	// generate random number between 1 and 5 (inclusive)
	randomNum = rand() % ColorEnumSize;

	return (Color)randomNum;
}

void Board::updateFrameTime()
{
	timeCurrentFrame = getCurrentTime;

	frameTime = timeCurrentFrame - timeLastFrame;
	timeLastFrame = timeCurrentFrame;
}

void renderBoard(renderer, spriteMap)
{
	for (int x = 0; x < boardSize; x++)
		for (int y = 0; y < boardSize; y++)
			SDL_RenderCopy(renderer, spriteMap[board[x][y].color], NULL, NULL);
}

