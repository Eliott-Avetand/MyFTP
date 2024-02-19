/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** pass.c
*/
#include "myftp.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void help_pass(client_t *client)
{
    dprintf(client->fd, "PASS <SP> <password> <CRLF> :"
    "Specify password for authentication\r\n");
}

void pass(char **words, client_t *client, enum Mode mode)
{
    if (mode == HELP) {
        help_pass(client);
        return;
    }
    if (double_array_len(words) > 2)
        dprintf(client->fd,
        "501 Syntax error in parameters or arguments.\r\n");
    else {
        if (double_array_len(words) == 1 &&
        strcmp(client->username, "Anonymous") == 0) {
            dprintf(client->fd, "230 User logged in, proceed.\r\n");
            client->logged_in = true;
            client->password = true;
        } else {
            dprintf(client->fd, "530 Not logged in.\r\n");
            client->logged_in = false;
            client->password = false;
        }
    }
}
