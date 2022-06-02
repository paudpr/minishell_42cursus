#include "pruebas_bash.h"

/*
"cat Makefile > salida | ls | cat << eof >> salida2"
*/


int main(int argc, char **argv, char **environ)
{
    // atexit(check_leaks);
    t_def *def;
    t_def *copy;
    t_env *env;
    t_cmds *cmds;
    int n_pipes;

	if(argc != 2)
		print_error("Error. Arguments");
    get_list(&def, argv[1]);
    env = get_struct_env(environ);

    n_pipes = ft_lstsize(def) - 1;
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
        copy = copy->next;
        free_struct(cmds);
        cmds->num++;
    }
    wait_process(def);
    free_pipe(cmds);
    free(cmds);
    free_env(env);
    free_list(&def);
    return(0);
}


