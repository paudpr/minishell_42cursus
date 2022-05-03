/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:37:41 by pdel-pin          #+#    #+#             */
/*   Updated: 2021/10/28 12:14:59 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*t;

	if (!s1 || !s2)
		return (NULL);
	t = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (t == 0)
		return (NULL);
	if (s1 != 0 && s2 != 0)
	{
		ft_strlcpy(t, s1, ft_strlen(s1) + 1);
		ft_strlcat(t, s2, (ft_strlen(s1) + ft_strlen(s2) + 1));
		return (t);
	}
	return (0);
}
