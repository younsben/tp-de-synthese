#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define msgHello "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define enseash "enseash % "
#define strExit "exit"
#define nbCharExit 4
#define wCon 1
#define rCon 0
#define readSize 128

int main()
{
    write(wCon, msgHello, sizeof(msgHello)); //Envoie msgHello dans la console
    char entree[readSize];
    int inputSize;
    while (strcmp(entree, strExit)) { //Attends que l'utilisateur tape "exit"
        write(wCon, enseash, sizeof(enseash));
        inputSize = read(rCon, entree, readSize);
        entree[inputSize-1] = '\0'; //On met le délimiteur de fin de chaine
    }
    exit(EXIT_SUCCESS);
}