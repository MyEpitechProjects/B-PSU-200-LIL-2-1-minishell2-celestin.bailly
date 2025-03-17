/*
** EPITECH PROJECT, 2025
** my_strcat
** File description:
** strcat
*/

#include "mysh.h"

char *my_strcat(char *dest, char *input)
{
    int inputx = 0;
    int destx = 0;

    if (dest == NULL || input == NULL)
        return NULL;
    while (input[inputx] != '\0'){
        if (dest[destx] == '\0'){
            dest[destx] = input[inputx];
            dest[destx + 1] = '\0';
            inputx += 1;
        }
        destx += 1;
    }
    return dest;
}
