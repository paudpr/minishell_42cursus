#include "minishell.h"

void print_nodes(t_def *def)
{
	int i;

	while(def)
	{
		printf("%p\t\t%p\n", def, def->next);
		printf("%d\t\t", *(def)->type);
		i = -1;
		while(def->argv[++i])
			printf("%s\t\t", def->argv[i]);
		printf("\n\n");
		def = def->next;
	}
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

int get_type(char **argv, int i)
{
	int type;

	if(!ft_strncmp(argv[i], "<", ft_strlen(argv[i])))
		type = T_RIN;
	if(!ft_strncmp(argv[i], "<<", ft_strlen(argv[i])))
		type = T_HD;
	if(!ft_strncmp(argv[i], ">", ft_strlen(argv[i])))
		type = T_ROUT;
	if(!ft_strncmp(argv[i], ">>", ft_strlen(argv[i])))
		type = T_APP;
	else
		type = T_CMD;
	return(type);
}

t_def *create_node(int size, t_list *lst)
{
	int i;
	t_def *new;

	new = malloc(sizeof(t_def) * 1);
	if(new == NULL)
		return(new);
	new->argv = malloc(sizeof(char *) * (size + 1));
	if(new->argv == NULL)
		return(NULL);
	new->type = malloc(sizeof(int) * (size + 1));
	if(new->type == NULL)
		return(NULL);
	new->argv[size] = NULL;
	printf("--------------------------------------------------------\n");
	i = 0;
	while(i < size)
	{
		new->argv[i] = ft_strdup(lst->content);
		new->type[i] = get_type(new->argv, i);
		printf("\ti -> %d\n", i);
		printf("tyyyypeeeeee -> %d\n", new->type[i]);
		// if(new->type[i] && new->type[i] < 4)
		// {
		// 	if(size - i <= 1)
		// 	{
		// 		printf("minishell: syntax error near unexpected token `newline`\n");
		// 		return (NULL);
		// 	}
		// 	i++;
		// 	lst = lst->next;
		// 	new->argv[i] = ft_strdup(lst->content);
		// 	new->type[i] = new->type[i - 1];
		// 	if(i >= size) 
		// 		break;
		// }
		i++;
		lst = lst->next;
	}
	// printf("i -> %d\n", i);
	return(new);
	(void)size;
	(void)lst;
}

t_def *parse_nodes(t_def *def, t_list *lst)
{
	int	size;
	int flag;
	t_list *aux;
	t_def *new;

	aux = lst;
	size = 0;
	flag = 0;
	while(lst)
	{
		if(size == 0)
		{
			size = count_argvs(lst);
			flag = 1;
		}
		if(flag == 1)
		{
			printf("entro aqui con:\n\tsize = %d\n\tcontent = %s\n", size, lst->content);
			new = create_node(size, lst);
			// mini_lstadd_back(def, new);
			flag = 0;
		}
		size--;
		lst = lst->next;
		if(size == 0 && lst && lst->next)
			lst = lst->next;
	}
	print_nodes(def);
	return(def);
}
