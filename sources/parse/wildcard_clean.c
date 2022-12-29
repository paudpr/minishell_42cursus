/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:29:08 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/12/29 11:29:09 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_files(void)
{
	DIR				*dir;
	struct dirent	*items;
	t_list			*lst;
	char			check_hidden;

	lst = NULL;
	dir = opendir(".");
	if (dir != NULL)
	{
		items = readdir(dir);
		while (items)
		{
			check_hidden = (char)items->d_name[0];
			if (check_hidden != '.')
				ft_lstadd_back(&lst, ft_lstnew(ft_strdup(items->d_name)));
			items = readdir(dir);
		}
	}
	closedir(dir);
	return (lst);
}

static t_def	*get_wildcard_norm(int i)
{
	t_def	*new;

	new = ft_calloc(1, sizeof(t_def));
	if (new == NULL)
		return (new);
	new->argv = ft_calloc(i + 1, sizeof(char *));
	if (new->argv == NULL)
		return (NULL);
	new->type = ft_calloc(i + 1, sizeof(int));
	if (new->type == NULL)
		return (NULL);
	return (new);
}

void	wildcard_argv_norm1(t_list *lst, t_def **new, int *j)
{
	int	i;

	i = *j;
	while (lst)
	{
		(*new)->argv[i] = ft_strdup(lst->content);
		(*new)->type[i] = 5;
		i++;
		lst = lst->next;
	}
	*j = i;
}

void	wildcard_argv_norm2(t_def **new, t_def *node, int *j, int k)
{
	int	i;

	i = *j;
	(*new)->argv[i] = ft_strdup(node->argv[k]);
	(*new)->type[i] = node->type[k];
	i++;
	*j = i;
}

t_def	*get_wildcard(t_def **node)
{
	int		i;
	int		j;
	t_def	*new;
	t_list	*lst;
	t_list	*aux;

	lst = get_files();
	aux = lst;
	new = get_wildcard_norm(ft_double_len((*node)->argv) - 1 + ft_lstsize(lst));
	if (lst == NULL || new == NULL)
		return (*node);
	i = 0;
	j = 0;
	while (i < ft_double_len((*node)->argv))
	{
		if (!ft_strncmp((*node)->argv[i], "*", 1))
			wildcard_argv_norm1(lst, &new, &j);
		else
			wildcard_argv_norm2(&new, *node, &j, i);
		i++;
	}
	free_lst(aux);
	free_list(node);
	return (new);
}
