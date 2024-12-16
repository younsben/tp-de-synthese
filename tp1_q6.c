#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

#define msgHello "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define enseash "enseash % "
#define enseashExit "enseash [exit:%d|%dms] "
#define enseashSign "enseash [sign:%d|%dms] "
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
#define nbArgs 16
#define lengthArgs 16

int main()
{
    write(wCon, msgHello, sizeof(msgHello)); //Envoie msgHello dans la console
    char entree[readSize];
    char** args = malloc(nbArgs*sizeof(char*));
    int status = -2;
    char buffer[bufferSize];
    int inputSize;
    struct timespec ts1;
    struct timespec ts2;
    while (1) {
        if (status == -2) {
            write(wCon, enseash, sizeof(enseash));
        } else {
            clock_gettime(CLOCK_REALTIME, &ts2);
            if (WIFEXITED(status) == 1) {
                sprintf(buffer, enseashExit, WEXITSTATUS(status), (ts2.tv_nsec-ts1.tv_nsec)/1000000);
            }
            if (WIFSIGNALED(status) == 1) {
                sprintf(buffer, enseashSign, WTERMSIG(status), (ts2.tv_nsec-ts1.tv_nsec)/1000000);
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

        clock_gettime(CLOCK_REALTIME, &ts1);
        if (strcmp(entree, strExit) == 0 || inputSize == 0) { //Si l'utilisateur tape exit ou si il a fait Ctrl+D, on exit
            write(wCon, msgBye, sizeof(msgBye));
            exit(EXIT_SUCCESS);
        }

        int j = 0;
        int n = 0;
        args[0] = malloc(lengthArgs*sizeof(char));
        for (int i = 0; i < readSize; i++) { //Séparation des arguments
            if (entree[i] == '\0') {
                args[n][j] = '\0';
                args[n+1] = NULL;
                break;
            }
            if (entree[i] == ' ') {
                args[n][j] = '\0';
                args[n+1] = malloc(lengthArgs*sizeof(char));
                n++;
                j = 0;
            } else {
                args[n][j] = entree[i];
                j++;
            }
        }

        if (fork() == 0) { //On exécute la commande dans un fils
            if (execvp(args[0], args) == -1) {
                write(wCon, msgCommande, sizeof(msgCommande));
                exit(EXIT_FAILURE);
            }
        }
        wait(&status);
    }
    exit(EXIT_SUCCESS);
}