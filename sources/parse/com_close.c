/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:30:31 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/12/29 13:32:31 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if(num % 2 != 0)
	// wait_close_coms(str, num, flag);

void wait_close_coms(char *str, int num, char flag)
{
	(void)str;
	(void)num;
	(void)flag;
	return ;	
}

// char count_coms(char *read, char flag, int *coms)
// {
// 	int i;

// 	i = 0;

// 	while (i < ft_strlen(read))
// 	{
		
// 	}
// 	return (flag);
// }

// // si activo esto tengo que quitar en parse_com.c el error de comillas abiertas
// void	wait_close_coms(char *str, int *num, char flag)
// {
// 	int		coms;
// 	char	*aux;
// 	char	*read;

// 	printf("ENTRO AQUI\n");
// 	printf("str -> %s\nflag -> %c\n", str, flag);
// 	(void)num;
// 	(void)flag;

// 	coms = *num;
// 	read = NULL;
// 	while (1)
// 	{
// 		write(1, "> ", 2);
// 		read = get_next_line(0);
// 		flag = count_coms(read, flag, &coms);
// 		if(flag == 0)
// 			break ;
// 	}
// }
