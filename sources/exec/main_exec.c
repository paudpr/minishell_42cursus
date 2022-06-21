#include "minishell.h"

void    main_exec(t_def *def, t_env *env)
{
    t_cmds *cmds;
    int n_pipes;

    n_pipes = mini_lstsize(def);
    cmds = ft_calloc(sizeof(t_cmds), 1);
    if(cmds == NULL)
        print_error("memoria struct cmds");
    init_struct_cmds(env, cmds, n_pipes);
	check_hd(def);
    exec_cmds(def, cmds);
    wait_process(def);

	// clean_hd();
    free_pipe(cmds, n_pipes);
    free_env(cmds->env);
    free(cmds);
}

void    exec_cmds(t_def *def, t_cmds *cmds)
{
    t_def *copy;
    int i;

    copy = def;
    while (copy)
    {
        i = 0;
        while(copy->argv[i])
        {
            if(copy->type[i] == 4)
            {
                get_argv_path(copy, cmds);
                if(copy->next == NULL && cmds->num == 0)
                    do_one_command(cmds);
                else if (copy->next == NULL)
                    do_last_command(cmds);
                else
                    do_commands(cmds);
                free_struct(cmds);
                cmds->num++;
            }
            copy = copy->next;
            i++;
        }
    }
    dup2(cmds->fd_in, STDIN_FILENO);        //devolvemos a los valores originales de STDIN y STDOUT
    dup2(cmds->fd_out, STDOUT_FILENO);
    close(cmds->fd_in);
    close(cmds->fd_out);
}
