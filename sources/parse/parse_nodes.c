#include "minishell.h"

void	print_nodes(t_def *def)
{
	int	i;

	while (def)
	{
		printf("%p\t%p\n", def, def->next);
		i = -1;
		while (++i < ft_double_len(def->argv))
			printf("%s\t", def->argv[i]);
		i = -1;
		printf("\n");
		while (++i < ft_double_len(def->argv))
			printf("%d\t", def->type[i]);
		printf("\n\n");
		def = def->next;
	}
}

int	count_argvs(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		if (!ft_strncmp(lst->content, "|", 1))
			break ;
		count++;
		lst = lst->next;
	}
	return (count);
}

int	get_type(char *argv)
{
	int	type;

	if (!ft_strncmp(argv, "<<", 2))
		type = T_HD;
	else if (!ft_strncmp(argv, "<", 1))
		type = T_RIN;
	else if (!ft_strncmp(argv, ">>", 2))
		type = T_APP;
	else if (!ft_strncmp(argv, ">", 1))
		type = T_ROUT;
	else if ((!ft_strncmp(argv, "*", 1) && ft_strlen(argv) == 1)
		|| argv[0] == '*' || argv[ft_strlen(argv) - 1] == '*')
		type = T_WC;
	else
		type = T_CMD;
	return (type);
}

// t_list *clean_files_start(t_list **lst, char *argv)
// {
// 	t_list *prev;
// 	t_list *aux;

// 	aux = *lst;
// 	prev = NULL;
// 	print_list(*lst);
// 	printf("-------------\n");
// 	while (aux)
// 	{
// 		printf("%p\t%p\t%s\n", aux, aux->next, aux->content);
// 		printf("prev -> %p\n", prev);
// 		if (!ft_strncmp(argv, aux->content, ft_strlen(argv)))
// 		{
// 			printf("entro 1\n");
// 			if(prev == NULL)
// 			{
// 				printf("entro 1.1\n");
// 				*lst = aux->next;
// 				free(aux);
// 				aux = *lst;
// 			}
// 			else
// 			{
// 				printf("entro 1.2\n");
// 				prev->next = aux->next;
// 				free(aux);
// 				aux = prev->next;
// 			}
// 		}
// 		else
// 		{
// 			printf("entro aqui 2\n");
// 			printf("%p\t%d\n", prev, 0);
// 			printf("%p\t%p\n\n", aux, aux->next);
// 			free(prev);
// 			// printf("%p\t%p\n", prev, prev->next);
// 			printf("%p\t%p\n\n", aux, aux->next);
// 			prev = aux;
// 			printf("%p\t%p\n", prev, prev->next);
// 			printf("%p\t%p\n\n", aux, aux->next);
// 			free(aux);
// 			printf("%p\t%p\n", prev, prev->next);
// 			// printf("%p\t%p\n\n", aux, aux->next);
// 			aux = prev->next;
// 			printf("%p\t%p\n", prev, prev->next);
// 			printf("%p\t%p\n\n", aux, aux->next);
// 		}
// 	}
// 	return(*lst);
// }

t_list *clean_files_start(t_list **lst, char *argv)
{
	int		i;
	int		len;
	t_list	*aux;
	t_list	*prev;
	t_list	*del;

	i = 0;
	aux = *lst;
	prev = NULL;
	len = ft_strlen(argv);
	while (aux)
	{
		if(i == 0 && !ft_strncmp(argv, aux->content, len))
		{
			del = *lst;
			lst = &aux->next;
			aux = aux->next;
			free_lst(del);
		}
		else if (!ft_strncmp(argv, aux->content, len))
		{
			del = aux;
			prev->next = aux->next;
			aux = aux->next;
			if (!aux->next)
				break;
			aux = aux->next;
			prev = prev->next;
			free(del);
		}
		else
		{
			prev = aux;
			aux = aux->next;
		}
		i++;
	}
	return(*lst);
}

t_list *clean_files_end(t_list **lst, char *argv)
{
	int len;

	len = ft_strlen(argv);
	return(*lst);
}


t_list *get_files(int type, char *argv)
{
	DIR *dir;
	struct dirent *items;
	t_list *lst;
	char check_hidden;

	lst = NULL;
	dir = opendir(".");
	if (dir != NULL)
	{
		items = readdir(dir);
		while((items = readdir(dir)) != NULL)
		{
			check_hidden = (char)items->d_name[0];
			if (check_hidden != '.')
				ft_lstadd_back(&lst, ft_lstnew(ft_strdup(items->d_name)));
		}
	}
	//habria que ordenarlo alfabéticamente antes de devolver la lista 
	closedir(dir);
	printf("get_files -> %s\t%s\n", ft_substr(argv, 1, ft_strlen(argv) - 1), ft_substr(argv, 0, ft_strlen(argv) - 1));
	if (type == 1)
		lst = clean_files_end(&lst, ft_substr(argv, 1, ft_strlen(argv) - 1));
	if (type == 2)
		lst = clean_files_start(&lst, ft_substr(argv, 0, ft_strlen(argv) - 1));
	return(lst);
}

t_def *get_wildcard(t_def **node, char *argv, int type)
{
	int i;
	int j;
	t_def *new;
	t_list *lst;
	t_list *aux;

	if (ft_strlen(argv) != 1)
	{
		if (argv[0] == '*')
			type = 1;
		else
			type = 2;
	}
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
	return(new);
}

t_def	*create_node(int size, t_list *lst)
{
	int		i;
	t_def	*new;

	new = ft_calloc(1, sizeof(t_def));
	if (new == NULL)
		return (new);
	new->argv = ft_calloc(size + 1, sizeof(char *));
	if (new->argv == NULL)
		return (NULL);
	new->type = ft_calloc(size + 1, sizeof(int));
	if (new->type == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new->argv[i] = ft_strdup(lst->content);
		new->type[i] = get_type(new->argv[i]);
		printf("++ %s\n", new->argv[i]);
		if (new->type[i] && new->type[i] < 5)
		{
			i++;
			lst = lst->next;
			new->argv[i] = ft_strdup(lst->content);
			new->type[i] = new->type[i - 1];
			if (i >= size)
				break ;
		}
		if (new->type[i] && new->type[i] == 6)
			new = get_wildcard(&new, new->argv[i], 0);
		i++;
		lst = lst->next;
	}
	return (new);
}

t_def	*parse_nodes(t_list *lst, t_env *env)
{
	int		size;
	int		flag;
	t_def	*new;
	t_def	*nodes;

	size = 0;
	flag = 0;
	nodes = NULL;
	while (lst)
	{
		if (size == 0)
		{
			size = count_argvs(lst);
			flag = 1;
		}
		if (flag == 1)
		{
			new = create_node(size, lst);
			clean_com(new->argv, env);
			mini_lstadd_back(&nodes, new);
			flag = 0;
		}
		size--;
		lst = lst->next;
		if (size == 0 && lst && lst->next)
			lst = lst->next;
	}
	return (nodes);
}
