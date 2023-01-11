/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_echo_pwd_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladelpinoramirez <pauladelpinoramire    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:52:21 by pdel-pin          #+#    #+#             */
/*   Updated: 2023/01/04 10:38:46 by pauladelpin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_flag_echo(t_cmds *cmds)
{
	int	i;

	i = 0;
	while (cmds->cmds_argv[1][i])
	{
		if (i == 0 && cmds->cmds_argv[1][i] == '-')
			i++;
		if (cmds->cmds_argv[1][i] == 'n')
			i++;
		else
			return (0);
	}
	return (1);
}

void	do_echo(t_cmds *cmds)
{
	int	flag;
	int	i;

	flag = 0;
	if (ft_double_len(cmds->cmds_argv) == 1)
		printf("\n");
	if (ft_double_len(cmds->cmds_argv) > 1)
	{
		i = 1;
		flag = check_flag_echo(cmds);
		if (flag > 0)
			i++;
		while (i < ft_double_len(cmds->cmds_argv))
		{
			printf("%s", cmds->cmds_argv[i]);
			if (i + 1 < ft_double_len(cmds->cmds_argv))
				printf(" ");
			i++;
		}
		if (flag == 0)
			printf("\n");
	}
	g_exit_status = 0;
}

void	do_pwd(t_cmds *cmds)
{
	char	pwd[PATH_MAX];

	(void)cmds;
	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
}

int check_alldigit(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	do_exit(t_cmds *cmds)
{
	int	len;

	len = ft_double_len(cmds->cmds_argv);
	printf("exit\n");			// este es el motivo por que me imprime exit incluso cuando está como ultimo comando
	if (len > 2)
	{
		if (!check_alldigit(cmds->cmds_argv[1]))
		{
			g_exit_status = 1;
			printf("minishell: exit: too many arguments\n");
		}
		else
		{
			g_exit_status = 255;
			printf("minishell: exit: %s: numeric argument required\n", cmds->cmds_argv[1]);
			exit(g_exit_status);
		}
	}
	else if (len == 2 && check_alldigit(cmds->cmds_argv[1]))
	{
		g_exit_status = 255;
		printf("minishell: exit: %s: numeric argument required\n", cmds->cmds_argv[1]);
	}
	else if (len == 1)
	{
		g_exit_status = 0;
		exit(0);
	}
}
