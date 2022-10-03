/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:52:43 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/10/03 15:52:44 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec(t_cmds *cmds)
{
	char		*cmd;
	extern char	**environ;

	cmd = NULL;
	if (cmds->cmds_argv != NULL)
	{
		cmd = ft_strjoin(cmds->cmds_path, cmds->cmds_argv[0]);
		if (cmds->bin == 0)
		{
			if (execve(cmd, cmds->cmds_argv, cmds->env->env) < 0)
				perror("");
		}
		free(cmd);
	}
}

static void	do_commands(t_def *def, t_cmds *cmds, int *check)
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
		do_builtin(cmds, check);
		exec(cmds);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(cmds->pipe_fd[cmds->num][1]);
		dup2(cmds->pipe_fd[cmds->num][0], STDIN_FILENO);
		close(cmds->pipe_fd[cmds->num][0]);
	}
	*check = 1;
}

static void	do_last_command(t_def *def, t_cmds *cmds, int *check)
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
		do_builtin(cmds, check);
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
	*check = 1;
}

static void	do_one_command(t_def *def, t_cmds *cmds, int *check)
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
	*check = 1;
}

void	do_process(t_def *def, t_cmds *cmds)
{
	int	i;
	int	check;

	check = 0;
	i = 0;
	while (i < ft_double_len(def->argv))
	{
		if (def->next == NULL && cmds->num == 0 && check == 0)
		{
			do_builtin(cmds, &check);
			if (cmds->bin == 0)
				do_one_command(def, cmds, &check);
		}
		else if (def->next == NULL && check == 0)
			do_last_command(def, cmds, &check);
		else if (check == 0)
			do_commands(def, cmds, &check);
		if (def->type[i] == 0)
		{
			i++;
			cmds->hd++;
		}
	i++;
	}
}
