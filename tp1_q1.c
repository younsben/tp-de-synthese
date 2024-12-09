#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define nbCharExit 4
#define msgHello "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define strExit "exit"

int main()
{
    write(1, msgHello, sizeof(msgHello));
    char* entree;
    while (strncmp(entree, strExit, nbCharExit)) { //Attends que l'utilisateur tape "exit"
        read(0, entree, sizeof(strExit));
    }
    exit(EXIT_SUCCESS);
}