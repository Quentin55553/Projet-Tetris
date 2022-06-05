#include "tetris.h"



void print2Darray(Block *block, int array[GRID_SIZE][GRID_SIZE], int blocksTrackingArray[GRID_SIZE][GRID_SIZE]) { // To create the game array 
    printf("\nVoici votre grille :\n ");
    for (int q = 0; q < GRID_SIZE; q++) {
        printf(ENABLE_BOLD_TEXT "%c " RESET_TEXT_FORMAT , q+65);
    }
    printf("\n");

    for (int i = 0; i < GRID_SIZE; i++) { // Each row
        for (int j = 0; j < GRID_SIZE; j++) { // Each column
            printf(ENABLE_BOLD_TEXT "|" RESET_TEXT_FORMAT);
            int block_type = blocksTrackingArray[i][j];
            if (block_type != 32) { // To check whether there is not blank
                printf("%s%c" RESET_TEXT_FORMAT, block[block_type].color, array[i][j]); // To print the block with color
            } else {
                printf("%c", array[i][j]);
            }
        }
        printf(ENABLE_BOLD_TEXT "|\n" RESET_TEXT_FORMAT);
    }
    printf("\n");
}



void initArray(int array[GRID_SIZE][GRID_SIZE]) { // Procedure for creating a game array filled with empty cells.
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            array[i][j] = 32; // To fill the array with blank
        }
    }
}



void initBlocks(Block *blocks) { // Procedure to store each tetros with all its orientations and colors
    blocks[0].nbShapes = 4;
    blocks[0].blockShapes = malloc(blocks[0].nbShapes * sizeof(BlockProperties));
    checkMallocBlockProperties(blocks[0].blockShapes);
    blocks[0].color = malloc(strlen(BRIGHT_RED_COLOR) * sizeof(char));
    checkMalloc(blocks[0].color);
    blocks[0].color = BRIGHT_RED_COLOR;
    // 1
    blocks[0].blockShapes[0].height = 2;
    blocks[0].blockShapes[0].width = 3;
    blocks[0].blockShapes[0].shape = malloc(blocks[0].blockShapes[0].height * blocks[0].blockShapes[0].width * sizeof(char));
    checkMalloc(blocks[0].blockShapes[0].shape);
    blocks[0].blockShapes[0].shape = " @ @@@";
    //" @ "
    //"@@@"
    
    // 2
    blocks[0].blockShapes[1].height = 2;
    blocks[0].blockShapes[1].width = 3;
    blocks[0].blockShapes[1].shape = malloc(blocks[0].blockShapes[1].height * blocks[0].blockShapes[1].width * sizeof(char));
    checkMalloc(blocks[0].blockShapes[1].shape);
    blocks[0].blockShapes[1].shape = "@@@ @ ";
    //"@@@"
    //" @ "

    // 3
    blocks[0].blockShapes[2].height = 3;
    blocks[0].blockShapes[2].width = 2;
    blocks[0].blockShapes[2].shape = malloc(blocks[0].blockShapes[2].height * blocks[0].blockShapes[2].width * sizeof(char));
    checkMalloc(blocks[0].blockShapes[2].shape);
    blocks[0].blockShapes[2].shape = "@ @@@ ";
    //"@ "
    //"@@"
    //"@ "

    // 4
    blocks[0].blockShapes[3].height = 3;
    blocks[0].blockShapes[3].width = 2;
    blocks[0].blockShapes[3].shape = malloc(blocks[0].blockShapes[3].height * blocks[0].blockShapes[3].width * sizeof(char));
    checkMalloc(blocks[0].blockShapes[3].shape);
    blocks[0].blockShapes[3].shape = " @@@ @";
    //" @"
    //"@@"
    //" @"
    
    /////////////////////////////////////////////////////
    blocks[1].nbShapes = 2;
    blocks[1].blockShapes = malloc(blocks[1].nbShapes * sizeof(BlockProperties));
    checkMallocBlockProperties(blocks[1].blockShapes);
    blocks[1].color = malloc(strlen(BRIGHT_YELLOW_COLOR) * sizeof(char));
    checkMalloc(blocks[1].color);
    blocks[1].color = BRIGHT_YELLOW_COLOR;
    // 1
    blocks[1].blockShapes[0].height = 4;
    blocks[1].blockShapes[0].width = 1;
    blocks[1].blockShapes[0].shape = malloc(blocks[1].blockShapes[0].height * blocks[1].blockShapes[0].width * sizeof(char));
    checkMalloc(blocks[1].blockShapes[0].shape);
    blocks[1].blockShapes[0].shape = "@@@@";
    //"@"
    //"@"
    //"@"
    //"@"
    
    // 2
    blocks[1].blockShapes[1].height = 1;
    blocks[1].blockShapes[1].width = 4;
    blocks[1].blockShapes[1].shape = malloc(blocks[1].blockShapes[1].height * blocks[1].blockShapes[1].width * sizeof(char));
    checkMalloc(blocks[1].blockShapes[1].shape);
    blocks[1].blockShapes[1].shape = "@@@@";
    //"@@@@"
    
    /////////////////////////////////////////////////////
    blocks[2].nbShapes = 4;
    blocks[2].blockShapes = malloc(blocks[2].nbShapes * sizeof(BlockProperties));
    checkMallocBlockProperties(blocks[2].blockShapes);
    blocks[2].color = malloc(strlen(BRIGHT_GREEN_COLOR) * sizeof(char));
    checkMalloc(blocks[2].color);
    blocks[2].color = BRIGHT_GREEN_COLOR;
    // 1
    blocks[2].blockShapes[0].height = 2;
    blocks[2].blockShapes[0].width = 3;
    blocks[2].blockShapes[0].shape = malloc(blocks[2].blockShapes[0].height * blocks[2].blockShapes[0].width * sizeof(char));
    checkMalloc(blocks[2].blockShapes[0].shape);
    blocks[2].blockShapes[0].shape = "@  @@@";
    //"@  "
    //"@@@"
    
    // 2
    blocks[2].blockShapes[1].height = 3;
    blocks[2].blockShapes[1].width = 2;
    blocks[2].blockShapes[1].shape = malloc(blocks[2].blockShapes[1].height * blocks[2].blockShapes[1].width * sizeof(char));
    checkMalloc(blocks[2].blockShapes[1].shape);
    blocks[2].blockShapes[1].shape = " @ @@@";
    //" @"
    //" @"
    //"@@"
    
    // 3
    blocks[2].blockShapes[2].height = 2;
    blocks[2].blockShapes[2].width = 3;
    blocks[2].blockShapes[2].shape = malloc(blocks[2].blockShapes[2].height * blocks[2].blockShapes[2].width * sizeof(char));
    checkMalloc(blocks[2].blockShapes[2].shape);
    blocks[2].blockShapes[2].shape = "@@@  @";
    //"@@@"
    //"  @"

    // 4
    blocks[2].blockShapes[3].height = 3;
    blocks[2].blockShapes[3].width = 2;
    blocks[2].blockShapes[3].shape = malloc(blocks[2].blockShapes[3].height * blocks[2].blockShapes[3].width * sizeof(char));
    checkMalloc(blocks[2].blockShapes[3].shape);
    blocks[2].blockShapes[3].shape = "@@@ @ ";
    //"@@"
    //"@ "
    //"@ "

    //////////////////////////////////////////////////////
    blocks[3].nbShapes = 4;
    blocks[3].blockShapes = malloc(blocks[3].nbShapes * sizeof(BlockProperties));
    checkMallocBlockProperties(blocks[3].blockShapes);
    blocks[3].color = malloc(strlen(BRIGHT_CYAN_COLOR) * sizeof(char));
    checkMalloc(blocks[3].color);
    blocks[3].color = BRIGHT_CYAN_COLOR;
    // 1
    blocks[3].blockShapes[0].height = 2;
    blocks[3].blockShapes[0].width = 3;
    blocks[3].blockShapes[0].shape = malloc(blocks[3].blockShapes[0].height * blocks[3].blockShapes[0].width * sizeof(char));
    checkMalloc(blocks[3].blockShapes[0].shape);
    blocks[3].blockShapes[0].shape = "  @@@@";
    //"  @"
    //"@@@"

    // 2
    blocks[3].blockShapes[1].height = 3;
    blocks[3].blockShapes[1].width = 2;
    blocks[3].blockShapes[1].shape = malloc(blocks[3].blockShapes[1].height * blocks[3].blockShapes[1].width * sizeof(char));
    checkMalloc(blocks[3].blockShapes[1].shape);
    blocks[3].blockShapes[1].shape = "@@ @ @";
    //"@@"
    //" @"
    //" @"
    
    // 3
    blocks[3].blockShapes[2].height = 2;
    blocks[3].blockShapes[2].width = 3;
    blocks[3].blockShapes[2].shape = malloc(blocks[3].blockShapes[2].height * blocks[3].blockShapes[2].width * sizeof(char));
    checkMalloc(blocks[3].blockShapes[2].shape);
    blocks[3].blockShapes[2].shape = "@@@@  ";
    //"@@@"
    //"@  "

    // 4
    blocks[3].blockShapes[3].height = 3;
    blocks[3].blockShapes[3].width = 2;
    blocks[3].blockShapes[3].shape = malloc(blocks[3].blockShapes[3].height * blocks[3].blockShapes[3].width * sizeof(char));
    checkMalloc(blocks[3].blockShapes[3].shape);
    blocks[3].blockShapes[3].shape = "@ @ @@";
    //"@ "
    //"@ "
    //"@@"

    //////////////////////////////////////////////////////
    blocks[4].nbShapes = 2;
    blocks[4].blockShapes = malloc(blocks[4].nbShapes * sizeof(BlockProperties));
    checkMallocBlockProperties(blocks[4].blockShapes);
    blocks[4].color = malloc(strlen(BRIGHT_WHITE_COLOR) * sizeof(char));
    checkMalloc(blocks[4].color);
    blocks[4].color = BRIGHT_WHITE_COLOR;
    // 1
    blocks[4].blockShapes[0].height = 2;
    blocks[4].blockShapes[0].width = 3;
    blocks[4].blockShapes[0].shape = malloc(blocks[4].blockShapes[0].height * blocks[4].blockShapes[0].width * sizeof(char));
    checkMalloc(blocks[4].blockShapes[0].shape);
    blocks[4].blockShapes[0].shape = " @@@@ ";
    //" @@"
    //"@@ "

    // 2
    blocks[4].blockShapes[1].height = 3;
    blocks[4].blockShapes[1].width = 2;
    blocks[4].blockShapes[1].shape = malloc(blocks[4].blockShapes[1].height * blocks[4].blockShapes[1].width * sizeof(char));
    checkMalloc(blocks[4].blockShapes[1].shape);
    blocks[4].blockShapes[1].shape = "@ @@ @";
    //"@ "
    //"@@"
    //" @"

    //////////////////////////////////////////////////////
    blocks[5].nbShapes = 2;
    blocks[5].blockShapes = malloc(blocks[5].nbShapes * sizeof(BlockProperties));
    checkMallocBlockProperties(blocks[5].blockShapes);
    blocks[5].color = malloc(strlen(BRIGHT_PURPLE_COLOR) * sizeof(char));
    checkMalloc(blocks[5].color);
    blocks[5].color = BRIGHT_PURPLE_COLOR;
    // 1
    blocks[5].blockShapes[0].height = 2;
    blocks[5].blockShapes[0].width = 3;
    blocks[5].blockShapes[0].shape = malloc(blocks[5].blockShapes[0].height * blocks[5].blockShapes[0].width * sizeof(char));
    checkMalloc(blocks[5].blockShapes[0].shape);
    blocks[5].blockShapes[0].shape = "@@  @@";
    //"@@ "
    //" @@"

    // 2
    blocks[5].blockShapes[1].height = 3;
    blocks[5].blockShapes[1].width = 2;
    blocks[5].blockShapes[1].shape = malloc(blocks[5].blockShapes[1].height * blocks[5].blockShapes[1].width * sizeof(char));
    checkMalloc(blocks[5].blockShapes[1].shape);
    blocks[5].blockShapes[1].shape = " @@@@ ";
    //" @"
    //"@@"
    //"@ "

    //////////////////////////////////////////////////////
    blocks[6].nbShapes = 1;
    blocks[6].blockShapes = malloc(blocks[6].nbShapes * sizeof(BlockProperties));
    checkMallocBlockProperties(blocks[6].blockShapes);
    blocks[6].color = malloc(strlen(BRIGHT_BLUE_COLOR) * sizeof(char));
    checkMalloc(blocks[6].color);
    blocks[6].color = BRIGHT_BLUE_COLOR;
    // 1
    blocks[6].blockShapes[0].height = 2;
    blocks[6].blockShapes[0].width = 2;
    blocks[6].blockShapes[0].shape = malloc(blocks[6].blockShapes[0].height * blocks[6].blockShapes[0].width * sizeof(char));
    checkMalloc(blocks[6].blockShapes[0].shape);
    blocks[6].blockShapes[0].shape = "@@@@";
    //"@@"
    //"@@"
}
