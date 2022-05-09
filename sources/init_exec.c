#include "minishell.h"

/*
cat Makefile > salida | ls | cat << eof >> salida2
*/

void init_exec(t_def *def)
{
	def = malloc(sizeof(t_def) * 1);
	if(def == NULL)
		print_error(MEM);







}