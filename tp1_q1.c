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

int main() {
    write(wCon, msgHello, sizeof(msgHello)); //Send msgHello to the console
    char input[readSize];
    int inputSize;
    while (strcmp(input, strExit)) { //Wait for user to type "exit"
        write(wCon, enseash, sizeof(enseash));
        inputSize = read(rCon, input, readSize);
        input[inputSize-1] = '\0'; //Add the delimiter to the end of the string
    }
    exit(EXIT_SUCCESS);
}