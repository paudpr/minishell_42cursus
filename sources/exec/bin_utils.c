/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:52:34 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/10/03 15:52:35 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// used by unset and export
int	var_exists(t_cmds *cmds, int i, int len)
{
	int		j;
	int		length;
	int		flag;
	char	*other;

	j = 0;
	flag = 0;
	other = ft_strchr(cmds->cmds_argv[i], '=');
	length = ft_strlen(cmds->cmds_argv[i]) - ft_strlen(other);
	while (j < len)
	{
		if (ft_strncmp(cmds->cmds_argv[i], cmds->env->env[j], length) == 0)
			flag = 1;
		j++;
	}
	return (flag);
}
