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
	// check_hd(def);                         //  !!!!!! metodo comentado en archivo heredoc. cambiando estructura de lectura y ejecución por nodo
    exec_cmds(def, cmds);
    wait_process(def);

	// clean_hd();
    free_pipe(cmds, n_pipes);
    free_env(cmds->env);
    free(cmds);
}

void    exec_cmds(t_def *def, t_cmds *cmds)
{
    while (def)
    {
        get_argv_path(def, cmds);
        check_hd(def,  cmds);
        // check_redir(def, cmds);
        // printf("argumentos -> %s\n%s\n", cmds->cmds_argv, cmds->cmds_path);
        do_process(def, cmds);
        // clean_hd();
        // cmds->num++;
        def = def->next;
    }
    dup2(cmds->fd_in, STDIN_FILENO);        //devolvemos a los valores originales de STDIN y STDOUT
    dup2(cmds->fd_out, STDOUT_FILENO);
    close(cmds->fd_in);
    close(cmds->fd_out);
}
