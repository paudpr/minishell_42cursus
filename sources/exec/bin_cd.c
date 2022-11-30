/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:52:18 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/11/30 11:00:25 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// norminette division
void	do_cd_return_dir(t_cmds *cmds, char *new)
{
	char	dir[PATH_MAX];

	getcwd(dir, sizeof(dir));
	change_var(cmds->env, "OLDPWD=", dir);
	chdir(ft_strchr(new, '/'));
	free(new);
	getcwd(dir, sizeof(dir));
	change_var(cmds->env, "PWD=", dir);
	printf("%s\n", dir);
}

//vuelve al ultimo directorio donde ha estado. cd -
void	cd_return_dir(t_cmds *cmds)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	j = 0;
	new = NULL;
	while (++i < ft_double_len(cmds->env->env))
	{
		if (ft_strncmp(cmds->env->env[i], "PWD=", ft_strlen("PWD=")) == 0)
			j++;
		if (ft_strncmp(cmds->env->env[i], "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
			new = ft_strdup(cmds->env->env[i]);
	}
	if (j != 1 || new == NULL)
		printf("minishell: cd: OLDPWD not set\n");
	else
		do_cd_return_dir(cmds, new);
}

static char	*cd_rel_dir(t_cmds *cmds)
{
	char	*start;
	char	*new;

	start = ft_strdup("/Users/pdel-pin");
	new = ft_strjoin(start, ft_strchr(cmds->cmds_argv[1], '/'));
	free(start);
	return (new);
}

// va al directorio indicado. cd (path)
void	cd_move_dir(t_cmds *cmds)
{
	char	*new;
	char	dir[PATH_MAX];

	new = NULL;
	if (cmds->cmds_argv[1][0] == '~')
		new = cd_rel_dir(cmds);
	else
		new = ft_strdup(cmds->cmds_argv[1]);
	getcwd(dir, sizeof(dir));
	if (chdir(new) != 0)
		perror("minishell: cd");
	else
	{
		change_var(cmds->env, "OLDPWD=", dir);
		chdir(new);
		getcwd(dir, sizeof(dir));
		change_var(cmds->env, "PWD=", dir);
	}
	free(new);
}

// void create_oldpwd(t_cmds *cmds)	// crea old pwd si no existe
									// no existe si no hay entorno
// {
// 	int i;
// 	int check;
// 	char **copy;

// 	i = -1;
// 	check = 0;
// 	while (++i < ft_double_len(cmds->env->env))
// 	{
// 		if (!ft_strncmp("OLDPWD=", cmds->env->env[i], ft_strlen("OLDPWD=")))
// 			check++;
// 	}
// 	if (check == 1)
// 	{
// 		copy = malloc(sizeof(char *) * (ft_double_len(cmds->env->env) + 1));
// 		i = -1;
// 		while (++i < ft_double_len(cmds->env->env))
// 			copy[i] = ft_strdup(cmds->env->env[i]);
// 		copy[i] = ft_strdup("OLDPWD=");
// 		copy[i + 1] = 0;
// 		ft_free_double(cmds->env->env);
// 		cmds->env->env = copy;
// 	}
// }

void	do_cd(t_cmds *cmds)
{
	size_t	len;

	len = ft_strlen(cmds->cmds_argv[1]);
	if (ft_double_len(cmds->cmds_argv) == 1)
		cd_home_dir(cmds);
	else if (ft_double_len(cmds->cmds_argv) > 1)
	{
		if (ft_strncmp(cmds->cmds_argv[1], "..", len) == 0
			&& len == ft_strlen(".."))
			cd_back_dir(cmds);
		else if (ft_strncmp(cmds->cmds_argv[1], ".", len) == 0
			&& len == ft_strlen("."))
			return ;
		else if (ft_strncmp(cmds->cmds_argv[1], "-", len) == 0
			&& len == ft_strlen("-"))
			cd_return_dir(cmds);
		else
			cd_move_dir(cmds);
	}
}
