/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 13:12:26 by pdel-pin          #+#    #+#             */
/*   Updated: 2021/10/28 12:13:02 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	if (!dst && !src)
		return (0);
	if (d > s)
	{
		d += len;
		s += len;
		while (len--)
			*(unsigned char *)--d = *(unsigned char *)--s;
	}
	else
	{
		while (len--)
		{
			*(unsigned char *)d = *(unsigned char *)s;
			d++;
			s++;
		}
	}
	return (dst);
}
