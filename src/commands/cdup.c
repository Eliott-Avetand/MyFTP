/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** cdup.c
*/
#include "myftp.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void help_cdup(client_t *client)
{
    dprintf(client->fd, "CDUP <CRLF> :"
    "Change working directory to parent directory\r\n");
}

void cdup(char **words, client_t *client, enum Mode mode)
{
    if (mode == HELP) {
        help_cdup(client);
        return;
    }
    if (double_array_len(words) != 1)
        dprintf(client->fd,
        "501 Syntax error in parameters or arguments.\r\n");
    else {
        chdir(client->path);
        chdir("..");
        client->path = strdup(getcwd(NULL, 0));
        dprintf(client->fd, "200 Command okay.\r\n");
    }
}
