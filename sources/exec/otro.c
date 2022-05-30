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
    // printf("%d\n", cmds->pipe_fd[0][0]);


    while(copy)
    {
        printf("-----------------> %d\n", cmds->num);
        cmds->cmds_argv = get_argv(copy);
        cmds->cmds_path = get_path(copy, env->path, cmds->cmds_argv);
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
        printf("------------------\n");
        copy = copy->next;
        free_struct(cmds);
        cmds->num++;
    }

    //gestionar waiiiiiiiiiiiiiiit
    free_pipe(cmds);
    free(cmds);
    free_env(env);
    free_list(&def);
    return(0);
}




// void	pipex(char *infile, char *outfile, t_vals *vals)
// {
// 	int		i;
// 	int		fd;
// 	pid_t	pid;

// 	i = 0;
// 	while (vals->cmds_argv[i])
// 		i++;
// 	fd = open(infile, O_RDONLY);
// 	if (fd < 0)
// 		print_error(0);
// 	unlink("/tmp/file");
// 	dup2(fd, STDIN_FILENO);
// 	close(fd);
// 	while (vals->cmds_argv[vals->num] && vals->num < i - 1)
// 	{
// 		pid = exec_child(vals);
// 		vals->num += 1;
// 	}
// 	check_herefile(infile);
// 	wait(&pid);
// 	fd = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	check_access(outfile);
// 	dup2(fd, STDOUT_FILENO);
// 	close(fd);
// 	exec(vals);
// }

// pid_t	exec_child(t_vals *vals)
// {
// 	pid_t	pid;

// 	if (pipe(vals->pipe_fd) < 0)
// 		print_error(0);
// 	pid = fork();
// 	if (pid < 0)
// 		print_error(0);
// 	if (pid == 0)
// 	{
// 		close(vals->pipe_fd[0]);
// 		dup2(vals->pipe_fd[1], STDOUT_FILENO);
// 		close(vals->pipe_fd[1]);
// 		exec(vals);
// 	}
// 	else
// 	{
// 		close(vals->pipe_fd[1]);
// 		dup2(vals->pipe_fd[0], STDIN_FILENO);
// 		close(vals->pipe_fd[0]);
// 	}
// 	return (pid);
// }