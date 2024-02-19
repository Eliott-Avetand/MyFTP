/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** handle_commands.c
*/
#include "myftp.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void handle_commands(char **words, client_t *client)
{
    int counter = 0;

    if (!client->logged_in) {
        dprintf(client->fd, "530 Not logged in.\r\n");
        return;
    }
    for (counter = 0; counter < 11; counter++) {
        if (strcmp(words[0], commands_s[counter].name) == 0) {
            (commands_s[counter].func)(words, client, COMMAND);
            break;
        }
    }
    if (counter == 11)
        dprintf(client->fd, "500 Command not implemented.\r\n");
}

void middleware(char *input, client_t *client)
{
    char **words = my_str_to_word_array(input);

    if (!words)
        exit(84);
    if (double_array_len(words) == 0)
        dprintf(client->fd, "500 Invalid command.\r\n");
    else if (strcmp(words[0], "USER") != 0 &&
    strcmp(words[0], "PASS") != 0 && strcmp(words[0], "QUIT") != 0)
        handle_commands(words, client);
    else {
        if (strcmp(words[0], "QUIT") == 0)
            quit(words, client, COMMAND);
        else if (strcmp(words[0], "USER") == 0)
            user(words, client, COMMAND);
        else
            pass(words, client, COMMAND);
    }
    free_double_array(words);
}
