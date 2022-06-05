#include "tetris.h"



unsigned long getTimeMicroSec() { // Function that returns the current time
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (1000000 * tv.tv_sec) + tv.tv_usec;
}



void checkMallocFile(FILE *file) { // To check whether problems occured with the file 
    if(file == NULL){
        printf(RED_COLOR "Erreur lors de l'ouverture du fichier.\n" RESET_TEXT_FORMAT);
        printf(RED_COLOR "Code d'erreur : %d \n" RESET_TEXT_FORMAT, errno);
        printf(RED_COLOR "Message d'erreur : %s \n" RESET_TEXT_FORMAT, strerror(errno));
        exit(1); // Exits the program. exit() function contained in the <stdlib.h> module.
    }
}



void checkMalloc(char *tab) { // To check whether problems occured when creating array of shapes
    if (tab == NULL) {
        printf(RED_COLOR "Erreur d'allocation mémoire.\n" RESET_TEXT_FORMAT);
        printf(RED_COLOR "Code d'erreur : %d \n" RESET_TEXT_FORMAT, errno);
        printf(RED_COLOR "Message d'erreur : %s \n" RESET_TEXT_FORMAT, strerror(errno));
        exit(1); // Exits the program. exit() function contained in the <stdlib.h> module.
    }
}



void checkMallocBlockProperties(BlockProperties *tab) { // To check whether problems occured with the array of shapes orientations
    if (tab == NULL) {
        printf(RED_COLOR "Erreur d'allocation mémoire.\n" RESET_TEXT_FORMAT);
        printf(RED_COLOR "Code d'erreur : %d \n" RESET_TEXT_FORMAT, errno);
        printf(RED_COLOR "Message d'erreur : %s \n" RESET_TEXT_FORMAT, strerror(errno));
        exit(1); // Exits the program. exit() function contained in the <stdlib.h> module.
    }
}



void BufferIsEmpty() { // To clear the buffer
    int c = 0;
    while(c != '\n' && c!= EOF) {
        c = getchar(); // getchar() used to go to the next character
    }
}
