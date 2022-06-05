#include "tetris.h"



void swapCharacters(char *array1, char *array2) { // Swap characters of two different string array
	for (int i = 0; i < 20; i++) {
		char tmp = array1[i];
		array1[i] = array2[i];
		array2[i] = tmp; 
	}
}



void sortHighscore(FILE *score_file){
    score_file = fopen("scores.txt","r");

    char cur_char = fgetc(score_file);
    int count_row = 0;
    while(((cur_char = fgetc(score_file)) != EOF)) { // To count rows of the score file
        if (cur_char == '\n') {
            count_row++;
        }
    }
    rewind(score_file);

    User *scores_array = malloc(sizeof(int) * sizeof(char) * 20 * (count_row/2));

    for (int i = 0; i < count_row/2; i++) {
        fscanf(score_file, "Joueur : %s Score : %d\n", scores_array[i].pseudo, &scores_array[i].score);
    }

    fclose(score_file);
    
    for (int noEtape = 0; noEtape < (count_row/2)-1; noEtape++) {
        int indiceMax = noEtape;
        for (int noCase = noEtape + 1; noCase < count_row/2; noCase++) {
            if (scores_array[noCase].score > scores_array[indiceMax].score) {
                indiceMax = noCase;
            }
        }
        if (indiceMax != noEtape) {
            int temp = scores_array[indiceMax].score;
            scores_array[indiceMax].score = scores_array[noEtape].score;
            scores_array[noEtape].score = temp;
            
            swapCharacters(scores_array[indiceMax].pseudo, scores_array[noEtape].pseudo);
        }
    }
    
    printf("\nVos 5 meilleures parties jusqu'à maintenant :\n");
    for (int i = 0; i < 5; i++) {
    	printf("%d Pseudo : %s\n", i+1, scores_array[i].pseudo);
    	printf("  Score : %d\n", scores_array[i].score);
    }
    printf("\n");
   	
}



void Highscore(User player){ // Procedure that displays the nickname and score of the player performing the game in a file
    FILE *score_file = NULL;
    if ((score_file = fopen("scores.txt", "r")) == NULL) { // If the file doesn't exist
        score_file = fopen("scores.txt","w");

    } 
    else { // If the file exists
        score_file = fopen("scores.txt", "a");

    }
    checkMallocFile(score_file);

    fprintf(score_file, "Joueur : %s\n", player.pseudo);
    fprintf(score_file, "Score : %d\n", player.score);

    fclose(score_file);
    
    sortHighscore(score_file);
}
