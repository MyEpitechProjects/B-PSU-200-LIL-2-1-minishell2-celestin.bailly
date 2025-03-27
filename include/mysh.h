/*
** EPITECH PROJECT, 2025
** mylib
** File description:
** header
*/

#ifndef LIBMY_H
    #define LIBMY_H
    #include <unistd.h>
    #include <stddef.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <sys/wait.h>
    #include <sys/resource.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <dirent.h>
    #include <stdbool.h>
typedef struct pipes {
    int stdin[2];
    int stdout[2];
    int piped_stdin;
    int piped_stdout;
} pipes_t;
typedef struct myshell {
    char *commands;
    char **splitted;
    char *hostname;
    unsigned char status;
    bool root;
    char *stdout;
    bool piped;
    bool redirected;
    pid_t fork;
    struct env *env;
} myshell_t;
typedef struct env {
    char *name;
    char *value;
    struct env *nxt;
} env_t;

void print_current_dir(myshell_t *shell);
int my_env(myshell_t *shell);
int my_setenv(myshell_t *shell, char *name, char *value, int overwrite);
void my_free_list(char **lst);
int my_free(void *data, int value);
int my_exit(myshell_t *shell);
int free_struct(myshell_t *shell, int value);
int my_cd(myshell_t *shell);
char *my_strcat(char *dest, char *input);
char *my_getenv(myshell_t *shell, char *name);
char **my_str_to_word_array(char const *str);
char **my_split(char *str, char delimiter);
int my_strlen(char const *str);
int my_list_len(char **lst);
env_t *env_cpy(char **environ);
char *clist_get_value(env_t *env, char *name);
void clist_push(env_t *env, char *name, char *value);
char **clist_to_list(env_t *env);
void free_env(env_t *temp);
char *my_strcpy(char *dest, char const *src);
int my_env_len(env_t *tmp);
int strlstcmp(char **lst, char const *str);
int handle_commands(myshell_t *shell, char **builtins);
void my_putstr(const char *str);
void clist_edit(env_t *env, char *name, char *value);
int name_in_clist(env_t *env, char *name);
int shell_loop(myshell_t *shell);
int my_setenv_comm(myshell_t *shell);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
int create_fork(myshell_t *shell, char *path);
char *extract_commands_path(myshell_t *shell);
char *get_specific_usr_home(char *user);
int delete(env_t *tmp, char *name);
int my_unsetenv(myshell_t *shell, char *name);
int my_unsetenv_comm(myshell_t *shell);
long get_file_size(const char *filename);
char **files_to_list(char *file_name);
int get_stdout(myshell_t *shell, int fd);
bool is_root(void);
char **my_strsplit(const char *text, const char *delim, char spe);
bool is_valid(char **split);
bool scan_line(myshell_t *shell, char **split);
int handle_save_redirection(myshell_t *shell, char **splitted, int idx,
    bool is_write);
int handle_get_redirection(myshell_t *shell, char **splitted, int idx);
void parse_eof(myshell_t *shell, char *eof_param);
int set_pipe_flg(myshell_t *shell, char **splitted, int i);
bool is_good_eof(char *str1, char *str2);

#endif
