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

void do_command(t_cmds *cmds)
{

    // check_heredoc();
    // gestionar_redir();
    // dups_ejecutar();
    pid_t pid;
    // int fd;

    // fd = open(infile, O_RDONLY);

    /* ejecuta como proceso hijo*/
    if(pipe(cmds->pipe_fd) < 0)
        perror("");
    pid = fork();
    if(pid < 0)
        perror("");
    if(pid == 0)
    {
        // close(cmds->pipe_fd[0]);
        // dup2(cmds->pipe_fd[1], STDOUT_FILENO);
        // close(cmds->pipe_fd[1]);
        exec(cmds);
    }
    else
    {
        close(cmds->pipe_fd[1]);
        dup2(cmds->pipe_fd[0], STDIN_FILENO);
        close(cmds->pipe_fd[0]);
    }
    printf("pid -> %d\n", pid);

    /*hasta aqui*/


}

void do_command2(t_cmds *cmds)
{

    // check_heredoc();
    // gestionar_redir();
    // dups_ejecutar();
    pid_t pid;
    // int fd;

    // fd = open(infile, O_RDONLY);

    /* ejecuta como proceso hijo*/
    if(pipe(cmds->pipe_fd) < 0)
        perror("");
    pid = fork();
    if(pid < 0)
        perror("");
    if(pid == 0)
    {
        // close(cmds->pipe_fd[0]);
        // dup2(cmds->pipe_fd[1], STDOUT_FILENO);
        // close(cmds->pipe_fd[1]);
        exec(cmds);
    }
    else
    {
        close(cmds->pipe_fd[1]);
        dup2(cmds->pipe_fd[0], STDIN_FILENO);
        close(cmds->pipe_fd[0]);
    }
    printf("pid -> %d\n", pid);

    /*hasta aqui*/


}