/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladelpinoramirez <pauladelpinoramire    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:26:57 by pdel-pin          #+#    #+#             */
/*   Updated: 2023/01/03 22:49:57 by pauladelpin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	disable_output(void)
{
	int				x;
	struct termios	termios;

	x = tcgetattr(0, &termios);
	if (x)
	{
		perror("");
		exit(1);
	}
	termios.c_lflag &= ~ECHOCTL;
	x = tcsetattr(0, 0, &termios);
	if (x)
	{
		perror("");
		exit(1);
	}
}

int	main(void)
{
	char		*line;
	extern char	**environ;
	t_def		*def;
	t_env		*env;

	def = NULL;
	g_exit_status = 0;			///actualizar despues de fallos
	env = get_struct_env(environ);
	disable_output();
	while (1)
	{
		// sig_default();
		line = readline(DARKGREEN "minishell > " RESET);
		if (line == NULL) //eof -> ctrl-D
		{
			printf("exit");
			exit(0);
		}
		if (line != NULL && *line != 0)
			add_history(line);
		main_parse(&def, line, env);
		main_exec(def, env);
		free(line);
		free_def(&def);
	}
	free_env(env);
	return (0);
}
