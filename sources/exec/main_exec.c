#include "minishell.h"

void    main_exec(t_def *def, t_env *env)
{
    t_cmds *cmds;
    int n_pipes;
	int hds;

    n_pipes = mini_lstsize(def);
    cmds = ft_calloc(sizeof(t_cmds), 1);
    if(cmds == NULL)
        print_error("memoria struct cmds");
    init_struct_cmds(env, cmds, n_pipes);
	hds = check_hd(def, cmds);
    exec_cmds(def, cmds);
    wait_process(def);
	clean_hd(hds);                 
    free_pipe(cmds, n_pipes);
    free(cmds);
}

void    exec_cmds(t_def *def, t_cmds *cmds)
{
	int hd;

	hd = 0;
    while (def)
    {
        get_argv_path(def, cmds);        
        check_redir(def, &hd);
        do_process(def, cmds);
        // cmds->num++;
        def = def->next;
        free_struct(cmds);
    }
    dup2(cmds->fd_in, STDIN_FILENO);        //devolvemos a los valores originales de STDIN y STDOUT
    dup2(cmds->fd_out, STDOUT_FILENO);
    close(cmds->fd_in);
    close(cmds->fd_out);
}
