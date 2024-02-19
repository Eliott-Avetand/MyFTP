/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** passv.c
*/
#include "myftp.h"
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

void help_pasv(client_t *client)
{
    dprintf(client->fd, "PASV <CRLF> :"
    "Enable 'passive' mode for data transfer\r\n");
}

void print_pasv(int port, char *ip, client_t *client)
{
    dprintf(client->fd,
    "227 Entering Passive Mode (%s, %d, %d).\r\n",
    ip, port / 256, port % 256);
}

void configure_data_server(client_t *client)
{
    int data_fd;
    struct sockaddr_in server;
    socklen_t len = sizeof(struct sockaddr_in);

    data_fd = create_socket();
    server.sin_port = htons(0);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_family = AF_INET;
    if (bind(data_fd, (struct sockaddr *)&server, len) == -1) {
        fprintf(stderr, "Socket bind failed...\r\n");
        exit(84);
    }
    if (listen(data_fd, 50) == -1) {
        fprintf(stderr, "Listen failed...\r\n");
        exit(84);
    }
    getsockname(data_fd, (struct sockaddr *)&server, &len);
    client->data_fd = data_fd;
    print_pasv(ntohs(server.sin_port), inet_ntoa(server.sin_addr), client);
}

void pasv(char **words, client_t *client, enum Mode mode)
{
    if (mode == HELP) {
        help_pasv(client);
        return;
    }
    if (double_array_len(words) != 1) {
        dprintf(client->fd,
        "501 Syntax error in parameters or arguments.\r\n");
    } else {
        client->mode = PASSIVE;
        configure_data_server(client);
    }
}
