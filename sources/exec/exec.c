#include "pruebas_bash.h"

void exec(t_cmds *cmds)
{
    int i;

    check_heredoc();
    gestionar_infile();
    dups_ejecutar();
    
}
