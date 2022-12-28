#include "minishell.h"

t_list *clean_files_start(t_list *lst, char *argv)
{
	t_list	*new;
	t_list	*aux;

	new = NULL;
	aux = lst;
	print_list(aux);
	while (aux)
	{
		if (!ft_strncmp(aux->content, argv, ft_strlen(argv)))
			ft_lstadd_back(&new, ft_lstnew(aux->content));
		aux = aux->next;
	}
	
	print_list(lst);
	free(argv);
	if (ft_lstsize(new) == 0)
		return (lst);
	return (new);
}


// t_list	*clean_files_end(t_list **lst, char *argv)
// {
// 	int	len;

// 	len = ft_strlen(argv);
// 	free(argv);
// 	return (*lst);
// }

t_list	*get_files(int type, char *argv)
{
	DIR				*dir;
	struct dirent	*items;
	t_list			*lst;
	t_list			*aux;
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
	aux = NULL;
	// if (type == 1)
	// 	aux = clean_files_end(&lst, ft_substr(argv, 0, ft_strlen(argv) - 1));
	if (type == 2)
		aux = clean_files_start(lst, ft_substr(argv, 0, ft_strlen(argv) - 1));
	// print_list(aux);																	// por algun motivo estos dos comparten la dirección de memoria, aunque no tienen el mismo contenido
	// print_list(lst);
	if (type == 1 || type == 2)
	{
		printf("-> es wildcard complejo - %i \n", type);
		// printf("%p\t%p\t%s\n", aux, aux->next, aux->content);
		
		free_lst(lst);			// hace que el return de despues pete por que tienen la misma dirección de memoria por algún motivo de aux
		
		// printf("%p\t%p\t%s\n", aux, aux->next, aux->content);
		return (aux);
	}
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
t_def	*get_wildcard(t_def **node, char *argv, int type)
{
	int		i;
	int		j;
	t_def	*new;
	t_list	*lst;
	t_list	*aux;

	type = type_wildcard(argv);
	lst = get_files(type, argv);
	printf("%p\t%p\t%s\n", lst, lst->next, lst->content);
	printf("---------------------> lista limpia \n");
	new = get_wildcard_norm(ft_double_len((*node)->argv) - 1 + ft_lstsize(lst));
	if (lst == NULL || new == NULL)
		return (*node);
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
	// print_nodes(new);
	// free_lst(aux);
	free_list(node);
	return (new);
}


// static void get_wildcard_norm2(t_def **node, int j, t_list *lst, char *argv)
// {
	
// }





// new, j, lst, (*node)->argv[i]