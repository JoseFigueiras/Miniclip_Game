#include "Board.hpp"

Board::Board(int boardSize, int comboSize, int screenWidth, int screenHeight)
{
	Board::boardSize = boardSize;
	Board::comboSize = comboSize;
	Board::screenSize = screenWidth < screenHeight ? screenWidth : screenHeight;
	Board::tileSize = (screenSize / 2) / boardSize;
	Board::spaceBetweenTiles = tileSize / 5;

	int boardPixelSize = boardSize * (tileSize + spaceBetweenTiles);
	Board::topLeftX = screenWidth / 2 - boardPixelSize / 2;
	Board::topLeftY = screenHeight / 2 - boardPixelSize / 2;

	initTiles();
}

Board::~Board()
{
	for (int i = 0; i < boardSize; i++)
		delete board[i];
	delete board;
}

void Board::initTiles()
{
	// init board as a boardSize x boardSize 2d Matrix of type Tile
	board = new Tile*[boardSize];
	for (int i = 0; i < boardSize; i++)
		board[i] = new Tile[boardSize];

	for (int x = 0; x < boardSize; x++) {
		for (int y = 0; y < boardSize; y++) {
			board[x][y].isEmpty = false;
			board[x][y].color = generateRandomColor();
			board[x][y].finalXPos = topLeftX + x * (tileSize + spaceBetweenTiles);
			board[x][y].finalYPos = topLeftY + y * (tileSize + spaceBetweenTiles);
			board[x][y].currentYPos = board[x][y].finalYPos;
			board[x][y].velocity = 0.0f;
		}
	}
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
	for (int x = 0; x < boardSize; x++) {
		for (int y = 0; y < boardSize; y++) {
			if (isTileInsideCombo(x, y))
			{
				board[x][y].isEmpty = true;
				board[x][y].velocity = 0.0f;
				board[x][y].currentYPos = board[x][y].finalYPos;
			}
		}
	}
}

bool Board::isBoardStill()
{
	for (int x = 0; x < boardSize; x++)
		for (int y = 0; y < boardSize; y++)
			if (board[x][y].currentYPos != board[x][y].finalYPos)
				return false;
	return true;
}

bool Board::isBoardFilled()
{
	for (int x = 0; x < boardSize; x++)
		for (int y = 0; y < boardSize; y++)
			if (board[x][y].isEmpty)
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
	for (int x = 0; x < boardSize; x++)
	{
		// loop row by row starting from the bottom
		// does not look at the first (top) row
		for (int y = boardSize - 1; y >= 1; y--)
		{
			if (board[x][y].isEmpty)
			{
				// swap tiles
				// put content of tile above into empty tile
				// make tile above empty
				Tile* tileEmpty = &board[x][y];
				Tile* tileAbove = &board[x][y - 1];

				tileEmpty->isEmpty = tileEmpty->isEmpty;
				tileEmpty->color = tileAbove->color;
				tileEmpty->currentYPos = tileAbove->currentYPos;
				tileEmpty->velocity = tileAbove->velocity;

				tileAbove->isEmpty = true;
			}
			// is tile in free fall
			else if (board[x][y].currentYPos != board[x][y].finalYPos)
			{
				board[x][y].currentYPos += board[x][y].velocity;
				if (board[x][y].currentYPos >= board[x][y].finalYPos)
					board[x][y].currentYPos = board[x][y].finalYPos;
				if (board[x][y].velocity == 0.0f)
					board[x][y].velocity = 1;
				board[x][y].velocity = board[x][y].velocity * 1.1f;
			}
		}
	}
}

void Board::spawnTiles()
{
	// y index for the top row
	int y = 0;

	// loop through top row, spawn tiles if empty space found
	for (int x = 0; x < boardSize; x++)
	{
		if (board[x][y].isEmpty)
		{
			board[x][y].color = generateRandomColor();
			board[x][y].isEmpty = false;
			board[x][y].currentYPos = board[x][y].finalYPos + tileSize + spaceBetweenTiles;
		}
	}
}

bool Board::isTileInsideCombo(int x, int y)
{
	Tile startTile = board[x][y];

	// init as 1 to account for the starting tile
	int	matchingHorizontal = 1;

	// loop forward and count ocurrences
	for (int i = x + 1; 0 <= i && i < boardSize && board[i][y].color == startTile.color; i++)
		matchingHorizontal++;
	// loop backwards and count ocurrences
	for (int i = x - 1; 0 <= i && i < boardSize && board[i][y].color == startTile.color; i--)
		matchingHorizontal++;

	if (matchingHorizontal >= comboSize)
		return true;

	// init as 1 to account for the starting tile
	int	matchingVertical = 1;

	// loop up and count ocurrences
	for (int i = y + 1; 0 <= i && i < boardSize && board[x][i].color == startTile.color; i++)
		matchingVertical++;
	// loop down and count ocurrences
	for (int i = y - 1; 0 <= i && i < boardSize && board[x][i].color == startTile.color; i--)
		matchingVertical++;

	if (matchingVertical >= comboSize)
		return true;

	return false;
}

Color Board::generateRandomColor()
{
	int randomNum;

	int* seed = new int();
	srand((unsigned int)seed);
	delete seed;

	// generate random number between 1 and 5 (inclusive)
	randomNum = rand() % ColorEnumSize;

	return (Color)randomNum;
}

void Board::renderBoard(SDL_Renderer* renderer, std::map<Color, SDL_Texture*> spriteMap)
{
	for (int x = 0; x < boardSize; x++)
	{
		for (int y = 0; y < boardSize; y++)
		{
			if (board[x][y].isEmpty)
				;
			else
			{
				SDL_Rect* dstrect = new SDL_Rect();

				dstrect->x = board[x][y].finalXPos;
				dstrect->y = board[x][y].currentYPos;
				dstrect->w = tileSize;
				dstrect->h = tileSize;
				SDL_RenderCopy(renderer, spriteMap[board[x][y].color], NULL, dstrect);
				//printf("color = %d\n", board[x][y].color);

				delete dstrect;
			}
		}
	}
}

