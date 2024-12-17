#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("There is missing arguments");
        exit(EXIT_SUCCESS);
    }

    for (int i = 0; i < 3; i++) {
        printf("%s\n", argv[i]);
    }

    exit(EXIT_SUCCESS);
}