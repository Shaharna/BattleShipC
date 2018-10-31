/**
 * @file battleships.c
 * @author  Shahar Nahum <shahar.nahum@mail.huji.ac.il>
 * @version 2.0
 * @date 10 Aug 2018
 *
 * @brief System to keep track of the cooking times.
 *
 * @section DESCRIPTION
 * The system runs a battleships game with a minimal gui.
 * Input  : The board game size, and the players moves.
 * Process: managing the game, starting with locating randomly the ships and processing every move
 * received from the player.
 * Output : Each turn the program prints the board an a matching message.
 */
// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "battleships.h"

// -------------------------- const definitions -------------------------

/**
 * @def SUNK_MESSAGE "Hit and sunk.\n"
 * @brief the message printed to the screen when the player hit a ship and it made her sunk.
 */
#define SUNK_MESSAGE "Hit and sunk.\n"

/**
 * @def HIT_MESSAGE "Hit!\n"
 * @brief the message printed to the screen when the player hit a ship.
 */
#define HIT_MESSAGE "Hit!\n"

/**
 * @def ALREADY_HIT_MESSAGE "Already been Hit.\n"
 * @brief the message printed to the screen when the player made a move and he already made
 * this move.
 */
#define ALREADY_HIT_MESSAGE "Already been Hit.\n"

/**
 * @def INVALID_MOVE_MESSAGE "invalid Move, try again\n"
 * @brief the message printed to the screen when the player made an invalid move.
 * this move.
 */
#define INVALID_MOVE_MESSAGE "invalid Move, try again\n"

/**
 * @def INVALID_MOVE_MESSAGE "invalid Move, try again\n"
 * @brief the message printed to the screen when the player made a move and did not hit a ship.
 * this move.
 */
#define MISS_MESSAGE "Miss\n"

/**
 * @def SHIPS_NUM 5
 * @brief the number of ships participating in the game.
 */
#define SHIPS_NUM 5

/**
 * @def VERTICAL 0
 * @brief the angle of the ship is vertical
 */
#define VERTICAL 0

/**
 * @def HORIZONTAL 1
 * @brief the angle of the ship is horizontal
 */
#define HORIZONTAL 1

/**
 * @def  TRUE 1
 * @brief the angle of the ship is vertical
 */
#define TRUE 1

/**
 * @def FALSE -1
 * @brief the angle of the ship is horizontal
 */
#define FALSE (-1)

/**
 * @def EMPTY_CELL '_'
 * @brief An empty cell in the board.
 */
#define EMPTY_CELL '_'

/**
 * @def MISS_CELL 'o'
 * @brief A mark for a taken cell in the manager board.
 */
#define MISS_CELL 'o'

/**
 * @def HIT_CELL 'x'
 * @brief A mark for a taken cell in the manager board.
 */
#define HIT_CELL 'x'

/**
 * @def MIN_NUM_ASCII_VALUE 48
 * @brief the ASCII value of the min cell in the ships array cell, converting the value from char
 * to int and vice versa. Helping to match the index of the ship located in the manager board to
 * the ship in the ships array.
 */
#define MIN_NUM_ASCII_VALUE 48

/**
 * @def START_LETTER 97
 * @brief The first letter to be printed in the boar's row indexes.
 */
#define START_LETTER 97

/**
 * The length of each ship participating in the game.
 */
enum Ships_VERITY
		{
		AIRCRAFT_CARRIER = 5,
		BATTLE_CRIUSER = 4,
		MISSILE_SHIP = 3,
		SUBMARINE = 3,
		BATTLE_SHIP = 2
		};
// ------------------------------ structs ----------------------------

/**
 * a structure describing a ship in the game. includes the following attributes:
 * row - the row index of the ship on the board.
 * col - the column index of the ship on the board.
 * angle - 0 for vertical, 1 for horizontal.
 * size - the length of the ship.
 * lives - the number of cells on the board that were not hit. (the initialization of lives is
 * the size of the ship).
 */
typedef struct Ship
{
	int row;
	int col;
	int length;
	int angle;
	int lives;
} Ship;

// ------------------------------ functions ----------------------------
/**
 * @brief Receives a size and creates a char board initialized to empty cells.
 * @param size The board size
 * @return The new board initialized.
 */
char **initialBoard(int size)
{
	int i, j;
	char **board = (char **) malloc(size * sizeof(char *));
	for (i = 0; i < size; i++)
	{
		board[i] = (char *) malloc(size * sizeof(char));
		for (j = 0; j < size; j++)
		{
			board[i][j] = EMPTY_CELL;
		}
	}
	return board;
}


/**
 * @brief Receives a new ship just placed randomly on the board and return true
 *  if the entire ship coordinates can be placed in the board bounds and false otherwise.
 * @param Ship *newShip the new ship.
 * @param boardS The board Size.
 * @return TRUE if the ship location is in the board bounds FALSE otherwise
 */
int isInRange(Ship *newShip, int boardS)
{
	if (newShip->angle == VERTICAL)
	{
		if ((newShip->row + (newShip->length))-1 < boardS)
		{
			return TRUE;
		}
	}
	else
	{
		if ((newShip->col + (newShip->length))-1 < boardS)
		{
			return TRUE;
		}
	}
	return FALSE;
}

/**
 * @brief The function receives a new ship needed to be located in the board and the manager
 * board holding all the other ships taken Coordinates.
 * The function return TRUE if the new ship's location is free and FALSE if its taken.
 * @param managerBoard The manager board in the game (saving all the ships locations).
 * @param newShip A pointer to the new ship needed to be placed.
 * @return TRUE If all the ships coordinate are free, FALSE otherwise.
 */
int isEmptyLocation(char **managerBoard, Ship *newShip)
{
	int j;
	if (newShip->angle == VERTICAL)
	{
		for (j = 0; j < newShip->length; j++)
		{
			if (managerBoard[(newShip->row) + j][newShip->col] != EMPTY_CELL)
			{
				return FALSE;
			}
		}
	}
	else
	{
		for (j = 0; j < newShip->length; j++)
		{
			if (managerBoard[newShip->row][(newShip->col) + j] != EMPTY_CELL)
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

/**
 * @brief The function receives a new ship needed to be located in the manager board and the
 * manager board holding all the other ships taken Coordinates. The function mark in the manager
 * board the ship location as taken.
 * @param managerBoard The manager board in the game (saving all the ships locations).
 * @param newShip A pointer to the new ship needed to be placed.
 * @param index The index of the ship in the ships array.
 */
void updateManagerBoard(Ship *newShip, char **managerBoard, int index)
{
	int j;
	if (newShip->angle == VERTICAL)
	{
		for (j = 0; j < newShip->length; j++)
		{
			managerBoard[(newShip->row) + j][newShip->col] = (char) (index + MIN_NUM_ASCII_VALUE);
		}
	}
	else if (newShip->angle == HORIZONTAL)
	{
		for (j = 0; j < newShip->length; j++)
		{
			managerBoard[(newShip->row)][(newShip->col) + j] = (char) (index + MIN_NUM_ASCII_VALUE);
		}
	}
}

/**
 * The function initial random values to the ship's parameters.
 * @param newShip The new ship to initialize
 * @param boardSize The size of the board.
 * @return A pointer to the new ship with new random parameters.
 */
Ship *randomizeParams(Ship *newShip, int boardSize)
{
	newShip->angle = rand() % 2;
	newShip->row = rand() % boardSize;
	newShip->col = rand() % boardSize;
	return newShip;
}

/**
 * @brief The function receives a new ship needed to be located in the board and the manager
 * board holding all the other ships taken Coordinates. The function picks a random value for
 * the ship, validate it, and mark it on the manager board.
 * @param newShip A pointer to the new ship needed to be placed.
 * @param boardSize The boardSize (as the height and width are equal)
 * @param managerBoard Rhe manager board in the game (saving all the ships locations).
 * @param index The index of the ship in the ships array.
 * */
void placeShip(Ship *newShip, int boardSize, char **managerBoard, int index)
{
	newShip = randomizeParams(newShip, boardSize);
	while (isInRange(newShip, boardSize) == FALSE ||
		   isEmptyLocation(managerBoard, newShip) == FALSE)
	{
		newShip = randomizeParams(newShip, boardSize);
	}
	updateManagerBoard(newShip, managerBoard, index);
}

/**
* @brief The function receives a the board size and the manager board holding all the other
* ships taken Coordinates.
* The function builds and locate all the ships in the game and holds them in an array.
* The function return the array of ships created.
* @param boardSize The boardSize (as the height and width are equal)
* @param managerBoard The manager board in the game (saving all the ships locations).
* @return The function return the array of ships created.
* */
Ship *shipFactory(int boardSize, char **managerBoard)
{
	int const arr[SHIPS_NUM] =  {
								AIRCRAFT_CARRIER,
							 	BATTLE_CRIUSER,
							 	MISSILE_SHIP,
							 	SUBMARINE,
								BATTLE_SHIP
								};
	Ship *shipArr = (Ship *) malloc(SHIPS_NUM * sizeof(Ship));
	int i;
	for (i = 0; i < SHIPS_NUM; i++)
	{
		shipArr[i].length = arr[i];
		shipArr[i].lives = shipArr[i].length;
		placeShip(&shipArr[i], boardSize, managerBoard, i);
	}
	return shipArr;
}

/**
 * @brief The function receives a  board size and a pointer to the board and print it.
 * @param board The board to print.
 * @param boardSize The boardSize (as the height and width are equal)
 * */
void printBoard(char **board, int boardSize)
{
	int i;
	for (i = 0; i < boardSize; i++)
	{
		printf(",%d", i + 1);
	}
	printf("\n");
	for (i = 0; i < boardSize; i++)
	{
		printf("%c", (char) (START_LETTER + i));
		for (int j = 0; j < boardSize; j++)
		{
			printf(" %c", board[i][j]);
		}
		printf("\n");
	}
}

/**
 * The function handles a case when the user hit a ship on the board. The function updates the
 * hit ship lives and if the ship is dead it will print the correct message and update the counter
 * of the dead ships in the game.
 * @param row The row received from the user.
 * @param col The column received from the user.
 * @param managerBoard The manager board in the game (saving all the ships locations).
 * @param toPrintBoard
 * @param boardSize The boardSize (as the height and width are equal)
 * @param ships An array holding all the ships participating in the game.
 * @param deadShips The counter counting the number of dead ships in the game.
 * @return The updated number of dead ships in the game according to the last turn.
 */
int hit(int row, int col, char **managerBoard, char **toPrintBoard, Ship *ships, int deadShips)
{
	int index;
	toPrintBoard[row][col] = HIT_CELL;
	index = (int) (managerBoard[row][col] - MIN_NUM_ASCII_VALUE);
	ships[index].lives--;
	if (ships[index].lives == 0)
	{
		printf(SUNK_MESSAGE);
		deadShips++;
	}
	else
	{
		printf(HIT_MESSAGE);
	}
	return deadShips;
}

/**
 * The function verifies the move received by the player is valid (is in the board bounds).
 * @param row The row received from the user.
 * @param col The column received from the user.
 * @param boardSize The boardSize (as the height and width are equal)
 * @return
 */
int isValidMove(int row, int col, int boardSize)
{
	if (row > boardSize-1)
	{
		return FALSE;
	}
	if (col > boardSize-1)
	{
		return FALSE;
	}
	return TRUE;
}

/**
 * The function run a whole single turn in the game, receiving the user move.
 * @param row The row received from the user.
 * @param col The column received from the user.
 * @param managerBoard The manager board in the game (saving all the ships locations).
 * @param toPrintBoard The board represented to the user during the game, it holds all the user
 * shots marked as miss ('o') and hit('x').
 * @param boardSize The boardSize (as the height and width are equal)
 * @param ships An array holding all the ships participating in the game.
 * @param deadShips The counter counting the number of dead ships in the game.
 * @return The updated number of dead ships in the game according to the last turn.
 */
int singleTurn(int row, int col, char **managerBoard, char **toPrintBoard, int boardSize,
			   Ship *ships, int deadShips)
{
	if (isValidMove(row, col, boardSize) == FALSE)
	{
		printf(INVALID_MOVE_MESSAGE);
		return deadShips;
	}

	if (toPrintBoard[row][col] != EMPTY_CELL)
	{
		printf(ALREADY_HIT_MESSAGE);
	}
	else
	{
		if (managerBoard[row][col] == EMPTY_CELL)
		{
			toPrintBoard[row][col] = MISS_CELL;
			printf(MISS_MESSAGE);
		}
		else
		{
			deadShips = hit(row, col, managerBoard, toPrintBoard, ships, deadShips);
		}
	}
	printBoard(toPrintBoard, boardSize);
	return deadShips;
}

/**
* @brief The function receives a two dimension array and free all of its .
* @param board the board to print.
* @param boardSize the boardSize (as the height and width are equal)
* */
void free2DArray(char **array, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		free(array[i]);
	}
	free(array);
}

/**
 * The function free all the space taken by the program using the free function.
 * @param toPrintBoard The board represented to the user during the game, it holds all the user
 * shots marked as miss ('o') and hit('x').
 * @param managerBoard
 * @param shipsArray
 * @param boardSize
 */
void freeAllSpace(char **toPrintBoard, char **managerBoard, Ship *shipsArray, int boardSize)
{
	free2DArray(toPrintBoard, boardSize);
	free2DArray(managerBoard, boardSize);
	free(shipsArray);
}