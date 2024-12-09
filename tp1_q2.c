#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define msgHello "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define strExit "exit"
#define nbCharExit 4
#define strFortune "fortune"
#define nbCharFortune 7
#define wCon 1
#define rCon 0
#define readSize 128

int main()
{
    write(wCon, msgHello, sizeof(msgHello)); //Envoie msgHello dans la console
    char* entree;
    while (1) {
        read(rCon, entree, readSize);
        if (strncmp(entree, strExit, nbCharExit) == 0) { //Si l'utilisateur tape exit, on break
            break;
        } else if (strncmp(entree, strFortune, nbCharFortune) == 0) { //S'il tape fortune, on execute fortune dans un fils
            if (fork() == 0) {
                execlp("fortune", "fortune", (char*) NULL);
            }
        }
    }
    exit(EXIT_SUCCESS);
}