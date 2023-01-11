/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladelpinoramirez <pauladelpinoramire    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:29:11 by pdel-pin          #+#    #+#             */
/*   Updated: 2023/01/04 09:59:30 by pauladelpin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *clean_files_start(t_list *lst, char *argv)		// hace leaks
{
	t_list	*new;
	t_list	*aux;

	new = NULL;
	aux = lst;
	while (aux)
	{
		// printf("%p\n", aux);			// leakkkkkksssssss
		if (!ft_strncmp(aux->content, argv, ft_strlen(argv)))
			ft_lstadd_back(&new, ft_lstnew(aux->content));
		aux = aux->next;
	}
	free(argv);
	if (ft_lstsize(new) == 0)
		return (lst);
	// free_lst(lst);			// esto peta sanitizer
	return (new);
}

t_list	*clean_files_end(t_list *lst, char *argv)		// también hace leaks
{
	char	*copy;
	t_list	*new;
	t_list	*aux;

	new = NULL;
	aux = lst;
	while (aux)
	{
		copy = ft_strrchr(aux->content, argv[0]);
		if (!ft_strncmp(aux->content, copy, ft_strlen(copy)))
			ft_lstadd_back(&new, ft_lstnew(aux->content));
		aux = aux->next;
	}
	free(argv);
	if (ft_lstsize(new) == 0)
		return (lst);
	return (new);
}

t_list	*get_files(int type, char *argv)
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
	if(type == 0)
		return (lst);
	else if (type == 2)
		return (clean_files_start(lst, ft_substr(argv, 0, ft_strlen(argv) - 1)));
	else if (type == 1)
		return (clean_files_end(lst, ft_substr(argv, 1, ft_strlen(argv) - 1)));
	return (lst);
}

int	type_wildcard(char *argv)
{
	int	type;

	type = 0;
	if (ft_strlen(argv) != 1)
	{
		if (argv[0] == '*')
			type = 1;
		else
			type = 2;
	}
	return (type);
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

//tiene que devolver una lista con los argumentos revisados
t_def	*get_wildcard(t_def **node, char *argv, int type, int *i)
{
	int		j;
	int		len;
	t_def	*new;
	t_list	*lst;
	t_list	*aux;

	type = type_wildcard(argv);
	lst = get_files(type, argv);
	len = ft_double_len((*node)->argv) - 1 + ft_lstsize(lst);
	new = get_wildcard_norm(len);
	if (lst == NULL || new == NULL)
		return (*node);
	j = 0;
	aux = lst;
	while (j < len)
	{
		if ((*node)->type[j] != T_WC && j < ft_double_len((*node)->argv))
		{
			new->argv[j] = ft_strdup((*node)->argv[j]);
			new->type[j] = (*node)->type[j];
			j++;
		}
		else
		{
			while (aux)
			{
				new->argv[j] = ft_strdup(aux->content);
				new->type[j] = T_CMD;
				aux = aux->next;
				j++;
			}	
		}
	}
	*i = j;
	free_lst(lst);
	free_def(node);
	return (new);
}
