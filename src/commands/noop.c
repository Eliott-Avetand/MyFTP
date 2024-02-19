/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** noop.c
*/
#include "myftp.h"
#include <unistd.h>
#include <stdio.h>

void help_noop(client_t *client)
{
    dprintf(client->fd, "NOOP <CRLF> : Do nothing\r\n");
}

void noop(char **words, client_t *client, enum Mode mode)
{
    if (mode == HELP) {
        help_noop(client);
        return;
    }
    if (double_array_len(words) != 1) {
        dprintf(client->fd,
        "501 Syntax error in parameters or arguments.\r\n");
    } else
        dprintf(client->fd, "200 Command okay.\r\n");
}
