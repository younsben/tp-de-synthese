#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("There is missing arguments");
        exit(EXIT_SUCCESS);
    }

    struct addrinfo hints;
    struct addrinfo *res;
    memset(&hints, 0, sizeof(struct addrinfo));

    getaddrinfo("localhost", NULL, &hints, &res); //Utiliser le argv[1] au lieu de "localhost"
    char string_target[128] = {0};
    char string_server[128] = {0};
    getnameinfo(res->ai_addr, res->ai_addrlen, string_target, 128, string_server, 128, 1 | 2);

    printf("%s\n", string_target);

    exit(EXIT_SUCCESS);
}