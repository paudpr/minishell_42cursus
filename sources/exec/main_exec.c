#include "minishell.h"

void    main_exec(t_def *def, t_env *env)
{
    t_cmds *cmds;
    int n_pipes;

    n_pipes = mini_lstsize(def) - 1;
    cmds = ft_calloc(sizeof(t_cmds), 1);
    if(cmds == NULL)
        print_error("memoria struct cmds");
    init_struct_cmds(env, cmds, n_pipes);

    exec_cmds(def, cmds);

    wait_process(def);
    // free_env(env);           !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    free_pipe(cmds);
    free(cmds);
}

void    exec_cmds(t_def *def, t_cmds *cmds)
{
    t_def *copy;

    copy = def;
    while (copy)
    {
        get_argv_path(copy, cmds);
        if(copy->next == NULL && cmds->num == 0)
        {
            do_one_command(cmds);
            free_struct(cmds);
            break ;
        }
        if (copy->next == NULL)
        {
            do_last_command(cmds);
            break ;
        }
        do_commands(cmds);
        free_struct(cmds);
        cmds->num++;
        copy = copy->next;
    }
    dup2(cmds->fd_in, STDIN_FILENO);
    dup2(cmds->fd_out, STDOUT_FILENO);
    close(cmds->fd_in);
    close(cmds->fd_out);
}