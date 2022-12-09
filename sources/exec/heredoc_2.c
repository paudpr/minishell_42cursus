/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:52:45 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/12/09 13:14:31 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_hd(int hd)
{
	int		i;
	char	*num;
	char	*name;

	i = 0;
	while (i < hd)
	{
		num = ft_itoa(i);
		name = ft_strjoin("/tmp/heredoc", num);
		// printf("clean_hd -> %p\t%p\n", num, name);
		unlink(name);
		free(name);
		free(num);
		i++;
	}
}
