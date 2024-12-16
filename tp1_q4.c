#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define msgHello "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define enseash "enseash % "
#define enseashExit "enseash [exit:%d] "
#define enseashSign "enseash [sign:%d] "
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
#define percentChar 37

int main()
{
    write(wCon, msgHello, sizeof(msgHello)); //Envoie msgHello dans la console
    char entree[readSize];
    int status = -2;
    char buffer[bufferSize];
    int inputSize;
    while (1) {
        if (status == -2) {
            write(wCon, enseash, sizeof(enseash));
        } else {
            if (WIFEXITED(status) == 1) {
                sprintf(buffer, enseashExit, WEXITSTATUS(status));
            }
            if (WIFSIGNALED(status) == 1) {
                sprintf(buffer, enseashSign, WTERMSIG(status));
            }
            strcat(buffer, "%");
            for (int i = 0; i < bufferSize; i++) { //On retire les caractères inutiles après le '%'
                if (buffer[i] == percentChar) {
                    for (int j = i+1; j < bufferSize; j++) {
                        buffer[j] = '\0';
                    }
                    break;
                }
            }
            write(wCon, buffer, sizeof(buffer));
        }
        inputSize = read(rCon, entree, readSize);
        entree[inputSize-1] = '\0'; //On met le délimiteur de fin de chaine

        if (strcmp(entree, strExit) == 0 || inputSize == 0) { //Si l'utilisateur tape exit ou si il a fait Ctrl+D, on exit
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