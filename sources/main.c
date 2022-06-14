# define RED "\033[1;31m"
# define RESET "\033[0m"

#include "minishell.h"

int main(void)
{
    // atexit(check_leaks);
	char *line;
    extern char **environ;
    t_def *def;
    t_env *env;

    def = NULL;
	while(1)
	{
        env = get_struct_env(environ);
        // dprintf(2, "--->este es el proceso: %d\n", getpid());
		line = readline(RED"minishell > "RESET);
		add_history(line);
        get_list(&def, line);       //main_parse()
        
        main_exec(def, env);
		free(line);
        free_list(&def);
	}
    free_env(env);
	return(0);
}
