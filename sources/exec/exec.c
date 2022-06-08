#include "minishell.h"


void exec(t_cmds *cmds)
{
    char **split;
    char *cmd;

    split = ft_split(cmds->cmds_argv, ' ');
    cmd = ft_strjoin(cmds->cmds_path, split[0]);
    // printf("cmd -> %s\n", cmd);
    // printf("split[0] -> %s\n", split[0]);
    // printf("env[0] -> %s\n", cmds->env->env[0]);
    if(execve(cmd, split, cmds->env->env) < 0)
        perror("falla execve ->");
}

void do_commands(t_cmds *cmds)
{
    pid_t pid;

    cmds->pipe_fd[cmds->num] = ft_calloc(2, sizeof(int));
    if(pipe(cmds->pipe_fd[cmds->num]) < 0)
        perror("");
    pid = fork();
    if(pid < 0)
        perror("");
    if(pid == 0)
    {
        close(cmds->pipe_fd[cmds->num][0]);
        dup2(cmds->pipe_fd[cmds->num][1], STDOUT_FILENO);
        close(cmds->pipe_fd[cmds->num][1]);
        exec(cmds);
        exit(-1);
    }
    else
    {
        close(cmds->pipe_fd[cmds->num][1]);
        dup2(cmds->pipe_fd[cmds->num][0], STDIN_FILENO);
        close(cmds->pipe_fd[cmds->num][0]);
    }
}

void do_last_command(t_cmds *cmds)
{
    pid_t pid;

    cmds->pipe_fd[cmds->num] = ft_calloc(2, sizeof(int));
    if(pipe(cmds->pipe_fd[cmds->num]) < 0)
        perror("");
    pid = fork();
    if(pid < 0)
        perror("");
    if(pid == 0)
        exec(cmds);
    else
    {
        close(cmds->pipe_fd[cmds->num][1]);
        dup2(cmds->pipe_fd[cmds->num][0], STDIN_FILENO);
        close(cmds->pipe_fd[cmds->num][0]);
        wait(&pid);
    }
}



void do_one_command(t_cmds *cmds)
{
    pid_t pid;

    cmds->pipe_fd[cmds->num] = ft_calloc(2, sizeof(int));
    if(pipe(cmds->pipe_fd[cmds->num]) < 0)
        perror("");
    pid = fork();
    if(pid < 0)
        perror("");
    if(pid == 0)
    {
        exec(cmds);
        exit(-1);
    }
    // getchar();
}

