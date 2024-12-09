#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define msgHello "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define enseash "enseash % "
#define msgBye "Bye bye..."
#define msgCommande "Cette commande n'existe pas ou prends des arguments\n"
#define strExit "exit"
#define nbCharExit 4
#define strFortune "fortune"
#define nbCharFortune 7
#define wCon 1
#define rCon 0
#define readSize 128
#define bufferSize 64

int main()
{
    write(wCon, msgHello, sizeof(msgHello)); //Envoie msgHello dans la console
    char entree[readSize];
    int status;
    char buffer[bufferSize];
    int inputSize;
    while (1) {
        write(wCon, enseash, sizeof(enseash));
        inputSize = read(rCon, entree, readSize);
        entree[inputSize-1] = '\0'; //On met le délimiteur de fin de chaine

        if (strcmp(entree, strExit) == 0) { //Si l'utilisateur tape exit, on break
            write(wCon, msgBye, sizeof(msgBye));
            exit(EXIT_SUCCESS);
        }

        if (fork() == 0) { //On exécute la commande dans un fils
            if (execvp(entree, (char*) NULL) == -1) {
                write(wCon, msgCommande, sizeof(msgCommande));
                exit(EXIT_FAILURE);
            }
        }
        wait(&status);
    }
    exit(EXIT_SUCCESS);
}