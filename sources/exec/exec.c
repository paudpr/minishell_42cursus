#include "minishell.h"

void exec(t_cmds *cmds)
{
    char **split;
    char *cmd;

    split = ft_split(cmds->cmds_argv, ' ');
    cmd = ft_strjoin(cmds->cmds_path, split[0]);
    if(execve(cmd, split, cmds->env->env) < 0)
        perror("falla execve ->");
}

void do_commands(t_cmds *cmds)
{
    pid_t pid;

    cmds->pipe_fd[cmds->num] = ft_calloc(sizeof(int), 2);
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

    // printf("valor num en last_comand -> %d\n", cmds->num);
    cmds->pipe_fd[cmds->num] = ft_calloc(sizeof(int), 2);
    if(pipe(cmds->pipe_fd[cmds->num]) < 0)
        perror("");
    pid = fork();
    if(pid < 0)
        perror("");
    if(pid == 0)
	{
		//check_redir();
        exec(cmds);
	}
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

    // printf("valor num  en one_comdan -> %d\n", cmds->num);
    // cmds->pipe_fd[cmds->num] = ft_calloc(2, sizeof(int));
    // printf("%p %p \n",cmds->cmds_argv, cmds->cmds_path);
    // if(pipe(cmds->pipe_fd[cmds->num]) < 0)
    //     perror("");
    pid = fork();
    if(pid < 0)
        perror("");
    if(pid == 0)
    {
		//check_redir();
        exec(cmds);
        exit(0);
    }
}





/*
cuando haces un heredoc, tienes que poonerle un wait para el proceso concreto en el 
que pusiste el heredoc (pid del fork), para asegurarte que para todas las ejecucoines
mientras que el hheredoc está haciendose. esto es:
<< eof | << eof2 | ls, al contrario que cat | cat | ls, no va a ejecuar todo a la vez
y a devolver ls lo primero, si no que va a esperar a que los heredocs estén hechos
para devolver ls
igualmente << eof | ls | <<eof2 no devuelve ls en ningún momento.
esto viene ppor la diferencia de gestión entre lo que tengo en la función wait_process()
que es un: espera a este numero de procesos, entonces devuelve el ls en cuanto puede,
y despues se queda esperando a los cats, y hasta que no se hayan hecho tantos cosos
como cats tengo, no acaba la ejecución
el heredoc, te da igual el numero de procesos que tengas, no puedes dejar que nada salga
hasta que no este terminnado esaa lectura, por lo que ppones el wait esppecíficamente de
ese pid*/