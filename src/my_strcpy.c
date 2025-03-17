/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

char *my_strcpy(char *dest, char const *src)
{
    int index = 0;

    while (src[index] != '\0'){
        dest[index] = src[index];
        index += 1;
    }
    dest[index] = '\0';
    return dest;
}
