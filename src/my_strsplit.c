/*
** EPITECH PROJECT, 2025
** my_sscanf
** File description:
** sscanf
*/

#include <stddef.h>
#include <stdbool.h>
#include "mysh.h"

static bool is_delim(char c, const char *delim, int activated)
{
    if (activated == 1)
        return false;
    for (int i = 0; delim[i] != '\0'; i++){
        if (delim[i] == c)
            return true;
    }
    return false;
}

static char **free_error(char **res)
{
    for (int i = 0; res[i] != NULL; i++)
        free(res[i]);
    free(res);
    return NULL;
}

static int get_word_num(const char *text, const char *delim, char spe)
{
    int num = 0;
    int is_word = 0;
    int act = 0;

    for (int i = 0; text[i] != '\0'; i++){
        if (is_delim(text[i], delim, act) && act == 0){
            is_word = 0;
            num++;
        }
        if (text[i] == spe){
            act = ((act + 1) % 2);
            continue;
        }
        if (!is_delim(text[i], delim, act) && is_word == 0){
            num += 1;
            is_word = 1;
        }
    }
    return num;
}

static int calc_len(const char *text, const char *delim, char spe)
{
    int len = 0;
    int act = 0;

    for (int i = 0; (!is_delim(text[i], delim, 0) || act == 1)
        && text[i] != '\0'; i++){
        if (text[i] != spe)
            len += 1;
        if (text[i] == spe)
            act = ((act + 1) % 2);
    }
    return len;
}

static int split_push(const char *text, const char *delim,
    char spe, char **res)
{
    int act = 0;
    int idx = 0;
    int i = 0;

    while ((!is_delim(text[i], delim, 0) || act == 1) && text[i] != '\0'){
        if (text[i] != spe){
            (*res)[idx] = text[i];
            idx++;
        }
        if (text[i] == spe)
            act = ((act + 1) % 2);
        i++;
    }
    (*res)[idx] = '\0';
    if (text[i] == spe)
        return i + 1;
    return i;
}

static int split_push_delim(char delim, char **res, int idx, int *i)
{
    res[idx] = malloc(sizeof(char) * 2);
    if (res[idx] == NULL)
        return 0;
    res[idx][1] = '\0';
    res[idx][0] = delim;
    *i = (*i + 1);
    return 1;
}

static char **split_run(const char *text, const char *delim,
    char spe, int word_num)
{
    int text_len = my_strlen(text);
    char **res = malloc(sizeof(char *) * (word_num + 1));
    int val[] = {0, 0};

    if (res == NULL)
        return NULL;
    res[word_num] = NULL;
    for (int i = 0; i < text_len && val[1] < word_num;){
        if (is_delim(text[i], delim, 0)){
            val[1] += split_push_delim(text[i], res, val[1], &i);
            continue;
        }
        val[0] = calc_len(text + i, delim, spe);
        res[val[1]] = malloc(sizeof(char) * (val[0] + 1));
        if (res[val[1]] == NULL)
            return free_error(res);
        i += split_push(text + i, delim, spe, &res[val[1]]);
        val[1]++;
    }
    return res;
}

char **my_strsplit(const char *text, const char *delim, char spe)
{
    int word_num = 0;

    if (text == NULL || delim == NULL)
        return NULL;
    if (text[0] == '\0' || delim[0] == '\0')
        return NULL;
    word_num = get_word_num(text, delim, spe);
    if (word_num > 0)
        return split_run(text, delim, spe, word_num);
    else
        return NULL;
}
