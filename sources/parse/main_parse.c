#include "minishell.h"

void	free_lst(t_list *lst)
{
	t_list	*aux;

	while (lst)
	{
		aux = lst;
		lst = lst->next;
		aux->next = NULL;
		free(aux->content);
		free(aux);
	}
}

void	main_parse(t_def **def, char *line, t_env *env)
{
	t_list	*lst;
	t_list	*aux;

	if (!line)
		def = NULL;
	lst = split_blocks(line, 0);
	if (lst)
	{
		aux = lst;
		lst = lst->next;
		aux->next = NULL;
		free(aux->content);
		free(aux);
	}
	if (clean_redir(lst))
	{
		free_lst(lst);
		return ;
	}
	if (!parse_tokens(lst) && !parse_com(lst))
		*def = parse_nodes(lst, env);
	free_lst(lst);
}
