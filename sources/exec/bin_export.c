/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:52:30 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/10/03 15:52:31 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clean_var(char *new)
{
	int		i;
	int		length;
	char	*var;
	char	aux;

	var = NULL;
	length = ft_strlen(new);
	if (ft_strchr(new, '=') == 0)
		return (ft_strdup(new));
	else
	{
		aux = *(ft_strchr(new, '=') + 1);
		if (aux == 34 || aux == 39)
			length = length - 2;
		var = ft_calloc(length + 2, sizeof(char));
		i = -1;
		while (++i < length)
		{
			if (new[i] == 34 || new[i] == 39)
				i++;
			var[i] = new[i];
		}
	}
	return (var);
}

void	add_new_var(t_cmds *cmds, int i, int len)
{
	int		j;
	char	**new;

	j = -1;
	new = ft_calloc(len + 2, sizeof(char *));
	if (new == NULL)
		exit(0);
	while (++j < len)
		new[j] = ft_strdup(cmds->env->env[j]);
	new[j] = clean_var(cmds->cmds_argv[i]);
	ft_free_double(cmds->env->env);
	cmds->env->env = new;
}

void	transform_var(t_cmds *cmds, int i, int len)
{
	int		j;
	int		length;
	char	*other;
	int		length_2;
	char	*other_2;

	other = ft_strchr(cmds->cmds_argv[i], '=');
	length = ft_strlen(cmds->cmds_argv[i]) - ft_strlen(other);
	j = 0;
	while (j < len)
	{
		other_2 = ft_strchr(cmds->env->env[j], '=');
		length_2 = ft_strlen(cmds->env->env[j]) - ft_strlen(other_2);
		if (ft_strncmp(cmds->cmds_argv[i], cmds->env->env[j], length) == 0
			&& length == length_2)
		{
			free(cmds->env->env[j]);
			cmds->env->env[j] = clean_var(cmds->cmds_argv[i]);
		}
		j++;
	}
}

void	add_var(t_cmds *cmds, int i)
{
	int	len;

	len = ft_double_len(cmds->env->env);
	if (check_valid_var(cmds, i) != 0)
	{
		if (var_exists(cmds, i, len) == 1)
		{
			if (ft_strchr(cmds->cmds_argv[i], '=') != 0)
				transform_var(cmds, i, len);
			else
				return ;
		}
		else
			add_new_var(cmds, i, len);
	}
}

void	do_export(t_cmds *cmds)
{	
	int		i;
	int		len;
	char	**copy;

	i = 1;
	copy = NULL;
	len = ft_double_len(cmds->cmds_argv);
	if (len == 1)
	{
		copy = sort_double(cmds->env->env);
		print_double_export(copy);
		ft_free_double(copy);
	}
	else
	{
		while (i < len)
		{
			add_var(cmds, i);
			i++;
		}
	}
}
