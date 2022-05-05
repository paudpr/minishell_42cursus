#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char *line;
	char *eof;

	eof = "eof";

	line = readline("test > ");
	while(line != eof)
	{
		line = readline("loquesea -> ");
		if(line != NULL)
			add_history(line);
		free(line);
	}
	return(0);
}
