#include "minishell.h"

int num_hd(t_def *def)
{
	int i;
	int n;

	i = 0;
	while(def->argv[i])
	{
		if(def->type[i] == 0 && def->argv[i + 1])
		{
			i++;	
			n++;
		}
		i++;
	}


}



void check_hd(t_def *def, t_env *env)
{
	int n;
	
	while(def)
	{
		n = num_hd(def);


		def = def->next;
	}
}