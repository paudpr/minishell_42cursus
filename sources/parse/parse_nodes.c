#include "minishell.h"

void print_nodes(t_def *def)
{
	int i;

	while(def)
	{
		printf("%p\t%p\n", def, def->next);
		i = -1;
		while(++i < ft_double_len(def->argv))
			printf("%s\t", def->argv[i]);
		i = -1;
		printf("\n");
		while(++i < ft_double_len(def->argv))
			printf("%d\t", def->type[i]);
		printf("\n\n");
		def = def->next;
	}
}

int clean_redir(t_list *lst)
{
	char *tmp;
	t_list *aux;

	aux = NULL;
	while(lst)
	{
		if(!ft_strncmp(lst->content, "<", 1) || !ft_strncmp(lst->content, ">", 1))
		{
			if(!lst->next)
			{
				printf("minishell: syntax error near unexpected token `newline`\n");
				return(1);
			}
			if(!ft_strncmp(lst->next->content, "<", 1) || !ft_strncmp(lst->next->content, ">", 1))
			{
				tmp = ft_strdup(lst->content);
				free(lst->content);
				lst->content = ft_strjoin(tmp, lst->next->content);
				free(tmp);
				aux = lst->next;
				lst->next = lst->next->next;
				free(aux->content);
				free(aux);
				if(!lst->next)
				{
					printf("minishell: syntax error near unexpected token `newline`\n");
					return(1);
				}
			}
		}
		lst = lst->next;
	}
	return(0);
}


int count_argvs(t_list *lst)
{
	int count;

	count = 0;
	
	while(lst)
	{
		if(!ft_strncmp(lst->content, "|", 1))
			break;
		count++;
		lst = lst->next;
	}
	return(count);
}

int get_type(char *argv)
{
	int type;

	if(!ft_strncmp(argv, "<<", 2))
		type = T_HD;
	else if(!ft_strncmp(argv, "<", 1))
		type = T_RIN;
	else if(!ft_strncmp(argv, ">>", 2))
		type = T_APP;
	else if(!ft_strncmp(argv, ">", 1))
		type = T_ROUT;
	else
		type = T_CMD;
	return(type);
}

t_def *create_node(int size, t_list *lst)
{
	int i;
	t_def *new;

	new = ft_calloc(1, sizeof(t_def));
	if(new == NULL)
		return(new);
	new->argv = ft_calloc(size + 1, sizeof(char *));
	if(new->argv == NULL)
		return(NULL);
	new->type = ft_calloc(size + 1, sizeof(int));
	if(new->type == NULL)
		return(NULL);
	i = 0;
	while(i < size)
	{
		new->argv[i] = ft_strdup(lst->content);
		new->type[i] = get_type(new->argv[i]);
		if(new->type[i] && new->type[i] < 5)
		{
			i++;
			lst = lst->next;
			new->argv[i] = ft_strdup(lst->content);
			new->type[i] = new->type[i - 1];
			if (i >= size) 
				break ;
		}
		i++;
		lst = lst->next;
	}
	return(new);
}

t_def *parse_nodes(t_list *lst)
{
	int	size;
	int flag;
	t_def *new;
	t_def *nodes;

	size = 0;
	flag = 0;
	nodes = NULL;
	if(clean_redir(lst))
		return(NULL);
	while(lst)
	{
		if(size == 0)
		{
			size = count_argvs(lst);
			flag = 1;
		}
		if(flag == 1)
		{
			new = create_node(size, lst);
			mini_lstadd_back(&nodes, new);
			flag = 0;
		}
		size--;
		lst = lst->next;
		if(size == 0 && lst && lst->next)
			lst = lst->next;
	}
	// print_nodes(nodes);
	return(nodes);
}
