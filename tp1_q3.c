#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define msgHello "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define enseash "enseash % "
#define msgBye "Bye bye..."
#define msgCommand "Cette commande n'existe pas ou prends des arguments\n"
#define strExit "exit"
#define nbCharExit 4
#define wCon 1
#define rCon 0
#define readSize 128
#define bufferSize 64

void exitBye(char* input, int inputSize);
void executeCommand(int* statusAdd, char* input);

int main() {
    write(wCon, msgHello, sizeof(msgHello)); //Send msgHello to the console
    char input[readSize];
    int status;
    char buffer[bufferSize];
    int inputSize;
    while (1) {
        write(wCon, enseash, sizeof(enseash));
        inputSize = read(rCon, input, readSize);
        input[inputSize-1] = '\0'; //Add the delimiter to the end of the string

        exitBye(input, inputSize);

        executeCommand(&status, input);
    }
    exit(EXIT_SUCCESS);
}

void exitBye(char* input, int inputSize) {
    if (strcmp(input, strExit) == 0 || inputSize == 0) { //If the user typed "exit" or press Ctrl+D, close the shell
        write(wCon, msgBye, sizeof(msgBye));
        exit(EXIT_SUCCESS);
    }
}

void executeCommand(int* statusAdd, char* input) {
    if (fork() == 0) { //Execute the command in a child process
        if (execvp(input, (char*) NULL) == -1) {
            write(wCon, msgCommand, sizeof(msgCommand));
            exit(EXIT_FAILURE);
        }
    }
    wait(statusAdd);
}