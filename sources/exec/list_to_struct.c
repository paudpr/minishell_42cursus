#include "minishell.h"

t_env   *get_struct_env(char **environ)
{
    t_env   *env;

    env =  malloc(sizeof(t_env));
    if(env == NULL)
        return (NULL);
    if(ft_double_len(environ) == 0)
    {
        env->shlvl = 1;
        build_environ(env);     //!!!!!!!!!!!!!!!! mala copia del env borrado
    }
    else
    {
        env->shlvl = get_shlvl(environ);
        copy_environ(environ, env);
    }
    // printf("ESTE ES MIM ENV\n");
    // int i = -1;
    // printf("%d\n", ft_double_len(env->env));
    // while(++i < ft_double_len(env->env))
    //     printf("%s\n", env->env[i]);
    // printf("jyhgtfds\n");
    return (env);
}

int get_shlvl(char **environ)
{
    int i;
    char *aux;
    char *shlvl;
	int lvl;

    i = 0;
    shlvl = NULL;

    // int j = -1;
    // while(environ[++j])
    //     printf("ENVIRON -> %s\n", environ[j]);
    while(i < ft_double_len(environ))
    {
        if(ft_strncmp(environ[i], "SHLVL=", 6) == 0)
            aux = ft_strdup(environ[i]);
        i++;
    }
    // printf("-----> %p\n%p\n", shlvl+1, aux);
    shlvl = ft_strchr(aux, '=');
    // printf("-----> %p\n%p\n", shlvl, aux);
    shlvl++;
	lvl = ft_atoi(shlvl);
	free(aux);
    return(lvl);
}

void build_environ(t_env *env)
{
    char cwd[PATH_MAX];

    env->env = ft_calloc(sizeof(char *), 3);
    if(env->env == NULL)
        return ; 
    getcwd(cwd, sizeof(cwd));
    env->env[0] = ft_strjoin("PWD=", cwd);
    env->env[1] = ft_strjoin("SHLVL=", ft_itoa(env->shlvl));
    env->env[2] = ft_strjoin("_=", cwd);
	env->path = NULL;   //!!!!!!!!!!!!!!!!!!!!!!!!! esto será pa revisar después
}

void copy_environ(char **environ, t_env *env)
{
    char *path;
    char *aux;
    int i;

    i = 0;
    env->env = ft_calloc(sizeof(char *), ft_double_len(environ) + 1);
    if(env->env == NULL)
        return ;
    while (environ[i])
    {
		if (ft_strncmp(environ[i], "SHLVL=", 6))
        	env->env[i] = ft_strdup(environ[i]);
		else
			env->env[i] = ft_strjoin("SHLVL=", ft_itoa(env->shlvl));
        if (ft_strnstr(environ[i], "PATH=", 5))
			aux = ft_strdup(environ[i]);
		i++;
    }
    path = ft_strchr(aux, '/');
    env->path = ft_split(path, ':');
    free(aux);
}

void init_struct_cmds(t_env *env, t_cmds *cmds, int i)
{
    cmds->env = env;
    cmds->num = 0;
    if(i < 0)
        i = 0;
    cmds->pipe_fd = ft_calloc(sizeof(int *), i);
    cmds->fd_in = dup(STDIN_FILENO);
    cmds->fd_out = dup(STDOUT_FILENO);
}

char    *check_valid(char **path, char *cmd)
{
    int i;
    char *cmd_str;
    char *cmd_path;
    char *aux;

    i = 0;
    cmd_path = NULL;
    while (path[i])
    {
        aux = ft_strjoin(path[i], "/");
        cmd_str = ft_strjoin(aux, cmd);
        if (access(cmd_str, F_OK) == 0)
            cmd_path = ft_strdup(aux);
        free(aux);
        free(cmd_str);
        i++;
    }
    if (cmd_path == NULL)
    {
        access(cmd_path, F_OK);
    }
    return (cmd_path);
}

char    *get_path(t_def *def, char **path, char *argvs)
{
    int  i;
    char    *cmd_path;
    char    **split_argv;

    i = 0;
    split_argv = NULL;
    cmd_path = NULL;
	if (path == NULL)	//!!!!!!!!!!!!!!!!! comprobar que este sea el valor meter en execve. contrastar el error con bash
		return (NULL);
    while(def->argv[i])
    {
        if(def->type[i] == 4)
        {
            split_argv = ft_split(argvs, ' ');
            cmd_path = check_valid(path, split_argv[0]);
            break ;
        }
        i++;
    }
    ft_free_double(split_argv);
    return (cmd_path);
}

char    *get_argv(t_def *def)
{
    int  i;
    char   *cmd;
    char   *aux;
    char   *temp;

    i = 0;
    cmd = NULL;
    while (def->argv[i])
    {
		printf("argv -> %s\ntype -> %d\n", def->argv[i], def->type[i]);
        if (def->type[i] == 4)
        {
            if (!cmd)
                cmd = ft_strdup(def->argv[i]);
            else
            {
                aux = ft_strjoin(cmd, " ");
                temp = ft_strdup(def->argv[i]);
                free(cmd);
                cmd = ft_strjoin(aux, temp);
                free(aux);
                free(temp);
            }
        }
        i++;
    }
    return (cmd);
}

char    *get_relative_path(char *cmd)
{
    char    *chr;
    char    *path;
    int  len;

    chr = ft_strrchr(cmd, '/') + 1;
    len = ft_strlen(cmd) - ft_strlen(chr);
    path = ft_substr(cmd, 0, len);
    return (path);
}

char    *get_relative_argv(char *cmd)
{
    char    *chr;

    chr = NULL;
    if (ft_strrchr(cmd, '/') != NULL)
    {
        chr = ft_strdup(ft_strrchr(cmd, '/') + 1);
        free(cmd);
    }
    return (chr);
}

char    *join_argv(char *cmd, char **split)
{
    char    *aux;
    char    *temp;
    int 	i;

    i = 1;
    temp = cmd;
    while (i < ft_double_len(split))
    {
        aux = ft_strjoin(temp, " ");
        free(temp);
        temp = ft_strjoin(aux, split[i]);
        free(aux);
        free(split[i]);
        i++;
    }
    return (temp);
}

void    get_argv_path(t_def *def, t_cmds *cmds)
{
    char    **split_argv;
    char    *rel_cmd;

    cmds->cmds_argv = get_argv(def);
    split_argv = ft_split(cmds->cmds_argv, ' ');
    if(ft_strrchr(split_argv[0], '/') != NULL)
    {
        cmds->cmds_path = get_relative_path(split_argv[0]);
        rel_cmd = get_relative_argv(split_argv[0]);
        free(cmds->cmds_argv);
        cmds->cmds_argv = join_argv(rel_cmd, split_argv);
        free(split_argv);
    }
    else
    {
        cmds->cmds_path = get_path(def, cmds->env->path, cmds->cmds_argv);
        ft_free_double(split_argv);
    }
}
