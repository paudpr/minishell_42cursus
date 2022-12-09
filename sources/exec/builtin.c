/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:52:37 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/12/09 16:20:41 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_bin(t_cmds *cmds, t_def *def)
{
	if (ft_strncmp(cmds->cmds_argv[0], "echo", ft_strlen("echo")) == 0
		&& ft_strlen("echo") == ft_strlen(cmds->cmds_argv[0]))
	{
		check_redir(def, cmds);
		cmds->bin = 1;
		do_echo(cmds);
	}
	if (ft_strncmp(cmds->cmds_argv[0], "cd", ft_strlen("cd")) == 0
		&& ft_strlen("cd") == ft_strlen(cmds->cmds_argv[0]))
	{
		check_redir(def, cmds);
		cmds->bin = 1;
		do_cd(cmds);
	}
	if (ft_strncmp(cmds->cmds_argv[0], "pwd", ft_strlen("pwd")) == 0
		&& ft_strlen("pwd") == ft_strlen(cmds->cmds_argv[0]))
	{
		check_redir(def, cmds);
		cmds->bin = 1;
		do_pwd(cmds);
	}
}

static void	check_bin2(t_cmds *cmds, t_def *def)
{
	if (ft_strncmp(cmds->cmds_argv[0], "export", ft_strlen("export")) == 0
		&& ft_strlen("export") == ft_strlen(cmds->cmds_argv[0]))
	{
		check_redir(def, cmds);
		cmds->bin = 1;
		do_export(cmds);
	}
	if (ft_strncmp(cmds->cmds_argv[0], "unset", ft_strlen("unset")) == 0
		&& ft_strlen("unset") == ft_strlen(cmds->cmds_argv[0]))
	{
		check_redir(def, cmds);
		cmds->bin = 1;
		do_unset(cmds);
	}
	if (ft_strncmp(cmds->cmds_argv[0], "env", ft_strlen("env")) == 0
		&& ft_strlen("env") == ft_strlen(cmds->cmds_argv[0]))
	{
		check_redir(def, cmds);
		cmds->bin = 1;
		do_env(cmds);
	}
}

static void	check_bin3(t_cmds *cmds, t_def *def)
{
	if (ft_strncmp(cmds->cmds_argv[0], "exit", ft_strlen("exit")) == 0
		&& ft_strlen("exit") == ft_strlen(cmds->cmds_argv[0]))
	{
		check_redir(def, cmds);
		cmds->bin = 1;
		do_exit(cmds);
	}
}

void	do_builtin(t_cmds *cmds, int *check, t_def *def)
{
	// printf("check -> %p\n", check);
	if (cmds->cmds_argv != NULL)
	{
		check_bin(cmds, def);
		check_bin2(cmds, def);
		check_bin3(cmds, def);
		*check = 1;
	}
}
