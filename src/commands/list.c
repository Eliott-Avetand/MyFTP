/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** list.c
*/
#include "myftp.h"
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void help_list(client_t *client)
{
    dprintf(client->fd, "LIST [<SP> <pathname>] <CRLF> :"
    "List files in the current working directory\r\n");
}

void listing(client_t *client, char *pathname, int client_data_fd)
{
    DIR *d = opendir(pathname);
    struct dirent *dir;

    if (d) {
        while ((dir = readdir(d)) != NULL)
            dprintf(client_data_fd, "%s\n", dir->d_name);
        closedir(d);
    } else
        dprintf(client->fd, "550 Requested action not taken. "
        "File unavailable (e.g., file not found, no access).\r\n");
    dprintf(client->fd, "226 Closing data connection.\r\n");
    exit(0);
}

void list_transfer(client_t *client, char *pathname)
{
    struct sockaddr_in data_client;
    socklen_t size = sizeof(data_client);
    int client_data_fd = accept(client->data_fd,
    (struct sockaddr *)&data_client, &size);
    int pid;

    dprintf(client->fd,
    "150 File status okay; about to open data connection.\r\n");
    chdir(client->path);
    pid = fork();
    if (pid == 0) {
        listing(client, pathname, client_data_fd);
        exit(0);
    } else
        client->mode = NONE;
}

void list(char **words, client_t *client, enum Mode mode)
{
    if (mode == HELP) {
        help_list(client);
        return;
    } else if (double_array_len(words) > 2) {
        dprintf(client->fd,
        "501 Syntax error in parameters or arguments.\r\n");
    } else {
        if (client->mode == NONE)
            dprintf(client->fd, "500 Illegal command.\r\n");
        else {
            chdir(client->path);
            list_transfer(client,
            double_array_len(words) == 1 ? client->path : words[1]);
        }
    }
}
