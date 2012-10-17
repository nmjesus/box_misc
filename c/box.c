#include <stdio.h>
#include <stdlib.h>
#include "lib/include/utils.h"

//socket
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#define MAX_CMD_LENGTH  20
#define QUIT            "quit"
#define BUFSIZE         1024

bool box_process_input(char cmd[MAX_CMD_LENGTH]) {
    if(str_cmp(cmd, QUIT)) {
        return FALSE;
    }
    return TRUE;
}

void box_read_input(int sockfd) {
    char cmd[MAX_CMD_LENGTH];

    do {
        fprintf(stdout, "box> ");
        fgets(cmd, MAX_CMD_LENGTH, stdin); // TODO: replace to fscanf
        send(sockfd, cmd, strlen(cmd),0);
    } while(box_process_input(cmd));
    shutdown(sockfd, 2);
}

int box_connect(char *host, int port) {
    struct hostent     *he;
    struct sockaddr_in  server;
    int                 sockfd;

    if((he = gethostbyname(host)) == NULL) {
        perror("error resolving hostname");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memcpy(&server.sin_addr, he->h_addr_list[0], he->h_length);
    server.sin_family   = AF_INET;
    server.sin_port     = htons(port);

    if(connect(sockfd, (struct sockaddr *) &server, sizeof(server)) == -1) {
        perror("error connecting");
        exit(1);
    }
    return sockfd;
}

int main(int argc, char **argv) {
    int sockfd = box_connect("192.168.1.64", 8082);
    box_read_input(sockfd);
    return 0;
}
