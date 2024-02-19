/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** dele.c
*/
#include "myftp.h"
#include <stdio.h>
#include <unistd.h>

void help_dele(client_t *client)
{
    dprintf(client->fd, "DELE <SP> <pathname> <CRLF> :"
    "Delete file on the server\r\n");
}

void dele(char **words, client_t *client, enum Mode mode)
{
    if (mode == HELP) {
        help_dele(client);
        return;
    }
    if (double_array_len(words) != 2)
        dprintf(client->fd,
        "501 Syntax error in parameters or arguments.\r\n");
    else {
        chdir(client->path);
        if (access(words[1], F_OK) == 0) {
            remove(words[1]);
            dprintf(client->fd,
            "250 Requested file action okay, completed.\r\n");
        } else
            dprintf(client->fd, "550 Requested action not taken. "
            "File unavailable (e.g., file not found, no access).\r\n");
    }
    (void)words;
    (void)client;
}
