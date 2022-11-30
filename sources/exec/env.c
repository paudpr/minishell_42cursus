/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:52:39 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/11/30 16:17:50 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_last_exec_aux(t_cmds *cmds, char *cmd, int i)
{
	int		index;
	char	*aux;
	char	*aux2;

	if (ft_double_len(cmds->cmds_argv) < 2)
		cmds->env->env[i] = ft_strjoin("_=", cmd);
	else
	{
		aux = ft_strjoin("_=", cmd);
		aux2 = ft_strjoin(aux, " ");
		free(aux);
		index = ft_double_len(cmds->cmds_argv) - 1;
		cmds->env->env[i] = ft_strjoin(aux2, cmds->cmds_argv[index]);
		free(aux2);
	}
}

void	change_last_exec(t_cmds *cmds, char *cmd, int type)
{
	int		i;

	i = ft_double_len(cmds->env->env) - 1;
	while (i >= 0)
	{
		if (!ft_strncmp(cmds->env->env[i], "_=", 2))
		{
			free(cmds->env->env[i]);
			if (type == 1)
				change_last_exec_aux(cmds, cmd, i);
			else
				cmds->env->env[i] = ft_strjoin("_=", cmd);
		}
		i--;
	}
	free(cmd);
}

t_env	*get_struct_env(char **environ)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	if (ft_double_len(environ) == 0)
	{
		env->shlvl = 1;
		build_environ(env);
	}
	else
		copy_environ(environ, env);
	return (env);
}

void	build_environ(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*shlvl;

	env->env = ft_calloc(sizeof(char *), 3);
	if (env->env == NULL)
		return ;
	getcwd(cwd, sizeof(cwd));
	env->shlvl = 1;
	shlvl = ft_itoa(env->shlvl);
	env->env[0] = ft_strjoin("PWD=", cwd);
	env->env[1] = ft_strjoin("SHLVL=", shlvl);
	free(shlvl);
	env->env[2] = ft_strjoin("_=", cwd);
}

void	copy_environ(char **environ, t_env *env)
{
	int		i;
	char	*point;
	char	*aux_shlvl;
	char	*shlvl;

	i = 0;
	env->env = ft_calloc(sizeof(char *), ft_double_len(environ) + 1);
	if (env->env == NULL)
		return ;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "SHLVL=", 6))
			env->env[i] = ft_strdup(environ[i]);
		else
		{
			aux_shlvl = ft_strdup(environ[i]);
			point = ft_strchr(aux_shlvl, '=') + 1;
			env->shlvl = ft_atoi(point) + 1;
			shlvl = ft_itoa(env->shlvl);
			env->env[i] = ft_strjoin("SHLVL=", shlvl);
			free(aux_shlvl);
			free(shlvl);
		}
		i++;
	}
}
