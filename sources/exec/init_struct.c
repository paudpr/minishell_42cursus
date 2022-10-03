/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:52:50 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/10/03 15:52:51 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct_cmds(t_env *env, t_cmds *cmds, int i)
{
	cmds->env = env;
	cmds->num = 0;
	cmds->bin = 0;
	cmds->hd = 0;
	if (i < 0)
		i = 0;
	cmds->pipe_fd = ft_calloc(sizeof(int *), i);
	cmds->fd_in = dup(STDIN_FILENO);
	cmds->fd_out = dup(STDOUT_FILENO);
}

char	*get_relative_path(char *cmd)
{
	char	*chr;
	char	*path;
	int		len;

	chr = ft_strrchr(cmd, '/') + 1;
	len = ft_strlen(cmd) - ft_strlen(chr);
	path = ft_substr(cmd, 0, len);
	return (path);
}

char	*get_relative_argv(char *cmd)
{
	char	*chr;

	chr = NULL;
	if (ft_strrchr(cmd, '/') != NULL)
		chr = ft_strdup(ft_strrchr(cmd, '/') + 1);
	return (chr);
}

char	*check_valid(char **path, char *cmd)
{
	int		i;
	char	*cmd_str;
	char	*cmd_path;
	char	*aux;

	i = 0;
	cmd_path = NULL;
	while (path[i])
	{
		aux = ft_strjoin(path[i], "/");
		cmd_str = ft_strjoin(aux, cmd);
		if (access(cmd_str, F_OK) == 0)
			cmd_path = ft_strdup(aux);
		free(aux);
		free(cmd_str);
		i++;
	}
	if (cmd_path == NULL)
		access(cmd_path, F_OK);
	return (cmd_path);
}
