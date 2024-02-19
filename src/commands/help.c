/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** help.c
*/
#include "myftp.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void print_all_commands(client_t *client)
{
    dprintf(client->fd,
    "USER <SP> <username> <CRLF> : Specify user for authentication\n"
    "PASS <SP> <password> <CRLF> : Specify password for authentication\n\n"
    "CWD  <SP> <pathname> <CRLF> : Change working directory\n"
    "CDUP <CRLF> : Change working directory to parent directory\n\n"
    "QUIT <CRLF> : Disconnection\n\n"
    "DELE <SP> <pathname> <CRLF> : Delete file on the server\n\n"
    "PWD  <CRLF> : Print working directory\n\n"
    "PASV <CRLF> : Enable 'passive' mode for data transfer\n\n"
    "PORT <SP> <host-port> <CRLF> : Enable 'active' mode for data transfer\n\n"
    "HELP [<SP> <string>] <CRLF> : List available commands\n\n"
    "NOOP <CRLF> : Do nothing\n\n"
    "(the following are commands using data transfer)\n\n"
    "RETR <SP> <pathname> <CRLF> : Download file from server to client\n"
    "STOR <SP> <pathname> <CRLF> : Upload file from client to server\n"
    "LIST [<SP> <pathname>] <CRLF> :"
    "List files in the current working directory\r\n");
}

void print_command(char **words, client_t *client)
{
    int counter = 0;

    for (counter = 0; counter < 14; counter++) {
        if (strcmp(words[1], commands_s[counter].name) == 0) {
            (commands_s[counter].func)(words, client, HELP);
            break;
        }
    }
    if (counter == 14)
        dprintf(client->fd, "500 Command not implemented.\r\n");
    else
        dprintf(client->fd, "214 Help message.\r\n");
}

void help_help(client_t *client)
{
    dprintf(client->fd, "HELP [<SP> <string>] <CRLF> :"
    "List available commands\r\n");
}

void help(char **words, client_t *client, enum Mode mode)
{
    int nb_words = double_array_len(words);

    if (mode == HELP) {
        help_help(client);
        return;
    }
    if (nb_words < 1 ||
    nb_words > 2) {
        dprintf(client->fd,
        "501 Syntax error in parameters or arguments.\r\n");
    } else {
        if (nb_words == 1) {
            print_all_commands(client);
            dprintf(client->fd, "214 Help message.\r\n");
        } else if (nb_words == 2)
            print_command(words, client);
    }
}
