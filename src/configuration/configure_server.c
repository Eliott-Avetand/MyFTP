/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** socket.c
*/
#include "myftp.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int create_socket(void)
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sfd == -1) {
        fprintf(stderr, "Socket creation failed...\r\n");
        exit(84);
    }
    return sfd;
}

void configure_socket(int sfd, int port)
{
    struct sockaddr_in server;

    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if (bind(sfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        fprintf(stderr, "Socket bind failed...\r\n");
        exit(84);
    }
    if (listen(sfd, 50) == -1) {
        fprintf(stderr, "Listen failed...\r\n");
        exit(84);
    }
}
