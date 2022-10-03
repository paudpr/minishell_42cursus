/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:52:32 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/10/03 15:52:33 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_var(t_cmds *cmds, int i, int len)
{
	int		j;
	int		k;
	int		length;
	char	*num;
	char	**new_env;

	new_env = ft_calloc(len, sizeof(char *));
	if (new_env == NULL)
		return ;
	j = -1;
	k = -1;
	num = ft_strchr(cmds->cmds_argv[i], '=');
	length = ft_strlen(cmds->cmds_argv[i]) - ft_strlen(num);
	while (++j < len)
	{
		if (ft_strncmp(cmds->cmds_argv[i], cmds->env->env[j], length) == 0)
			j++;
		if (j < len)
			new_env[++k] = ft_strdup(cmds->env->env[j]);
	}
	ft_free_double(cmds->env->env);
	cmds->env->env = new_env;
}

void	do_unset(t_cmds *cmds)
{
	int	i;
	int	j;
	int	len;

	i = 1;
	j = 0;
	len = ft_double_len(cmds->env->env);
	if (len == 1)
		return ;
	while (i < ft_double_len(cmds->cmds_argv))
	{
		len = ft_double_len(cmds->env->env);
		if (var_exists(cmds, i, len) == 1)
			del_var(cmds, i, len);
		i++;
	}
}
