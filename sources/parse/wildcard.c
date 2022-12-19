#include "minishell.h"

// t_list	*clean_files_start(t_list **lst, char *argv)
// {
// 	int		i;
// 	int		len;
// 	t_list	*aux;
// 	t_list	*prev;
// 	t_list	*del;

// 	i = 0;
// 	aux = *lst;
// 	prev = NULL;
// 	len = ft_strlen(argv);
// 	while (aux)
// 	{
// 		if(i == 0 && !ft_strncmp(argv, aux->content, len))
// 		{
// 			del = *lst;
// 			lst = &aux->next;
// 			aux = aux->next;
// 			free_lst(del);
// 		}
// 		else if (!ft_strncmp(argv, aux->content, len))
// 		{
// 			del = aux;
// 			prev->next = aux->next;
// 			aux = aux->next;
// 			if (!aux->next)
// 				break ;
// 			aux = aux->next;
// 			prev = prev->next;
// 			free(del);
// 		}
// 		else
// 		{
// 			prev = aux;
// 			aux = aux->next;
// 		}
// 		i++;
// 	}
// 	return (*lst);
// }

// t_list	*clean_files_end(t_list **lst, char *argv)
// {
// 	int	len;

// 	len = ft_strlen(argv);
// 	return (*lst);
// }

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
	(void)type;
	(void)argv;
	// printf("get_files -> %d\t%s\t%s\n", type, ft_substr(argv, 1, ft_strlen(argv) - 1), ft_substr(argv, 0, ft_strlen(argv) - 1));
	// if (type == 1)
	// 	lst = clean_files_end(&lst, ft_substr(argv, 1, ft_strlen(argv) - 1));
	// if (type == 2)
	// 	lst = clean_files_start(&lst, ft_substr(argv, 0, ft_strlen(argv) - 1));
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

//tiene que devolver una lista con los argumentos revisados
t_def	*get_wildcard(t_def **node, char *argv, int type)
{
	int		i;
	int		j;
	t_def	*new;
	t_list	*lst;
	t_list	*aux;

	type = type_wildcard(argv);
	lst = get_files(type, argv);
	if (lst == NULL)
		return (*node);
	new = ft_calloc(1, sizeof(t_def));
	if (new == NULL)
		return (new);
	i = ft_double_len((*node)->argv) - 1 + ft_lstsize(lst);
	new->argv = ft_calloc(i + 1, sizeof(char *));
	if (new->argv == NULL)
		return (NULL);
	new->type = ft_calloc(i + 1, sizeof(int));
	if (new->type == NULL)
		return (NULL);
	i = 0;
	j = 0;
	aux = lst;
	while (i < ft_double_len((*node)->argv))
	{
		if (!ft_strncmp((*node)->argv[i], "*", 1))
		{
			while (lst)
			{
				new->argv[j] = ft_strdup(lst->content);
				new->type[j] = 5;
				j++;
				lst = lst->next;
			}
		}
		else
		{
			new->argv[j] = ft_strdup((*node)->argv[i]);
			new->type[j] = (*node)->type[i];
			j++;
		}
		i++;
	}
	free_lst(aux);
	free_list(node);
	return (new);
}
