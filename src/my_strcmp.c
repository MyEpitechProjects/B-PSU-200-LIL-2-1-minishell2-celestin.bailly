/*
** EPITECH PROJECT, 2024
** C Pool Day 06
** File description:
** strcmp
*/

#include "mysh.h"

int my_strcmp(char const *s1, char const *s2)
{
    int idx = 0;
    int max = my_strlen(s2);

    while (s1[idx] != '\0'){
        if (s1[idx + 1] == '\0' && (idx + 1 < max))
            return s2[idx + 1] * -1;
        if (s1[idx + 1] != '\0' && (s2[idx + 1] == '\0'))
            return s1[idx + 1];
        if (s1[idx] != s2[idx])
            return s1[idx] - s2[idx];
        idx += 1;
    }
    return 0;
}

int my_strncmp(char const *s1, char const *s2, int n)
{
    int idx = 0;
    int max = my_strlen(s2);

    while (s1[idx] != '\0' && idx < n - 1){
        if (s1[idx + 1] == '\0' && (idx + 1 < max))
            return s2[idx + 1] * -1;
        if (s1[idx + 1] != '\0' && (s2[idx + 1] == '\0'))
            return s1[idx + 1];
        if (s1[idx] != s2[idx])
            return s1[idx] - s2[idx];
        idx += 1;
    }
    return 0;
}
