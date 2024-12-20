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
#define portLocalServer 1069
#define bufferSize 256
#define communicationMode "octet"

void addByteToBuffer(char buffer[256], int* offsetAdd, char byte);
void addStringToBuffer(char buffer[256], int* offsetAdd, char* message);

int main(int argc, char** argv) {
    if (argc != nbrArg) { //Show an error because there is missing arguments
        printf(errorArg);
        exit(EXIT_SUCCESS);
    }

    struct addrinfo hints;
    struct addrinfo *res;
    memset(&hints, 0, sizeof(struct addrinfo));

    getaddrinfo(argv[1], NULL, &hints, &res);
    char string_target[lengthString] = {0};
    char string_server[lengthString] = {0};
    getnameinfo(res->ai_addr, res->ai_addrlen, string_target, lengthString, string_server, lengthString, 1 | 2);
    
    int sock = socket(PF_INET, SOCK_DGRAM, 0); //PF_INET for IPv4 et SOCK_DGRAM for UDP

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(portLocalServer);
    inet_pton(AF_INET, string_target, &server_addr.sin_addr);

    unsigned char buffer[bufferSize];
    int offset = 0;
    addByteToBuffer(buffer, &offset, 0x00);
    addByteToBuffer(buffer, &offset, 0x01);
    addStringToBuffer(buffer, &offset, argv[2]);
    addByteToBuffer(buffer, &offset, 0x00);
    addStringToBuffer(buffer, &offset, communicationMode);
    addByteToBuffer(buffer, &offset, 0x00);
    int total_size = offset;

    sendto(sock, buffer, total_size, 0, (const struct sockaddr *) &server_addr, sizeof(server_addr)); //Send our buffer to the server on port 1069

    close(sock);
    exit(EXIT_SUCCESS);
}

void addByteToBuffer(char buffer[bufferSize], int* offsetAdd, char byte) {
    buffer[*offsetAdd] = byte;
    *offsetAdd++;
}

void addStringToBuffer(char buffer[bufferSize], int* offsetAdd, char* message) {
    int msg_len = strlen(message);
    memcpy(&buffer[*offsetAdd], message, msg_len);
    *offsetAdd += msg_len;
}