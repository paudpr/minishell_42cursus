/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:52:27 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/12/29 15:08:07 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_double_export(char **str)
{
	int	i;
	int	j;
	int	len;

	if (str == NULL)
		return ;
	i = 0;
	len = ft_double_len(str);
	while (i < len)
	{
		j = -1;
		if (i == 2)
			printf("declare -x EASTER_EGG=\"Dan\"\n");
		printf("declare -x ");
		while (str[i][++j] != '=' && str[i][j])
			printf("%c", str[i][j]);
		if (ft_strchr(str[i], '=') != 0)
		{
			printf("=\"");
			printf("%s", ft_strchr(str[i], '=') + 1);
			printf("\"");
		}
		printf("\n");
		i++;
	}
}

int	check_valid_var(t_cmds *cmds, int i)
{
	int	j;

	if (ft_isalpha(cmds->cmds_argv[i][0]) != 1)
	{
		g_exit_status = 1;
		perror("minishell: export: not a valid identifier");
		return (0);
	}
	j = 1;
	while (j < (int)ft_strlen(cmds->cmds_argv[i])
		&& cmds->cmds_argv[i][j] != '=')
	{
		if (ft_isalnum(cmds->cmds_argv[i][j]) != 1)
		{
			g_exit_status = 1;
			perror("minishell: export: not a valid identifier");
			return (0);
		}
		j++;
	}
	return (1);
}
