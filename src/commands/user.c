/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** user.c
*/
#include "myftp.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void help_user(client_t *client)
{
    dprintf(client->fd, "USER <SP> <username> <CRLF> :"
    "Specify user for authentication\r\n");
}

void user(char **words, client_t *client, enum Mode mode)
{
    if (mode == HELP) {
        help_user(client);
        return;
    }
    if (double_array_len(words) != 2)
        dprintf(client->fd,
        "501 Syntax error in parameters or arguments.\r\n");
    else {
        free(client->username);
        client->username = strdup(words[1]);
        if (client->password &&
        strcmp(client->username, "Anonymous") == 0) {
            dprintf(client->fd, "230 User logged in, proceed.\r\n");
            client->logged_in = true;
        } else {
            dprintf(client->fd, "331 User name okay, need password.\r\n");
            client->logged_in = false;
        }
    }
}
