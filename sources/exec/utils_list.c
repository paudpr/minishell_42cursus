/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladelpinoramirez <pauladelpinoramire    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:53:01 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/11/13 22:53:45 by pauladelpin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_def	*mini_lstnew(void *content, int *array)
{
	t_def	*a;

	a = malloc(sizeof(t_def));
	if (a == 0)
		return (0);
	a->argv = ft_split(content, ' ');
	a->type = array;
	a->next = NULL;
	return (a);
}

void	mini_lstadd_back(t_def **lst, t_def *new)
{
	t_def	*p;
	
	if (!*lst)
		*lst = new;
	else
	{
		p = mini_lstlast(*lst);
		p->next = new;
	}
}

t_def	*mini_lstlast(t_def *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	mini_lstsize(t_def *def)
{
	int	i;

	i = 1;
	if (def == NULL)
		return (0);
	while (def->next != NULL)
	{
		def = def->next;
		i++;
	}
	return (i);
}