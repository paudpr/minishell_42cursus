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
	check_redir(def, env);
    exec_cmds(def, cmds);
    wait_process(def);

    free_pipe(cmds, n_pipes);
    free_env(cmds->env);
    free(cmds);
}

void    exec_cmds(t_def *def, t_cmds *cmds)
{
    t_def *copy;

    // print_node(&def, 3);
    copy = def;
    while (copy)
    {
        printf("type -> %d\n", copy->type[0]);
        printf("-------> %s\n", cmds->cmds_argv);
        get_argv_path(copy, cmds);
        if(copy->next == NULL && cmds->num == 0)
            do_one_command(cmds);
        else if (copy->next == NULL)
            do_last_command(cmds);
        else
            do_commands(cmds);
        free_struct(cmds);
        cmds->num++;
        copy = copy->next;
    }
    dup2(cmds->fd_in, STDIN_FILENO);        //devolvemos a los valores originales de STDIN y STDOUT
    dup2(cmds->fd_out, STDOUT_FILENO);
    close(cmds->fd_in);
    close(cmds->fd_out);
}
