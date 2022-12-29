/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_echo_pwd_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:52:21 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/12/29 15:21:00 by pdel-pin         ###   ########.fr       */
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

void	do_exit(t_cmds *cmds)
{
	int	len;
	int	code;

	len = ft_double_len(cmds->cmds_argv);
	printf("exit\n");
	if (len > 2)
	{
		g_exit_status = 255;
		printf("minishell: exit: too many arguments\n");
	}
	else if (len == 2)
	{
		code = ft_atoi(cmds->cmds_argv[1]);
		exit(code);
	}
	else if (len == 1)
		exit(0);
}

// primero que sean numericos -> si hace exit y codigo 255
// comprobar qque todos los argumentos sean numericos code = 255 y si hacce exit
// comprobar que solo haya uno o hay error de muchos argumentos code = 1 y no hace exit