/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:17:08 by pdel-pin          #+#    #+#             */
/*   Updated: 2021/10/28 12:15:31 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (len && haystack[i])
	{
		n = 0;
		while (haystack[i + n] != 0
			&& haystack[i + n] == needle[n] && len - n > 0)
		{
			if (needle[n + 1] == '\0')
				return ((char *)&haystack[i]);
			n++;
		}
		i++;
		len--;
	}
	return (NULL);
}
