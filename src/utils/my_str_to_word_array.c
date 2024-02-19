/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** my_str_to_word_array
*/
#include "myftp.h"
#include <string.h>
#include <stdlib.h>
#include <string.h>

char **my_str_to_word_array(char *str)
{
    char *new_str = malloc(sizeof(char) * (strlen(str) - 1));
    char **words = malloc(sizeof(char *));
    char *token;
    int counter = 0;

    memmove(new_str, str, strlen(str) - 2);
    new_str[strlen(str) - 2] = '\0';
    token = strtok(new_str, " ");
    while (token != NULL) {
        words = realloc(words, sizeof(char *) * (counter + 2));
        words[counter] = strdup(token);
        token = strtok(NULL, " ");
        counter++;
    }
    words[counter] = NULL;
    free(new_str);
    free(str);
    return words;
}
