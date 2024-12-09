#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define nbCharExit 4
#define msgHello "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"

int main()
{
    write(1, msgHello, sizeof(msgHello));
    char* entree;
    char* strExit = "exit";
    while (strncmp(entree, strExit, nbCharExit)) {
        read(0, entree, sizeof(strExit));
    }
    exit(EXIT_SUCCESS);
}