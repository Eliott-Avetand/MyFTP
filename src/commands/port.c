/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** port.c
*/
#include "myftp.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void help_port(client_t *client)
{
    dprintf(client->fd, "PORT <SP> <host-port> <CRLF> :"
    "Enable 'active' mode for data transfer\r\n");
}

void port(char **words, client_t *client, enum Mode mode)
{
    if (mode == HELP) {
        help_port(client);
        return;
    }
    if (double_array_len(words) != 2) {
        dprintf(client->fd,
        "501 Syntax error in parameters or arguments.\r\n");
    } else {
        if (is_number(words[1])) {
            client->mode = ACTIVE;
            client->host_port = atoi(words[1]);
            dprintf(client->fd, "200 Command okay.\r\n");
        } else
            dprintf(client->fd,
            "501 Syntax error in parameters or arguments.\r\n");
    }
}
