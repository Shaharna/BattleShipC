/**
 * @file battleships_game.c
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
#include <time.h>
#include <string.h>

// -------------------------- const definitions -------------------------


/**
 * @def EXIT_STR "exit"
 * @brief the number of ships participating in the game.
 */
#define EXIT_STR "exit"

/**
 * @def MEMORY_ERROR 2
 * @brief the integer returned if one of the pointers is NULL .
 */
#define MEMORY_ERROR 2

/**
 * @def BOARD_SIZE_ERROR 3
 * @brief the integer returned if the .
 */
#define BOARD_SIZE_ERROR 3

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
 * @def SHIPS_NUM 5
 * @brief the number of ships participating in the game.
 */
#define SHIPS_NUM 5

/**
 * @def MIN_CHAR_VALUE 97
 * @brief the ascii value of the minimum letter symbolling the rows in the board.
 */
#define MIN_CHAR_VALUE 97

/**
 * @def EXIT_GAME 0
 * @brief the integer returned if the user typed exit.
 */
#define EXIT_GAME 0

/**
 * @def  GAME_OVER_MESSAGE "Game over\n"
 * @brief  The message printed to the console when the game is over.
 */
#define GAME_OVER_MESSAGE "Game over\n"

/**
 * @def ENTER_COORDINATES_MSG "enter coordinates:"
 * @brief the message printed to the screen when the user is asked to enter his moves.
 */
#define ENTER_COORDINATES_MSG "enter coordinates:"

/**
 * @def WRONG_BOARD_SIZE_MSG "You've entered a wrong size for the board."
 * @brief the message printed to the screen when the user inserted an invalid size for the board,
 * meaning the size was lower then 5 or bigger then 26.
 */
#define WRONG_BOARD_SIZE_MSG "You've entered a wrong size for the board."

/**
 * @def MAX_BOARD_SIZE 26
 * @brief The maximal board size allowed in the game.
 */
#define MAX_BOARD_SIZE 26

/**
 * @def MIN_BOARD_SIZE 5
 * @brief The minimal board size allowed in the game.
 */
#define MIN_BOARD_SIZE 5

/**
 * @def ENTER_BOARD_SIZE_MSG "enter board size: \n"
 * @brief The message printed to the screen when the user is asked to enter the board size.
 */
#define ENTER_BOARD_SIZE_MSG "enter board size: \n"
/**
 * @def MAX_BOARD_SIZE 26
 * @brief The maximal character that we need to process from the input.
 */
#define MAX_CHAR_INPUT 5


// ------------------------------ functions ----------------------------



/**
 * The function running all the turns in the game, using the single turn function.
 * @param boardSize
 * @return
 */
int run(int boardSize);

/**
 * This function verifies that the size received for the board is valid.
 * meaning the size is bigger then 5 or lower then 26.
 * @param sizeInput The size received for the board
 * @return TRUE (1) if the size is valid, FALSE otherwise.
 */
int isValidBoarSize(int sizeInput)
{
	if (sizeInput <= MAX_BOARD_SIZE && sizeInput >= MIN_BOARD_SIZE)
	{
		return TRUE;
	}
	return FALSE;
}

/**
 * The main function.
 * @return
 */
int main()
{
	srand((unsigned) time(0));
	int boardSize;
	printf(ENTER_BOARD_SIZE_MSG);
	scanf("%d", &boardSize);
	if (isValidBoarSize(boardSize) == FALSE)
	{
		fprintf(stderr, WRONG_BOARD_SIZE_MSG);
		return BOARD_SIZE_ERROR;
	}
	return run(boardSize);
}

/**
 * The function running all the turns in the game, using the single turn function.
 * @param boardSize
 * @return
 */
int run(int boardSize)
{
	char input[MAX_CHAR_INPUT];
	int col, rowInt, deadShips = 0;
	char rowChar;
	char **toPrintBoard = initialBoard(boardSize);
	char **managerBoard = initialBoard(boardSize);
	Ship *shipsArray = shipFactory(boardSize, managerBoard);
	if (managerBoard == NULL || toPrintBoard == NULL || shipsArray == NULL)
	{
		freeAllSpace(toPrintBoard, managerBoard, shipsArray, boardSize);
		return MEMORY_ERROR;
	}
	printBoard(toPrintBoard, boardSize);
	while (deadShips < SHIPS_NUM)
	{
		printf(ENTER_COORDINATES_MSG);
		scanf("%s", input);
		if (strcmp(input, EXIT_STR) == 0)
		{
			freeAllSpace(toPrintBoard, managerBoard, shipsArray, boardSize);
			return EXIT_GAME;
		}
		scanf("%d", &col);
		rowChar = input[0];
		rowInt = (int) (rowChar - MIN_CHAR_VALUE);
		deadShips = singleTurn(rowInt, col-1, managerBoard, toPrintBoard, boardSize,
								   shipsArray, deadShips);
	}
	freeAllSpace(toPrintBoard, managerBoard, shipsArray, boardSize);
	printf(GAME_OVER_MESSAGE);
	return 1;
}

