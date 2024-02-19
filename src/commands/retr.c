/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** cdup.c
*/
#include "myftp.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void help_retr(client_t *client)
{
    dprintf(client->fd, "RETR <SP> <pathname> <CRLF> :"
    "Download file from server to client\r\n");
}

void handle_file(client_t *client, char *pathname, int client_data_fd)
{
    int fd;
    char *buf;
    struct stat *statbuf = malloc(sizeof(struct stat));

    if ((fd = open(pathname, O_RDONLY)) != -1) {
        stat(pathname, statbuf);
        buf = malloc(sizeof(char) * (statbuf->st_size + 1));
        read(fd, buf, statbuf->st_size);
        buf[statbuf->st_size] = '\0';
        dprintf(client->fd,
        "150 File status okay; about to open data connection.\r\n");
        dprintf(client_data_fd, "%s", buf);
        shutdown(client->data_fd, SHUT_RDWR);
        close(client->data_fd);
        dprintf(client->fd, "226 Closing data connection.\r\n");
        free(buf);
    } else
        dprintf(client->fd, "550 Requested action not taken. "
        "File unavailable (e.g., file not found, no access).\r\n");
    free(statbuf);
}

void data_transfer(client_t *client, char *pathname)
{
    struct sockaddr_in data_client;
    socklen_t size = sizeof(data_client);
    int client_data_fd = accept(client->data_fd,
    (struct sockaddr *)&data_client, &size);
    int pid;

    chdir(client->path);
    pid = fork();
    if (pid == 0) {
        handle_file(client, pathname, client_data_fd);
        exit(0);
    } else
        client->mode = NONE;
}

void retr(char **words, client_t *client, enum Mode mode)
{
    if (mode == HELP) {
        help_retr(client);
        return;
    } else if (double_array_len(words) != 2) {
        dprintf(client->fd,
        "501 Syntax error in parameters or arguments.\r\n");
    } else {
        if (client->mode == NONE)
            dprintf(client->fd, "500 Illegal command.\r\n");
        else
            data_transfer(client, words[1]);
    }
}
