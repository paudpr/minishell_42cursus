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
    //wait hd pid
    wait_process(def);

	// clean_hd();
    free_pipe(cmds, n_pipes);
    free_env(cmds->env);
    free(cmds);
}


void    exec_cmds(t_def *def, t_cmds *cmds)
{
    //contar_hd();
    while (def)
    {
        // printf("posicion de comando -> %d\n", cmds->num);
        get_argv_path(def, cmds);
        check_hd(def, cmds);
        check_redir(def);
        do_process(def, cmds);
        cmds->num++;            //sin esto funciona quien sabe porque. con ello es como debe estár pero va más lento
        def = def->next;
    }
    // clean_hd();
    dup2(cmds->fd_in, STDIN_FILENO);        //devolvemos a los valores originales de STDIN y STDOUT
    dup2(cmds->fd_out, STDOUT_FILENO);
    close(cmds->fd_in);
    close(cmds->fd_out);
}
