/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** split
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mysh.h"
#include <stddef.h>

static int calc_token_num(char *str, int delimiter)
{
    int res = 1;

    for (int i = 0; str[i] != '\0'; i++){
        if (str[i] == delimiter)
            res++;
    }
    return res;
}

static int calc_len_idx(char *str, int start, char delimiter)
{
    int x = 1;

    for (int i = start; str[i] != delimiter && str[i] != '\0'; i++)
        x++;
    return x;
}

static void push_str_idx(char *str, char **str2, int index, char delimiter)
{
        int i2 = index;

        while (str[i2] != delimiter && str[i2] != '\0'){
            (*str2)[i2 - index] = str[i2];
            i2++;
        }
        (*str2)[i2 - index] = '\0';
}

static void fix(int number, int idx, char **result)
{
    for (int i = idx; i < number; i++){
        result[i] = malloc(sizeof(char) * 1);
        if (result[i] != NULL)
            result[i][0] = '\0';
    }
}

char **my_split(char *str, char delimiter)
{
    int number = calc_token_num(str, delimiter);
    int len = my_strlen(str);
    char **result = malloc((number + 1) * sizeof(char *));
    int index = 0;
    int r = 0;
    int idx = 0;

    if (result == NULL)
        return NULL;
    result[number] = NULL;
    while (index < len){
        r = calc_len_idx(str, index, delimiter);
        result[idx] = malloc(sizeof(char) * (r + 1));
        if (result[idx] != NULL)
            push_str_idx(str, &result[idx], index, delimiter);
        index += r;
        idx++;
    }
    fix(number, idx, result);
    return result;
}
