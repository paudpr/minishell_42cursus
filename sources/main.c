# define RED "\033[1;31m"
# define RESET "\033[0m"

#include "minishell.h"



int main(void)
{
	char *line;
    extern char **environ;
    t_def *def;
    t_env *env;

	line = readline(RED"minishell > "RESET);
	while(1)
	{
		if(line != NULL)
			add_history(line);
        printf("line -> %s\n", line);
        get_list(&def, line);
        env = get_struct_env(environ);
        main_exec(def, env);
		free(line);
		line = readline(RED"minishell > "RESET);
        // printf("peto aqui\n");
        free_list(&def);
	}
    free_env(env);
	return(0);
}

void main_exec(t_def *def, t_env *env)
{
    // atexit(check_leaks);
    t_def *copy;
    t_cmds *cmds;
    int n_pipes;


    n_pipes = mini_lstsize(def) - 1;
    copy = def;
    cmds = ft_calloc(sizeof(t_cmds), 1);
    if(cmds == NULL)
        print_error("memoria struct cmds");
    get_struct_cmds(env, cmds, n_pipes);




    while(copy)
    {
        get_argv_path(copy, cmds);
        if(copy->next == NULL && cmds->num == 0)
        {
            do_one_command(cmds);
            break;
        }
        if(copy->next == NULL)
        {
            do_last_command(cmds);
            break;
        }
        do_commands(cmds);
        printf("%p     %p    %p\n", cmds, cmds->cmds_argv, cmds->cmds_path);
        free_struct(cmds);
        cmds->num++;
        copy = copy->next;
    }
    wait_process(def);
    free_pipe(cmds);
    free(cmds);
}
