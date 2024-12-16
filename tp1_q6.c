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
#define msgCommand "Cette commande n'existe pas ou prends des arguments\n"
#define strExit "exit"
#define nbCharExit 4
#define wCon 1
#define rCon 0
#define readSize 128
#define bufferSize 64
#define percentChar 37
#define nbArgs 16
#define lengthArgs 16

void exitBye(char* input, int inputSize);
void decodeAndExecuteCommand(int* statusAdd, char* input, struct timespec* ts1Add, char** args);

int main() {
    write(wCon, msgHello, sizeof(msgHello)); //Send msgHello to the console
    char input[readSize];
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
            for (int i = 0; i < bufferSize; i++) { //Remove useless caractère after "%"
                if (buffer[i] == percentChar) {
                    for (int j = i+1; j < bufferSize; j++) {
                        buffer[j] = '\0';
                    }
                    break;
                }
            }
            write(wCon, buffer, sizeof(buffer));
        }
        inputSize = read(rCon, input, readSize);
        input[inputSize-1] = '\0'; //Add the delimiter to the end of the string

        exitBye(input, inputSize);

        decodeAndExecuteCommand(&status, input, &ts1, args);
    }
    exit(EXIT_SUCCESS);
}

void exitBye(char* input, int inputSize) {
    if (strcmp(input, strExit) == 0 || inputSize == 0) { //If the user typed "exit" or press Ctrl+D, close the shell
        write(wCon, msgBye, sizeof(msgBye));
        exit(EXIT_SUCCESS);
    }
}

void decodeAndExecuteCommand(int* statusAdd, char* input, struct timespec* ts1Add, char** args) {
    int j = 0;
    int n = 0;
    args[0] = malloc(lengthArgs*sizeof(char));
    for (int i = 0; i < readSize; i++) { //Split the arguments
        if (input[i] == '\0') {
            args[n][j] = '\0';
            args[n+1] = NULL;
            break;
        }
        if (input[i] == ' ') {
            args[n][j] = '\0';
            args[n+1] = malloc(lengthArgs*sizeof(char));
            n++;
            j = 0;
        } else {
            args[n][j] = input[i];
            j++;
        }
    }
    clock_gettime(CLOCK_REALTIME, ts1Add);
    if (fork() == 0) { //Execute the command in a child process
        if (execvp(args[0], args) == -1) {
            write(wCon, msgCommand, sizeof(msgCommand));
            exit(EXIT_FAILURE);
        }
    }
    wait(statusAdd);
}