#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define nbrArg 3
#define errorArg "There is missing arguments"

int main(int argc, char** argv) {
    if (argc != nbrArg) { //Show an error because there is missing arguments
        printf(errorArg);
        exit(EXIT_SUCCESS);
    }

    for (int i = 0; i < nbrArg; i++) {
        printf("%s\n", argv[i]);
    }

    exit(EXIT_SUCCESS);
}