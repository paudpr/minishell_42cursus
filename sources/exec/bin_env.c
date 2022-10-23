/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladelpinoramirez <pauladelpinoramire    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:52:25 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/10/22 13:12:37 by pauladelpin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_double_env(char **str)
{
	int	i;
	int	len;

	if (str == NULL)
		return ;
	i = 0;
	len = ft_double_len(str);
	while (i < len)
	{
		if (ft_strchr(str[i], '=') != 0)
			printf("%s\n", str[i]);
		i++;
	}
}

void	build_env(void)
{
	char	cwd[PATH_MAX];
	char	*shlvl;
	t_env	*copy;

	copy = ft_calloc(sizeof(t_env), 1);
	if (copy == NULL)
		return ;
	copy->env = ft_calloc(sizeof(char *), 3);
	if (copy->env == NULL)
		return ;
	getcwd(cwd, sizeof(cwd));
	copy->shlvl = 1;
	shlvl = ft_itoa(copy->shlvl);
	copy->env[0] = ft_strjoin("PWD=", cwd);
	copy->env[1] = ft_strjoin("SHLVL=", shlvl);
	free(shlvl);
	copy->env[2] = ft_strjoin("_=", cwd);
	print_double(copy->env);
	ft_free_double(copy->env);
	free(copy);
}

void	do_env(t_cmds *cmds)
{
	if (ft_double_len(cmds->cmds_argv) == 1)
	{
		if (ft_double_len(cmds->env->env) == 0)
			build_env();
		else
			print_double_env(cmds->env->env);
	}
	else
	{
		if (ft_double_len(cmds->cmds_argv) > 1)
			return ;
	}
}
