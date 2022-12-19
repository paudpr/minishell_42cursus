#include "minishell.h"

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define CYAN "\033[1;36m"
# define GREY "\033[1;90m"
# define YELLOW "\033[1;33m"
# define MAGENTA "\033[1;35m"
# define DARKGREEN "\e[0;32;40m"
# define RESET "\033[0m"

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
	g_exit_status = 0;
	env = get_struct_env(environ);
	disable_output();
	while (1)
	{
		// sig_default();
		line = readline(DARKGREEN "minishell > " RESET);
		if (line == NULL) //eof -> ctrl-D
		{
			printf("exit\n");
			exit(0);
		}
		if (line != NULL && *line != 0)
			add_history(line);
		main_parse(&def, line, env);
		main_exec(def, env);
		free(line);
		free_list(&def);
	}
	free_env(env);
	return (0);
}
