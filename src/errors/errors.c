/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** errors.c
*/
#include "myftp.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int handle_errors(char *port, char *path)
{
    if (is_number(port) && access(path, X_OK) == 0) {
        my_ftp(atoi(port), path);
        return 0;
    } else {
        fprintf(stderr, "ERROR: The port must be an int "
        "and the path, a valid one.\r\n");
        return 84;
    }
}
