/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cd_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:52:16 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/10/03 15:52:17 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_var(t_env *env, char *var, char *new)
{
	int		i;
	char	*copy;

	i = 0;
	while (i < ft_double_len(env->env))
	{
		if (ft_strncmp(env->env[i], var, ft_strlen(var)) == 0)
		{
			copy = ft_strjoin(var, new);
			free(env->env[i]);
			env->env[i] = ft_strdup(copy);
			free(copy);
			return ;
		}
		i++;
	}
}

//va al home. cd
void	cd_home_dir(t_cmds *cmds)
{
	int		i;
	char	*home;
	char	dir[PATH_MAX];

	getcwd(dir, sizeof(dir));
	i = 0;
	home = NULL;
	while (i < ft_double_len(cmds->env->env))
	{
		if (ft_strncmp(cmds->env->env[i], "HOME=", ft_strlen("HOME=")) == 0)
			home = ft_strchr(cmds->env->env[i], '/');
		i++;
	}
	if (home != NULL)
	{
		change_var(cmds->env, "OLDPWD=", dir);
		chdir(home);
		getcwd(dir, sizeof(dir));
		change_var(cmds->env, "PWD=", dir);
	}
	else
		printf("minishell: cd: HOME not set\n");
}

//va un directorio hacia atrás. cd ..
void	cd_back_dir(t_cmds *cmds)
{
	char	dir[PATH_MAX];
	char	*last;
	char	*new_dir;

	getcwd(dir, sizeof(dir));
	change_var(cmds->env, "OLDPWD=", dir);
	last = ft_strrchr(dir, '/') + 1;
	new_dir = ft_substr(dir, 0, ft_strlen(dir) - ft_strlen(last));
	chdir(new_dir);
	change_var(cmds->env, "PWD=", new_dir);
	free(new_dir);
}
