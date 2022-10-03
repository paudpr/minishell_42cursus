/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:53:04 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/10/03 15:53:05 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}

void	wait_process(t_def *def)
{
	int	i;
	int	*s;

	s = NULL;
	i = mini_lstsize(def);
	while (i)
	{
		waitpid(-1, s, 0);
		i--;
	}
}

void	print_double(char **str)
{
	int	i;
	int	len;

	if (str == NULL)
		return ;
	i = 0;
	len = ft_double_len(str);
	while (i < len)
	{
		printf("%s\n", str[i]);
		i++;
	}
}

char	**sort_double(char **str)
{
	int		i;
	int		j;
	int		len;
	int		index;
	char	**sorted;

	len = ft_double_len(str);
	sorted = ft_calloc(sizeof(char *), len + 1);
	i = 0;
	while (i < len)
	{
		j = 0;
		index = 0;
		while (j < len)
		{
			if (ft_strncmp(str[i], str[j], ft_strlen(str[i])) > 0)
				index++;
			j++;
		}
		sorted[index] = ft_strdup(str[i]);
		i++;
	}
	return (sorted);
}
