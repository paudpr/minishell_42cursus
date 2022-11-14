/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladelpinoramirez <pauladelpinoramire    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:52:52 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/11/14 14:44:40 by pauladelpin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char **path, char *argv)
{
	int		i;
	char	*cmd_path;

	i = 0;
	cmd_path = NULL;
	if (path == NULL)
		return (NULL);
	cmd_path = check_valid(path, argv);
	if (cmd_path == NULL)
		return (NULL);
	return (cmd_path);
}

static int	size_cmds(t_def *def)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (def->argv[i])
	{
		if (def->type[i] == T_CMD)
			size++;
		i++;
	}
	return (size);
}

static char	**get_argv(t_def *def)
{
	int		i;
	int		j;
	int		size;
	char	**cmds;

	i = 0;
	j = 0;
	size = size_cmds(def);
	if (size == 0)
		return (NULL);
	cmds = ft_calloc(sizeof(char *), size + 1);
	if (cmds == NULL)
		return (cmds);
	while (def->argv[i])
	{
		if (def->type[i] == T_CMD)
		{
			cmds[j] = ft_strdup(def->argv[i]);
			j++;
		}
		i++;
	}
	return (cmds);
}

static char	*get_var_path(t_cmds *cmds)
{
	int		i;
	char	*path;
	char	*path_clean;

	i = 0;
	path = NULL;
	while (i < ft_double_len(cmds->env->env))
	{
		if (ft_strncmp("PATH=", cmds->env->env[i], 5) == 0)
			path = ft_strdup(cmds->env->env[i]);
		i++;
	}
	if (path == NULL)
		return (NULL);
	path_clean = ft_strdup(ft_strchr(path, '=') + 1);
	free(path);
	return (path_clean);
}

void	get_argv_path(t_def *def, t_cmds *cmds)
{
	char	*path;
	char	**path_div;
	char	*rel_cmd;

	path = get_var_path(cmds);
	path_div = ft_split(path, ':');
	free(path);
	cmds->cmds_argv = get_argv(def);
	if (cmds->cmds_argv == NULL)
	{
		cmds->cmds_path = NULL;
		ft_free_double(path_div);
		return ;
	}
	if (ft_strrchr(cmds->cmds_argv[0], '/') != NULL)
	{
		cmds->cmds_path = get_relative_path(cmds->cmds_argv[0]);
		rel_cmd = get_relative_argv(cmds->cmds_argv[0]);
		free(cmds->cmds_argv[0]);
		cmds->cmds_argv[0] = ft_strdup(rel_cmd);
		free(rel_cmd);
	}
	else
		cmds->cmds_path = get_path(path_div, cmds->cmds_argv[0]);
	ft_free_double(path_div);
}
