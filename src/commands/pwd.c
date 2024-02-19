/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** pwd.c
*/
#include "myftp.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void help_pwd(client_t *client)
{
    dprintf(client->fd, "PWD <CRLF> : Print working directory\r\n");
}

void pwd(char **words, client_t *client, enum Mode mode)
{
    if (mode == HELP) {
        help_pwd(client);
        return;
    }
    if (double_array_len(words) != 1)
        dprintf(client->fd,
        "501 Syntax error in parameters or arguments.\r\n");
    else
        dprintf(client->fd, "257 %s created.\r\n", client->path);
}
