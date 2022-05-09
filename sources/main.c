#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>



int main(void)
{
	char *line;
	char *eof;

	eof = "exit";

	line = readline("minishell > ");
	while(strncmp(line, eof, strlen(eof)) != 0)
	{
		line = readline("minishell > ");
		if(line != NULL)
			add_history(line);
		free(line);
	}
	return(0);
}

