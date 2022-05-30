// // #include "pruebas_bash.h"


// static void	wait_child(t_info *info)
// {
// 	int	i;
// 	int	k;

// 	i = 0;
// 	while (i < info->nlst)
// 	{
// 		waitpid(-1, &k, 0);
// 		i++;
// 	}
// }

// void	make_process(t_info *info, t_lst *lst, t_env **env)
// {
// 	int	i;

// 	i = 0;
// 	check_here(info, lst);
// 	if (g_general_data->signal_heredoc == 0)
// 	{
// 		while (lst)
// 		{
// 			info->pos = i;
// 			commands(info, lst, env);
// 			lst = lst->next;
// 			i++;
// 		}
// 		wait_child(info);
// 	}
// }