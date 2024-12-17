#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

void addByteToBuffer(char buffer[256], int* offsetAdd, char byte);
void addStringToBuffer(char buffer[256], int* offsetAdd, char* message);

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("There is missing arguments");
        exit(EXIT_SUCCESS);
    }

    struct addrinfo hints;
    struct addrinfo *res;
    memset(&hints, 0, sizeof(struct addrinfo));

    getaddrinfo("www.ensea.fr", NULL, &hints, &res); //Utiliser le argv[1] au lieu de "localhost"
    char string_target[128] = {0};
    char string_server[128] = {0};
    getnameinfo(res->ai_addr, res->ai_addrlen, string_target, 128, string_server, 128, 1 | 2);

    /* struct addrinfo *current = res;
    while (current->ai_next != NULL) {
        printf("Found one result :\n");
        printf("\tai_family = %d\n", current->ai_family);
        printf("\tai_socktype = %d\n", current->ai_socktype);
        printf("\tai_protocol = %d\n", current->ai_protocol);
        if (current->ai_socktype == SOCK_DGRAM) {
            int sock = socket(current->ai_family, current->ai_socktype, current->ai_protocol);
            printf("Sock : %d\n", sock);
        }

        char string_target[128] = {0};
        char string_server[128] = {0};
        getnameinfo(current->ai_addr, current->ai_addrlen, string_target, 128, string_server, 128, 1 | 2);
        printf("\thost = %s\n", string_target);
        printf("\tserver = %s\n", string_server);    printf("Default result :\n");
    printf("\tai_family = %d\n", PF_INET);
    printf("\tai_socktype = %d\n", SOCK_DGRAM);
    printf("\tai_protocol = %d\n", 0);
    printf("Sock : %d\n", sock);

        current = current->ai_next;
    } */
    
    int sock = socket(PF_INET, SOCK_DGRAM, 17); //Ou IPPROTO_UDP en 3eme argument

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(69);
    inet_pton(AF_INET, string_target, &server_addr.sin_addr);
    //bind(sock, (const struct sockaddr *)&server_addr, sizeof(server_addr)); //pour le serveur uniquement

    unsigned char buffer[256];
    int offset = 0;
    addByteToBuffer(buffer, &offset, 0x00);
    addByteToBuffer(buffer, &offset, 0x01);
    addStringToBuffer(buffer, &offset, "zeros256"); //Ajouter \0 en + de l'octet 0 suivant ?
    addByteToBuffer(buffer, &offset, 0x00);
    addStringToBuffer(buffer, &offset, "octet"); //Ajouter \0 en + de l'octet 0 suivant ?
    addByteToBuffer(buffer, &offset, 0x00);
    int total_size = offset;

    sendto(sock, buffer, total_size, 0, (const struct sockaddr *) &server_addr, sizeof(server_addr));

    close(sock);
    exit(EXIT_SUCCESS);
}

void addByteToBuffer(char buffer[256], int* offsetAdd, char byte) {
    buffer[*offsetAdd] = byte;
    *offsetAdd++;
}

void addStringToBuffer(char buffer[256], int* offsetAdd, char* message) {
    int msg_len = strlen(message);
    memcpy(&buffer[*offsetAdd], message, msg_len);
    *offsetAdd += msg_len;
}