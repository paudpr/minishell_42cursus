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
    copy = def;
    while(copy)
    {
        cmds = get_struct_cmds(copy, env);
        // exec() supongo????
        // free_struct(*cmds);
        copy = copy->next;
    }

    // print_node(&def, ft_lstsize(def));




    free_env(env);
    free_list(&def);
    return(0);

}