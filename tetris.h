#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>

#define BRIGHT_RED_COLOR "\e[31;1m" // Colors used for the shapes
#define BRIGHT_YELLOW_COLOR "\e[33;1m"
#define BRIGHT_GREEN_COLOR "\e[32;1m"
#define BRIGHT_CYAN_COLOR "\e[36;1m" // Also used for the indicator arrow for positioning
#define BRIGHT_BLUE_COLOR "\e[34;1m"
#define BRIGHT_PURPLE_COLOR "\e[35;1m"
#define BRIGHT_WHITE_COLOR "\e[37;1m"
#define BRIGHT_RED_BACKGROUND_COLOR "\e[48;5;196m"
#define BRIGHT_GREEN_BACKGROUND_COLOR "\e[48;5;28m"
#define PURPLE_COLOR "\e[38;5;219m"
#define RED_COLOR "\e[31m" // For error messages
#define ENABLE_BOLD_TEXT "\e[1m" // For bold text
#define ENABLE_BLINKING_MODE "\e[5m" // For flashing text
#define UNDERLINE_TEXT "\e[4m"
#define RESET_TEXT_FORMAT "\e[0m" // To reset all changes made to the text

#define GRID_SIZE 10 // Constant for the table size
#define BLOCK_NB 7 // Constant for the tetros number

int points;

typedef struct{ // Structure for user informations
    char pseudo[20];
    int score;
}User;


typedef struct { // Structure for tetros properties 
    int height;
    int width;
    char *shape;
}BlockProperties;


typedef struct { // Structure for tetros orientations 
    int nbShapes;
    char *color;
    BlockProperties *blockShapes;
}Block;

void checkMallocFile(FILE *file); // To check whether problems occured with the file

void swapCharacters(char *array1, char *array2); // Swap characters of two different string array

void checkMalloc(char *tab); // To check whether problems occured when creating array of shapes

void checkMallocBlockProperties(BlockProperties *tab); // To check whether problems occured with the array of shapes orientations

void sortHighscore(FILE *score_file);

void Highscore(User player); // Procedure that displays the nickname and score of the player performing the game in a file

void BufferIsEmpty(); // To clear the buffer

void print2Darray(Block *block, int array[GRID_SIZE][GRID_SIZE], int blocksTrackingArray[GRID_SIZE][GRID_SIZE]); // To create the game array 

void initArray(int array[GRID_SIZE][GRID_SIZE]); // Procedure for creating a game array filled with empty cells.

void initBlocks(Block *blocks); // Procedure to store each tetros with all its orientations and colors

unsigned long getTimeMicroSec(); // Function that returns the current time

void LowerBlocks(int player_array[GRID_SIZE][GRID_SIZE], int blocksTrackingArray[GRID_SIZE][GRID_SIZE], int row_stage); // Procedure to remove a line when it is completed and lower all blocks above

void CheckRows(int player_array[GRID_SIZE][GRID_SIZE], int blocksTrackingArray[GRID_SIZE][GRID_SIZE]); // Procedure which scans the whole array and checks if a row is completed

int collision(Block *block, int player_array[GRID_SIZE][GRID_SIZE], int random, int choice, int column); // To make sure the tetros does not protrude from the grid 

int MaxHeight(Block *block, int player_array[GRID_SIZE][GRID_SIZE], int column1, int column2, int last_row, int block_type, int choice, int anti_recursion); // Function which returns the smallest gap between the bottom of the tetros and the highest block in the chosen column 

int placeBlock(Block *block, int player_array[GRID_SIZE][GRID_SIZE], int blocksTrackingArray[GRID_SIZE][GRID_SIZE], int block_type, int choice, int column); // To place tetros according to MaxHeight()

int printShape(Block *block, int random, int index, int range); // Procedure that displays all the orientations of the tetros drawn at random in the terminal

int MakeChoice(Block *block, int player_array[GRID_SIZE][GRID_SIZE], int blocksTrackingArray[GRID_SIZE][GRID_SIZE]); // Ask the user for a set of informations concerning the placement of each tetros
