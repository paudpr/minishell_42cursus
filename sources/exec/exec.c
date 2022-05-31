#include "pruebas_bash.h"


void exec(t_cmds *cmds)
{
    char **split;
    char *cmd;

    split = ft_split(cmds->cmds_argv, ' ');
    cmd = ft_strjoin(cmds->cmds_path, split[0]);
    if(execve(cmd, split, cmds->env->env) < 0)
        print_error("falla execve");
}

void	check_access(char *path)
{
	if (access(path, R_OK | W_OK) != 0)
		print_error(0);
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
        exec(cmds);
}



void check_relative_path(char *cmd)
{
    char *chr;

    chr = NULL;
    if(ft_strrchr(cmd, '/') != NULL)
    {
        chr = ft_strdup(ft_strrchr(cmd, '/') + 1);
        free(cmd);
        cmd = chr;
    }
}

void get_relative_path(char *cmd)
{
    //coger la parte de alante del str para guardar el path relativo
    char *chr;

    chr = NULL;
    if(ft_strrchr(cmd, '/') != NULL)
    {
        chr = ft_strdup(ft_strrchr(cmd, '/') + 1);
        free(cmd);
        cmd = chr;
    }
}

void wait_process(t_def *def)
{
    int i;
    int *s;

    s = NULL;
    i = ft_lstsize(def);
    while(i)
    {
        waitpid(-1, s, 0);
        i--;
    }
}
