#include "minishell.h"

void	exec(t_cmds *cmds)
{
	char		*cmd;
	extern char	**environ;

	check_bin(cmds);
	// check_bin2(cmds);
	cmd = ft_strjoin(cmds->cmds_path, cmds->cmds_argv[0]);
	printf("---> %s   %s    %s\n", cmd, cmds->cmds_argv[0],cmds->env->env[13]);
	if(cmds->bin == 0)
	{
		if (execve(cmd, cmds->cmds_argv, cmds->env->env) < 0)
			perror("falla execve ->");
	}
	free(cmd);
}

void	do_commands(t_def *def, t_cmds *cmds)
{
	pid_t	pid;

	cmds->pipe_fd[cmds->num] = ft_calloc(sizeof(int), 2);
	if (pipe(cmds->pipe_fd[cmds->num]) < 0)
		perror("");
	pid = fork();
	if (pid < 0)
		perror("");
	if (pid == 0)
	{
		close(cmds->pipe_fd[cmds->num][0]);
		dup2(cmds->pipe_fd[cmds->num][1], STDOUT_FILENO);
		close(cmds->pipe_fd[cmds->num][1]);
		check_redir(def, cmds);
		exec(cmds);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(cmds->pipe_fd[cmds->num][1]);
		dup2(cmds->pipe_fd[cmds->num][0], STDIN_FILENO);
		close(cmds->pipe_fd[cmds->num][0]);
	}
}

void	do_last_command(t_def *def, t_cmds *cmds)
{
	pid_t	pid;

	cmds->pipe_fd[cmds->num] = ft_calloc(sizeof(int), 2);
	if (pipe(cmds->pipe_fd[cmds->num]) < 0)
		perror("");
	pid = fork();
	if (pid < 0)
		perror("");
	if (pid == 0)
	{
		check_redir(def, cmds);
		exec(cmds);
		exit(0);
	}
	else
	{
		close(cmds->pipe_fd[cmds->num][1]);
		dup2(cmds->pipe_fd[cmds->num][0], STDIN_FILENO);
		close(cmds->pipe_fd[cmds->num][0]);
		wait(&pid);
	}
}

void	do_one_command(t_def *def, t_cmds *cmds)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("");
	if (pid == 0)
	{
		check_redir(def, cmds);
		exec(cmds);
		exit(EXIT_FAILURE);
	}
	else
		wait(&pid);
}

void	do_process(t_def *def, t_cmds *cmds)			//arreglar esta chapuzaaaaaaaa
{
	int	i;
	int	booleanos;

	booleanos = 0;
	i = 0;
	while (i < ft_double_len(def->argv))
	{
		if (def->next == NULL && cmds->num == 0 && booleanos == 0)
		{
			do_one_command(def, cmds);
			booleanos++;
		}
		else if (def->next == NULL && booleanos == 0)
		{
			booleanos++;
			do_last_command(def, cmds);
		}
		else if (booleanos == 0)
		{
			do_commands(def, cmds);
			booleanos++;
		}
	i++;
	}
}
