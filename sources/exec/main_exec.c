#include "minishell.h"

void	main_exec(t_def *def, t_env *env)
{
	t_cmds	*cmds;
	int		n_pipes;
	int		hds;

	n_pipes = mini_lstsize(def);
	cmds = ft_calloc(sizeof(t_cmds), 1);
	if (cmds == NULL)
		print_error("memoria struct cmds");
	init_struct_cmds(env, cmds, n_pipes);
	hds = check_hd(def);
	exec_cmds(def, cmds);
	wait_process(def);
	clean_hd(hds);
	free_pipe(cmds, n_pipes);
	free(cmds);
}

void	exec_cmds(t_def *def, t_cmds *cmds)
{
	while (def)
	{
		get_argv_path(def, cmds);
		do_process(def, cmds);
		cmds->num++;
		free_struct(cmds);
		def = def->next;
	}
	dup2(cmds->fd_in, STDIN_FILENO);
	dup2(cmds->fd_out, STDOUT_FILENO);
	close(cmds->fd_in);
	close(cmds->fd_out);
}
