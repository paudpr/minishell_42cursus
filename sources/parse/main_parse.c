#include "minishell.h"

int ignore_spaces(char *line, int i)
{
	while(line[i])
	{
		if(line[i] != ' ')
			break ;
		i++;
	}
	return (i);
}

int len_block(char *line, int i)
{
	int len;
	char flag;

	len = 0;
	while(line[i + len])
	{
		if(line[i + len] == 34 || line [i + len] == 39)
		{
			flag = line[i + len];
			while(line[i + len])
			{
				len++;
				if(flag == line[i + len])
					return(len + 1);
			}
		}
		else if (line[i + len] == ' ' || line[i + len] == '<' || line[i + len] == '>' || line[i + len] == '|')
			return (len);
		len++;
	}
	return (len);
}

t_list *split_blocks(char *line)
{
	t_list *lst;
	int i;
	int len;

	i = 0;
	len = 0;
	lst = ft_lstnew(ft_strdup(line));
	while(line[i])
	{	
		i = ignore_spaces(line, i);
		if((line[i] == '<' || line[i] == '>' || line[i] == '|') && line[i])
		{
			len = 1;
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(line, i, len)));
			i += len;
		}
		else if (line[i])
		{
			len = len_block(line, i);
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(line, i, len)));
			i += len;
		}
	}
	return(lst);
}

void print_list(t_list *lst)
{
	while(lst)
	{
		printf("%s\n", lst->content);
		lst = lst->next;
	}
}

int parse_tokens(t_list **lst)
{
	t_list *aux;
	int i;
	char c;
	// int flag;

	aux = lst;
	// flag = 0;
	if (ft_lstlast(aux)->content == '|' || aux->content == '|')
	{
		printf("syntax error near unexpected token `|'\n");
		return(1);
	}
	while(aux)
	{

		i = 0;
		if
		aux = aux->next;
	}
	return(0)
}

void main_parse(t_def **def, char *line)
{
	t_list *lst;
	t_list *aux;

	if(!line)
		def = NULL;
	lst = split_blocks(line);
	aux = lst;
	lst = lst->next;
	aux->next = NULL;
	free(aux->content);
	free(aux);
	if(!parse_tokens(lst))			//errores de tokens | < > << >> 
		parse_nodes(lst);			//crear nodos con argumentos correspondientes
	print_list(lst);

		
}
