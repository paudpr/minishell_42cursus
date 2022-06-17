#include "minishell.h"

void check_redir(t_def *def, t_env *env)
{
    t_def *copy;
    // int i = -1;

    copy = def;
    (void)env;
    while(copy)
    {
        // i = -1;
        // while(copy->argv[++i])
        // {
        //     printf("argumento -> %s\n", copy->argv[i]);
        //     printf("type -> %d\n", copy->type[i]);
        // }
        // printf("---------------\n");

    copy = copy->next;
    }

// aqui abro tantos heredocs como sea necesario por nodo
// creo los archivos de entrada y salida que no estén 
// y redefino in y out necesarios con dups

}