#include "tetris.h"



int main() {
    srand(time(NULL)); // To make the random functions (from stdlib.h) based on the current time

    points = 0;
    
    User player;

    int playerArray[GRID_SIZE][GRID_SIZE] = {};
    initArray(playerArray);

    int blocksTrackingArray[GRID_SIZE][GRID_SIZE] = {};
    initArray(blocksTrackingArray);

    Block blockArray[BLOCK_NB] = {};
    initBlocks(blockArray);

    do {
        printf("Entrer un pseudonyme :\n");
        scanf(" %s", player.pseudo);
        if ((strlen(player.pseudo) > 20)) {
            printf(RED_COLOR "\nAttention, le pseudo est trop long (20 caractères max.).\n\n" RESET_TEXT_FORMAT);
        }
    }while ((strlen(player.pseudo) > 20));


    int game;
    do {
        printf(PURPLE_COLOR "\nActuellement " UNDERLINE_TEXT "%d points" RESET_TEXT_FORMAT, points);
        print2Darray(blockArray, playerArray, blocksTrackingArray);
        game = MakeChoice(blockArray, playerArray, blocksTrackingArray);
    }while(game != -1);

    player.score = points;

    Highscore(player);


    return 0;
}
