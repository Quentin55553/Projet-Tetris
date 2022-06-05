#include "tetris.h"



void LowerBlocks(int player_array[GRID_SIZE][GRID_SIZE], int blocksTrackingArray[GRID_SIZE][GRID_SIZE], int row_stage) { // Procedure to remove a line when it is completed and lower all blocks above
    int row; // row_stage stands for full line index
    for (int i = 0; i < GRID_SIZE; i++) { // Each column
        row = row_stage;
        while(row > 0) {
            player_array[row][i] = player_array[row-1][i]; // Lower the block above
            player_array[row-1][i] = ' '; // Replace the block with blank
            blocksTrackingArray[row][i] = blocksTrackingArray[row-1][i]; // Lower the block color above
            blocksTrackingArray[row-1][1] = ' '; // Replace the block color with blank
            row--;
        }
    }
}



void CheckRows(int player_array[GRID_SIZE][GRID_SIZE], int blocksTrackingArray[GRID_SIZE][GRID_SIZE]) { // Procedure which scans the whole array and checks if a row is completed
    int row = 0, column = 0;
    while((row < GRID_SIZE) && (column < GRID_SIZE)) {
        if (player_array[row][column] != ' ') { // If there is no space, go to the next column
            column++;
        }
        else { // Otherwise skip line and go back to the first column
            row++;
            column = 0;
        }
        if (column == GRID_SIZE) { // If the line is completed, we call the procedure LowerBlocks() and tell the player he has scored points
            LowerBlocks(player_array, blocksTrackingArray, row);
            printf(BRIGHT_GREEN_BACKGROUND_COLOR "\nBRAVO, VOUS AVEZ REMPLI UNE LIGNE !" ENABLE_BOLD_TEXT " (" UNDERLINE_TEXT "+100 point\e[24m)" RESET_TEXT_FORMAT "\n");
            points += 100;
            row++;
            column = 0;
        }
    }
}



int collision(Block *block, int player_array[GRID_SIZE][GRID_SIZE], int random, int choice, int column) { // To make sure the tetros does not protrude from the grid 
    if ((block[random].blockShapes[choice].width + column) > GRID_SIZE) {
        return 1;
    } 
    return 0;
}



int MaxHeight(Block *block, int player_array[GRID_SIZE][GRID_SIZE], int column1, int column2, int last_row, int block_type, int choice, int anti_recursion) { // Function which returns the smallest gap between the bottom of the tetros and the highest block in the chosen column 
    int height_array[10] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10}; // Array to store the maximum heights for each column of the tetros
    int max_height, index = 0, check_blank, row, gap = 10;

    for (int i = column1; i <= column2; i++) { // For each column of the tetros
        check_blank = 0;
        max_height = 0;
        row = last_row; 
        while((row < 10) && (player_array[row][i] == ' ')) { // To count rows from the bottom of the tetros to the nearest block of the column
            row++;
            max_height++;
        }
        while(block[block_type].blockShapes[choice].shape[((last_row-1-check_blank)*block[block_type].blockShapes[choice].width) + i - column1] == ' ') { // To take into account each blank of the bottom of the tetros
            check_blank++;
            max_height++;
        }

        height_array[index] = max_height;
        index++;
    }

    int min = height_array[0]; // Arbitrary minimum for comparison
    for (int r = 0; r < GRID_SIZE; r++) { // To take the smallest value of the max_height array
        if (height_array[r] < min) {
            min = height_array[r];
        }
    }

    if (anti_recursion == 0) { // To prevent the function from calling itself infinitely
        gap = MaxHeight(block, player_array, column1, column2, 0, block_type, choice, 1);
    }

    if (block[block_type].blockShapes[choice].height > gap) { // To check if the player has lost (if there is not enough space for the tetros)
        printf(BRIGHT_RED_BACKGROUND_COLOR BRIGHT_WHITE_COLOR "\nVOUS AVEZ PERDU !" RESET_TEXT_FORMAT "\n");
        printf(BRIGHT_YELLOW_COLOR "\nVotre partie a été sauvegardée dans le fichier : " UNDERLINE_TEXT "scores.txt\n" RESET_TEXT_FORMAT);
        return -1; // To warn other functions that the player lost
    }

    return min;
}



int placeBlock(Block *block, int player_array[GRID_SIZE][GRID_SIZE], int blocksTrackingArray[GRID_SIZE][GRID_SIZE], int block_type, int choice, int column) { // To place tetros according to MaxHeight()

    int row = MaxHeight(block, player_array, column, column+block[block_type].blockShapes[choice].width-1, block[block_type].blockShapes[choice].height, block_type, choice, 0);

    if (row == -1) {
        return -1; // To warn other functions that the player lost
    }

    for (int i = 0; i < block[block_type].blockShapes[choice].height; i++) {
        for (int j = 0; j < block[block_type].blockShapes[choice].width; j++) {
            if (block[block_type].blockShapes[choice].shape[j+i*block[block_type].blockShapes[choice].width] != ' ') { // To prevent the tetros from replacing each other with spaces
                blocksTrackingArray[row][column+j] = block_type;
                player_array[row][column+j] = block[block_type].blockShapes[choice].shape[j+i*block[block_type].blockShapes[choice].width];
            }
        }
        row++;
    }
    CheckRows(player_array, blocksTrackingArray); // To check whether the play has completed a row
}



int printShape(Block *block, int random, int index, int range) { // Procedure that displays all the orientations of the tetros drawn at random in the terminal
    if (range == 1) { // To print a set of tetros in a row
        int maxheight_block_shapes = block[random].blockShapes[0].height;
        for (int i = 0; i < index; i++) {
            if (block[random].blockShapes[i].height > maxheight_block_shapes) {
                maxheight_block_shapes = block[random].blockShapes[i].height;
            }
        }
        for (int i = 0; i < maxheight_block_shapes+1; i++) {
            for (int k = 0; k < index; k++) {
                for (int j = 0; j < block[random].blockShapes[k].width; j++) {
                    if ((j+i*block[random].blockShapes[k].width) <= strlen(block[random].blockShapes[k].shape)-1) {
                        printf("%s%c" RESET_TEXT_FORMAT, block[random].color, block[random].blockShapes[k].shape[j+i*block[random].blockShapes[k].width]);
                    }
                    else {
                        printf(" ");
                    }
                }
                printf("     ");
            }
            printf("\n");
        }
    } else { // To only print one tetros
        for (int i = 0; i < block[random].blockShapes[index].height; i++) {
            for (int j = 0; j < block[random].blockShapes[index].width; j++) {
                printf("%s%c" RESET_TEXT_FORMAT,  block[random].color, block[random].blockShapes[index].shape[j+i*block[random].blockShapes[index].width]);
            }
            printf("\n");
        }
        printf(ENABLE_BLINKING_MODE BRIGHT_CYAN_COLOR "↑" RESET_TEXT_FORMAT RESET_TEXT_FORMAT);
        printf("\n");
    }
}



int MakeChoice(Block *block, int player_array[GRID_SIZE][GRID_SIZE], int blocksTrackingArray[GRID_SIZE][GRID_SIZE]) { // Ask the user for a set of informations concerning the placement of each tetros
    int random = rand() % BLOCK_NB, choice, nb_shapes = block[random].nbShapes;
    
    printf("Choisissez l'orientation de la pièce :\n");
    for (int z = 0; z < nb_shapes; z++) {
        printf(ENABLE_BOLD_TEXT " %d     " RESET_TEXT_FORMAT, z+1);
    }
    printf("\n");
    
    printShape(block, random, nb_shapes, 1);

    int time1_start = getTimeMicroSec();

    do { 
        scanf("%d", &choice);
        if (choice < 1 || choice > nb_shapes) {
            printf(RED_COLOR "\nAttention, il faut saisir un entier entre 1 et %d inclus.\n" RESET_TEXT_FORMAT, nb_shapes);
            BufferIsEmpty();
        }
    }while(choice < 1 || choice > nb_shapes);
    choice -= 1;

    int time1_stop = getTimeMicroSec();

    if ((time1_stop - time1_start) > 10000000) {
        choice = rand() % nb_shapes;
        printf(RED_COLOR "\nVous avez pris trop de temps à répondre (+10 s).\nUne forme a été sélectionnée au hasard (forme %d).\n" RESET_TEXT_FORMAT, choice+1);
    }

    printShape(block, random, choice, 0);


    char column;
    printf("\nChoisissez la colonne (la pièce tombera à l'endroit indiqué par " BRIGHT_CYAN_COLOR "↑" RESET_TEXT_FORMAT ") :\n");

    int time2_start = getTimeMicroSec();

    do {
        scanf(" %c", &column);
        if ((column >= (char)97) && (column <= 122)) {
            column -= 32;
        }
        if ((column < (char)65) || (column > (char)74)) {
            printf(RED_COLOR "\nAttention, il faut saisir une colonne entre A et J :\n" RESET_TEXT_FORMAT);
            BufferIsEmpty();
        }
        else if (collision(block, player_array, random, choice, column-65)) {
            printf(RED_COLOR "\nAttention, il n'y a pas assez d'espace entre la colonne %c et J, veuillez resaisir une colonne :\n" RESET_TEXT_FORMAT, column);
            BufferIsEmpty();
        }
    }while((column < (char)65) || (column > (char)74) || (collision(block, player_array, random, choice, column-65)));
   
    int time2_stop = getTimeMicroSec();


    if ((time2_stop - time2_start) > 10000000) {
        do {
            column = rand() % 11;
        }while(collision(block, player_array, random, choice, column-65));
        printf(RED_COLOR "\nVous avez pris trop de temps à répondre (+10 s).\nUne colonne a été sélectionnée au hasard (colonne %c).\n" RESET_TEXT_FORMAT, (char)(column+65));
        column += 65;
    }

    int place_block = placeBlock(block, player_array, blocksTrackingArray, random, choice, column-65);
    if (place_block == -1) { // If placeBlock() returned -1, it means that there is not enough space for the tetros, so we return -1 to tell main() function that the game is lost
        return -1;
    }
}
