/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:49:23 by pdel-pin          #+#    #+#             */
/*   Updated: 2021/10/28 12:15:03 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	i;
	size_t	d_len_save;

	d_len = ft_strlen(dst);
	d_len_save = ft_strlen(dst);
	if (dstsize == 0)
		return (ft_strlen(src));
	if (dstsize < d_len)
		return (ft_strlen(src) + dstsize);
	i = 0;
	while (src[i] != '\0' && d_len < (dstsize - 1))
	{
		dst[d_len] = src[i];
		i++;
		d_len++;
	}
	dst[d_len] = '\0';
	return (d_len_save + ft_strlen(src));
}
