#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define nbCharExit 4
#define msgHello "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define strExit "exit"
#define wCon 1
#define rCon 0

int main()
{
    write(wCon, msgHello, sizeof(msgHello)); //Envoie msgHello dans la console
    char* entree;
    while (strncmp(entree, strExit, nbCharExit)) { //Attends que l'utilisateur tape "exit"
        read(rCon, entree, sizeof(strExit));
    }
    exit(EXIT_SUCCESS);
}