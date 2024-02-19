/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** stor.c
*/
#include "myftp.h"
#include <stdio.h>

void help_stor(client_t *client)
{
    dprintf(client->fd, "STOR <SP> <pathname> <CRLF> :"
    "Upload file from client to server\r\n");
}

void stor(char **words, client_t *client, enum Mode mode)
{
    if (mode == HELP) {
        help_stor(client);
        return;
    }
    printf("STOR\r\n");
    (void)words;
    (void)client;
}
