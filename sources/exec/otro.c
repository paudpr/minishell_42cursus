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

	if(argc != 2)
		print_error("Error. Arguments");
    get_list(&def, argv[1]);
    env = get_struct_env(environ);

    // int i = -1;
    // while(env->env[++i])
    //     printf("env -> %s\n", env->env[i]);
    // i = -1;
    // printf("\n\n");
    // while(env->path[++i])
    //     printf("path -> %s\n", env->path[i]);


    copy = def;
    // guardar memoria para cmds aqui y proteger
    cmds = get_struct_cmds(copy, env);


    while(copy)
    {
        // exec() supongo????

        free_struct(cmds);
        copy = copy->next;
    }
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
