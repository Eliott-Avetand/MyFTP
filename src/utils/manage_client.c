/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** configure_client.c
*/
#include "myftp.h"
#include <stdlib.h>
#include <string.h>

void new_client(client_t **clients, int fd, char *path)
{
    client_t *client = malloc(sizeof(client_t));

    if (!client)
        exit(84);
    client->fd = fd;
    client->data_fd = 0;
    client->host_port = 0;
    client->logged_in = false;
    client->path = strdup(path);
    client->is_connected = true;
    client->next = (*clients);
    client->password = false;
    client->username = strdup("");
    client->mode = NONE;
    (*clients) = client;
}

void client_leave(client_t **clients, int fd)
{
    client_t *current = NULL;
    client_t *tmp = NULL;

    if (*clients == NULL)
        return;
    while (current->fd != fd) {
        if (current->next == NULL)
            return;
        tmp = current;
        current = current->next;
    }
    if (current == *clients)
        *clients = (*clients)->next;
    else
        tmp->next = current->next;
}

client_t *get_client(client_t **clients, int fd)
{
    client_t *current = *clients;

    if (*clients == NULL)
        return NULL;
    while (current->fd != fd) {
        if (current->next == NULL)
            return NULL;
        else
            current = current->next;
    }
    return current;
}
