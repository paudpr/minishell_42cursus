#include "minishell.h"

static int	clean_redir_check(t_list *lst)
{
	char	*tmp;
	t_list	*aux;

	aux = NULL;
	if (!ft_strncmp(lst->next->content, "<", 1)
		|| !ft_strncmp(lst->next->content, ">", 1))
	{
		tmp = ft_strdup(lst->content);
		free(lst->content);
		lst->content = ft_strjoin(tmp, lst->next->content);
		free(tmp);
		aux = lst->next;
		lst->next = lst->next->next;
		free(aux->content);
		free(aux);
		if (!lst->next)
		{
			printf("minishell: ");
			printf("syntax error near unexpected token 'newline'\n");
			g_exit_status = 258;
			return (1);
		}
	}
	return (0);
}

int	clean_redir(t_list *lst)
{
	while (lst)
	{
		if (!ft_strncmp(lst->content, "<", 1)
			|| !ft_strncmp(lst->content, ">", 1))
		{
			if (!lst->next)
			{
				printf("minishell: ");
				printf("syntax error near unexpected token 'newline'\n");
				g_exit_status = 258;
				return (1);
			}
			if (clean_redir_check(lst))
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}
