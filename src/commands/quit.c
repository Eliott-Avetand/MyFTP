/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** quit.c
*/
#include "myftp.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>

void help_quit(client_t *client)
{
    dprintf(client->fd, "QUIT <CRLF> : Disconnection\r\n");
}

void quit(char **words, client_t *client, enum Mode mode)
{
    if (mode == HELP) {
        help_quit(client);
        return;
    }
    if (double_array_len(words) != 1)
        dprintf(client->fd,
        "501 Syntax error in parameters or arguments.\r\n");
    else {
        dprintf(client->fd, "221 Service closing control connection.\r\n");
        client->is_connected = false;
        shutdown(client->fd, SHUT_RDWR);
        close(client->fd);
    }
}
