/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:52:59 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/10/03 15:53:00 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_def **def)
{
	int		i;
	t_def	*copy;

	i = mini_lstsize(*def);
	while (i)
	{
		ft_free_double((*def)->argv);
		free((*def)->type);
		copy = *def;
		*def = (*def)->next;
		free(copy);
		i--;
	}	
}

void	free_env(t_env *env)
{
	ft_free_double(env->env);
	free(env);
}

void	free_struct(t_cmds *vals)
{
	if (vals->cmds_argv != NULL)
		ft_free_double(vals->cmds_argv);
	if (vals->cmds_path != NULL)
		free(vals->cmds_path);
}

void	free_pipe(t_cmds *cmds, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(cmds->pipe_fd[i]);
		i++;
	}
	free(cmds->pipe_fd);
}
