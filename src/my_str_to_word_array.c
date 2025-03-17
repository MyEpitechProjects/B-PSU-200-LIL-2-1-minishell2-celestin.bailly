/*
** EPITECH PROJECT, 2024
** C Pool Day 08
** File description:
**  convert string to list
*/

#include "mysh.h"

int my_strlen(char const *str)
{
    int number = 0;

    if (str == NULL)
        return number;
    for (int i = 0; str[i] != '\0'; i++)
        number += 1;
    return number;
}

static int is_nalpha(char nbr)
{
    return (nbr == ' ' || nbr == '\t');
}

int count_non_alpha(char const *str)
{
    int idx = 0;
    int count = 0;
    int word = 0;

    while (str[idx] != '\0'){
        if (is_nalpha(str[idx]) == 1)
            word = 0;
        if ((is_nalpha(str[idx]) == 0) && word == 0){
            count += 1;
            word = 1;
        }
        idx += 1;
    }
    return count;
}

char **replace_string(char const *str, char **wr)
{
    int idx2 = 0;
    int idx3 = 0;
    int word = 0;

    for (int i = 0; str[i] != '\0'; i++){
        if (is_nalpha(str[i]) == 1 && word == 1) {
            idx2 += 1;
            idx3 = 0;
            word = 0;
        }
        if (is_nalpha(str[i]) == 0){
            wr[idx2][idx3] = str[i];
            wr[idx2][idx3 + 1] = '\0';
            idx3 += 1;
            word = 1;
        }
    }
    return wr;
}

int *count_every_string(int *len, char const *str)
{
    int value = 0;
    int end = 0;
    int idx = 0;

    for (int i = 0; str[i] != '\0'; i++){
        end = 0;
        if (is_nalpha(str[i]) == 1 && value > 0){
            len[idx] = value;
            idx += 1;
            value = 0;
        }
        if (is_nalpha(str[i]) == 0){
            value += 1;
            end = 1;
        }
    }
    if (end == 1)
        len[idx] = value;
    return len;
}

char **my_str_to_word_array(char const *str)
{
    int word_count = count_non_alpha(str);
    int word_len[word_count + 1];
    char **word_array;

    if (my_strlen(str) == 0)
        return NULL;
    word_array = malloc(sizeof(char *) * (word_count + 1));
    if (word_array == NULL)
        return NULL;
    count_every_string(word_len, str);
    for (int i = 0; i < word_count; i++){
        word_array[i] = malloc(sizeof(char) * (word_len[i] + 1));
    }
    replace_string(str, word_array);
    word_array[word_count] = NULL;
    return word_array;
}
