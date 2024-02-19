/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** double_array.c
*/
#include <stdlib.h>

int double_array_len(char **array)
{
    int counter = 0;

    while (array[counter])
        counter++;
    return counter;
}

void free_double_array(char **array)
{
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}
