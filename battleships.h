#ifndef BATTLESHIPS_H_
#define BATTLESHIPS_H_

// -------------------------- const definitions -------------------------

/**
 * @def SHIPS_NUM 5
 * @brief the number of ships participating in the game.
 */
#define SHIPS_NUM 5

// --------------------------  structs -------------------------


/**
 * a structure describing a ship in the game. includes the following attributes:
 * row - the row index of the ship on the board.
 * col - the column index of the ship on the board.
 * angle - 0 for vertical, 1 for horizontal.
 * size - the length of the ship.
 * lives - the number of cells on the board that were not hit. (the initialization of lives is
 * the size of the ship).
 */
typedef struct Ship Ship;

//----------------- functions--------------------------

/**
 * @brief Receives a size and creates a char board initialized to empty cells.
 * @param size - the board size
 * @return the new board initialized.
 */
char **initialBoard(int size);


/**
 * @brief The function receives a new ship needed to be located in the board and the manager
 * board holding all the other ships taken Coordinates. The function picks a random value for the
 * ship, validate it, and mark it on the manager board.
 * @param newShip a pointer to the new ship needed to be placed.
 * @param boardSize the boardSize (as the height and width are equal)
 * @param managerBoard the manager board in the game (saving all the ships locations).
 * @param index the index of the ship in the ships array.
 * */
void placeShip(Ship *newShip, int boardSize, char **managerBoard, int index);

/**
* @brief The function receives a the board size and the manager board holding all the other ships
* taken Coordinates.
* The function builds and locate all the ships in the game and holds them in an array.
* The function return the array of ships created.
* @param boardSize the boardSize (as the height and width are equal)
* @param managerBoard the manager board in the game (saving all the ships locations).
* @return the function return the array of ships created.
* */
Ship *shipFactory(int boardSize, char **managerBoard);

/**
 * @brief The function receives a  board size and a pointer to the board and print it.
 * @param board the board to print.
 * @param boardSize the boardSize.
 * */
void printBoard( char **board, int boardSize);


/**
 * The function handles a case when the user hit a ship on the board. The function updates the
 * hit ship lives and if the ship is dead it will print the correct message and update the counter
 * of the dead ships in the game.
 * @param row The row received from the user.
 * @param col The column received from the user.
 * @param managerBoard The manager board in the game.(saving all the ships locations).
 * @param toPrintBoard The board represented to the user during the game.
 * @param boardSize The boardSize.
 * @param ships An array holding all the ships participating in the game.
 * @param deadShips The counter counting the number of dead ships in the game.
 * @return The updated number of dead ships in the game according to the last turn.
 */
int hit(int row, int col, char **managerBoard, char **toPrintBoard, Ship *ships, int deadShips);


/**
 * The function run a whole single turn in the game, receiving the user move, and validates it.
 * @param row The row received from the user.
 * @param col The column received from the user.
 * @param managerBoard The manager board in the game (saving all the ships locations).
 * @param toPrintBoard The board represented to the user during the game.
 * @param boardSize The boardSize.
 * @param ships An array holding all the ships participating in the game.
 * @param deadShips The counter counting the number of dead ships in the game.
 * @return The updated number of dead ships in the game according to the last turn.
 */
int singleTurn(int row, int col, char **managerBoard, char **toPrintBoard, int boardSize,
			   Ship *ships, int deadShips);

/**
 * The function free all the space taken by the program using the free function.
 * @param toPrintBoard The board represented to the user during the game.
 * @param managerBoard The manager board in the game (saving all the ships locations).
 * @param shipsArray An array holding all the ships participating in the game.
 * @param boardSize  The boardSize.
 */
void freeAllSpace(char **toPrintBoard, char **managerBoard, Ship *shipsArray, int boardSize);

#endif /* BATTLESHIPS_H_ */