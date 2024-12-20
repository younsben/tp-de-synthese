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

int main(int argc, char** argv) {
    if (argc != nbrArg ) { //Show an error because there is missing arguments
        printf(errorArg );
        exit(EXIT_SUCCESS);
    }

    struct addrinfo hints;
    struct addrinfo *res;
    memset(&hints, 0, sizeof(struct addrinfo));

    getaddrinfo(argv[1] , NULL, &hints, &res);
    char string_target[lengthString] = {0};
    char string_server[lengthString] = {0};
    getnameinfo(res->ai_addr, res->ai_addrlen, string_target, lengthString, string_server, lengthString, 1 | 2);

    int sock = socket(PF_INET, SOCK_DGRAM, 0); //PF_INET for IPv4 et SOCK_DGRAM for UDP

    printf("%d\n", sock);

    close(sock);

    exit(EXIT_SUCCESS);
}