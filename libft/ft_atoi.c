/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:06:28 by pdel-pin          #+#    #+#             */
/*   Updated: 2021/10/28 11:31:05 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				i;
	int				r;
	unsigned int	sol;

	i = 0;
	r = 1;
	sol = 0;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			r = -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		sol = (sol * 10) + (str[i] - 48);
		if (sol > 2147483657 && r == 1)
			return (-1);
		if (sol > 2147483648 && r == -1)
			return (0);
		i++;
	}
	return (sol * r);
}
