#include "minishell.h"

#define RED "\033[1;31m"
#define RESET "\033[0m"

// void pepe(int señal)                //esto es control+C mientras no estás ejecutando
// {
//     if(señal == SIGINT)
//     {
//         printf("\n");
//         rl_on_new_line();
//         rl_replace_line("", 0);
//         rl_redisplay();
//     }
// }

int main(void)
{
    // atexit(check_leaks);
    char *line;
    extern char **environ;
    t_def *def;
    t_env *env;

    def = NULL;
    while (1)
    {
        env = get_struct_env(environ);
        // dprintf(2, "--->este es el proceso: %d\n", getpid());
        // signal(SIGINT, pepe);
        // signal(SIGQUIT, SIG_IGN);           //ignorar el sigquit
        line = readline(RED "minishell > " RESET);
        if(line != NULL && *line != 0)
            add_history(line);
        get_list(&def, line);            // main_parse();

        main_exec(def, env);
        free(line);
        free_list(&def);
    // printf("%p\n%p\n%p\n", env, env->path, env->env);
    }
    free_env(env);
    return (0);
}
