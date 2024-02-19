/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** my_ftp.c
*/
#include "myftp.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <errno.h>

void handle_client(client_t **clients, server_t *server, int fd)
{
    char *buf = malloc(sizeof(char) * 4096);
    int nbytes = read(fd, buf, 4096);
    client_t *client = get_client(clients, fd);

    if (nbytes <= 1) {
        dprintf(client->fd, "QUIT\r\n");
        close(client->fd);
        FD_CLR(client->fd, &server->main_set);
    } else {
        buf[nbytes] = '\0';
        middleware(buf, client);
        if (!client->is_connected)
            FD_CLR(client->fd, &server->main_set);
    }
}

void handle_server(client_t **clients, server_t *server)
{
    struct sockaddr_in client;
    socklen_t len;
    int afd;

    len = sizeof(struct sockaddr_in);
    if ((afd = accept(server->fd, (struct sockaddr *)&client, &len)) == -1)
        fprintf(stderr, "An error occurs\n");
    else {
        FD_SET(afd, &server->main_set);
        new_client(clients, afd, server->path);
        if (afd > server->nfds)
            server->nfds = afd;
        printf("New connection from %s on socket %d\r\n",
        inet_ntoa(client.sin_addr), afd);
        dprintf(afd, "220 Service ready for new user.\r\n");
    }
}

void handle_fds(client_t **clients, server_t *server)
{
    for (int i = 0; i < server->nfds + 1; i++) {
        if (FD_ISSET(i, &server->tmp_set) && i == server->fd)
            handle_server(clients, server);
        else if (FD_ISSET(i, &server->tmp_set))
            handle_client(clients, server, i);
    }
}

void shell(client_t **clients, server_t *server)
{
    FD_ZERO(&server->main_set);
    FD_ZERO(&server->tmp_set);
    FD_SET(server->fd, &server->main_set);
    server->nfds = server->fd;
    while (1) {
        memcpy(&server->tmp_set, &server->main_set, sizeof(server->main_set));
        if (select(server->nfds + 1,
        &server->tmp_set, NULL, NULL, NULL) == -1) {
            perror(strerror(errno));
            exit(84);
        }
        handle_fds(clients, server);
    }
}

void my_ftp(int port, char *path)
{
    client_t *clients = NULL;
    server_t *server = malloc(sizeof(server_t));
    int sfd = create_socket();

    configure_socket(sfd, port);
    server->path = strdup(path);
    server->fd = sfd;
    shell(&clients, server);
}
