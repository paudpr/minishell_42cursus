/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:08:46 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/05/03 18:44:51 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_len(int n)
{
	size_t	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_build_str(size_t len, char *str, int n, int neg)
{
	str[len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
	}
	if (neg)
		str[0] = '-';
}

char	*ft_itoa(int n)
{
	int		neg;
	size_t	len;
	char	*str;

	neg = 0;
	if (n < 0)
	{
		neg = 1;
		n *= -1;
	}
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_get_len(n) + neg;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (0);
	ft_build_str(len, str, n, neg);
	return (str);
}
