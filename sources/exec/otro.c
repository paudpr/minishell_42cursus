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
        printf("------------------\n");
        copy = copy->next;
        free_struct(cmds);
        cmds->num++;
    }

    // printf("%p\n", cmds->cmds_argv);
    wait_process(def);
    free_pipe(cmds);
    free(cmds);
    free_env(env);
    free_list(&def);
    return(0);
}


void get_argv_path(t_def *def, t_cmds *cmds)
{
    char **split_argv;
    char *rel_cmd;

    cmds->cmds_argv = get_argv(def);
    split_argv = ft_split(cmds->cmds_argv, ' ');
    if(ft_strrchr(split_argv[0], '/') != NULL)
    {
        printf("ENTRO AQUI\n");
        rel_cmd = get_relative_argv(split_argv[0]);
        free(cmds->cmds_argv);
        cmds->cmds_argv = join_argv(rel_cmd, split_argv);
        printf("!!!!!!!!!!!!!!!!!!!!!! leak  cmds->cmds_argvs -> %s\n", cmds->cmds_argv);
        cmds->cmds_path = get_relative_path(split_argv[0]);
    }
    else
        cmds->cmds_path = get_path(def, cmds->env->path, cmds->cmds_argv);
    ft_free_double(split_argv);



}

