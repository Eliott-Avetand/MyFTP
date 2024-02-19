/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** main.c
*/
#include "myftp.h"
#include <stdio.h>
#include <string.h>

int check_help(char *arg)
{
    if (strcmp(arg, "-help") == 0) {
        printf("USAGE: ./myftp port path\n");
        printf("\tport\tis the port number on"
        "which the server socket listens\n");
        printf("\tpath\tis the path to the home"
        "directory for the Anonymous user\n");
        return 0;
    } else
        return 84;
}

int main(int ac, char **av)
{
    if (ac == 2)
        return check_help(av[1]);
    else if (ac == 3)
        return handle_errors(av[1], av[2]);
    else {
        fprintf(stderr, "ERROR: Invalid args numbers"
        "(-help for further informations).\n");
        return 84;
    }
}
