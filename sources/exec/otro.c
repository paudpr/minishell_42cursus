#include "pruebas_bash.h"

/*
"cat Makefile > salida | ls | cat << eof >> salida2"
*/


int main(int argc, char **argv, char **environ)
{
    atexit(check_leaks);
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
    while(copy)
    {
        cmds = get_struct_cmds(copy, env);
        // exec() supongo????
        free_struct(cmds);
        free(cmds);
        copy = copy->next;
    }

    

    free_env(env);
    free_list(&def);
    return(0);
}