/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** cwd.c
*/
#include "myftp.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>

void help_cwd(client_t *client)
{
    dprintf(client->fd, "CWD <SP> <pathname> <CRLF> :"
    "Change working directory\r\n");
}

void cwd(char **words, client_t *client, enum Mode mode)
{
    if (mode == HELP) {
        help_cwd(client);
        return;
    }
    if (double_array_len(words) != 2)
        dprintf(client->fd, "550 Requested action not taken. "
        "File unavailable (e.g., file not found, no access).\r\n");
    else {
        if (access(words[1], X_OK) == 0) {
            chdir(client->path);
            chdir(words[1]);
            client->path = getcwd(NULL, 0);
            dprintf(client->fd,
            "250 Requested file action okay, completed.\r\n");
        } else
            dprintf(client->fd, "550 Requested action not taken. "
            "File unavailable (e.g., file not found, no access).\r\n");
    }
}
