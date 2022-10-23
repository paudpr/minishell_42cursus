#include "minishell.h"

#define RED "\033[1;31m"
#define RESET "\033[0m"

int	main(void)
{
	char		*line;
	extern char	**environ;
	t_def		*def;
	t_env		*env;

	def = NULL;
	env = get_struct_env(environ);
	while (1)
	{
		line = readline(RED "minishell > " RESET);
		if (line == NULL) //eof -> ctrl-D
		{
			printf("exit\n");
			exit(0);
		}
		if (line != NULL && *line != 0)
			add_history(line);
		main_parse(&def, line);
		// get_list(&def, line);			// main_parse();
		// main_exec(def, env);
		free(line);
		free_list(&def);
	}
	free_env(env);
	return (0);
}
