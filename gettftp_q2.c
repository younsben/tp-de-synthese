#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define nbrArg 3
#define errorArg "There is missing arguments"
#define lengthString 128
#define IP "localhost"

int main(int argc, char** argv) {
    if (argc != nbrArg) {
        printf(errorArg);
        exit(EXIT_SUCCESS);
    }

    struct addrinfo hints;
    struct addrinfo *res;
    memset(&hints, 0, sizeof(struct addrinfo));

    getaddrinfo(IP, NULL, &hints, &res); //Utiliser le argv[1] au lieu de "localhost"
    char string_target[lengthString] = {0};
    char string_server[lengthString] = {0};
    getnameinfo(res->ai_addr, res->ai_addrlen, string_target, lengthString, string_server, lengthString, 1 | 2);

    printf("%s\n", string_target);

    exit(EXIT_SUCCESS);
}