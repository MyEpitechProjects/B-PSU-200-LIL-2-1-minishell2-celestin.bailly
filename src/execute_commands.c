/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

const char *errno_msg[] = {
    NULL,
    NULL,
    ": Command not found.\n",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ": Exec format error. Binary file not executable.\n",
    NULL,
    NULL,
    NULL,
    NULL,
    ": Permission denied.\n"
};

static void close_pipe(int *val, int piped)
{
    if (piped == 0){
        close(val[0]);
        close(val[1]);
    }
}

int signals_error(myshell_t *shell, int status)
{
    int signals = WTERMSIG(status);

    my_putstr(strsignal(signals));
    shell->status = status;
    if (__WCOREDUMP(status))
        my_putstr(" (core dumped)");
    else
        shell->status = 128 + status;
    my_putstr("\n");
    return 0;
}

static int run_child(myshell_t *shell, char **env, char *path, pipes_t pipes)
{
    int res = -1;

    if (shell->piped == true){
        dup2(pipes.stdout[1], STDOUT_FILENO);
    }
    close(pipes.stdout[1]);
    close(pipes.stdin[1]);
    if (res == -1 && path == NULL)
        res = execve(shell->splitted[0], shell->splitted, env);
    if (res == -1 && path != NULL)
        res = execve(path, shell->splitted, env);
    if (res == -1)
        my_putstr(shell->splitted[0]);
    if (errno >= 0 && errno <= 13 && errno_msg[errno] != NULL)
        my_putstr(errno_msg[errno]);
    free(path);
    my_free_list(env);
    free_struct(shell, 0);
    exit((res == -1));
}

static void call_run_child(myshell_t *shell,
    char **env, char *path, pipes_t pipes)
{
    if (shell->stdout != NULL)
        dup2(pipes.stdin[0], STDIN_FILENO);
    close(pipes.stdin[0]);
    close(pipes.stdout[0]);
    run_child(shell, env, path, pipes);
}

static int run_parent(myshell_t *shell, int status)
{
    if (WIFEXITED(status)){
        shell->status = WEXITSTATUS(status);
        return (!(my_strcmp(shell->splitted[0], "chmod")));
    }
    if (WIFSIGNALED(status)){
        signals_error(shell, status);
        return (!(my_strcmp(shell->splitted[0], "chmod")));
    }
    shell->commands[0] = shell->commands[0];
    return (!(my_strcmp(shell->splitted[0], "chmod")));
}

static int wait_child(myshell_t *shell, char **env, char *path, pipes_t *pipes)
{
    int status;
    pid_t finished;

    my_free_list(env);
    free(path);
    if (shell->piped == true){
        get_stdout(shell, pipes->stdout[0]);
        close(pipes->stdin[0]);
    } else {
        close(pipes->stdout[0]);
        close(pipes->stdin[0]);
    }
    finished = waitpid(shell->fork, &status, 0);
    if (finished == shell->fork){
        return run_parent(shell, status);
    }
    return (!(my_strcmp(shell->splitted[0], "chmod")));
}

static int fail_fork_pipe(myshell_t *shell,
    char *path, char **env, pipes_t pipes)
{
    if (pipes.piped_stdin == 0)
        close_pipe(pipes.stdin, pipes.piped_stdin);
    if (pipes.piped_stdout == 0)
        close_pipe(pipes.stdout, pipes.piped_stdout);
    my_free_list(env);
    free(path);
    return (!(my_strcmp(shell->splitted[0], "chmod")));
}

int create_fork(myshell_t *shell, char *path)
{
    char **env = clist_to_list(shell->env);
    pipes_t pipes;

    pipes.piped_stdin = pipe(pipes.stdin);
    pipes.piped_stdout = pipe(pipes.stdout);
    shell->fork = fork();
    if (shell->fork == -1 ||
        (pipes.piped_stdin + pipes.piped_stdout) < 0 || env == NULL)
        return fail_fork_pipe(shell, path, env, pipes);
    if (shell->fork == 0)
        call_run_child(shell, env, path, pipes);
    if (shell->stdout != NULL)
        write(pipes.stdin[1], shell->stdout, my_strlen(shell->stdout));
    close(pipes.stdin[1]);
    close(pipes.stdout[1]);
    wait_child(shell, env, path, &pipes);
    return 0;
}
