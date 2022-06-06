# pruebas-bash


brew info readline

PRUEBAS COMANDOS:
cat Makefile
cat -e Makefile
cat Makefile | grep -i make
cat Makefile | grep -i make | wc    ----leaks
sort Makefile -r
sort Makefile -r | wc -l
cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | ls -l -a
cat | top | ls
cat Makefile | sort | grep -i make | wc -w -l

/bin/ls -l -a
/bin/ls -la | wc
/bin/cat Makefile
cat | /bin/cat | cat | cat | cat | /bin/cat | cat | cat | cat | /bin/cat | ls -l -a

cat Makefile | noexiste | ls       -------- no sale igual: distinto error y orden
noexiste | ls                      -------- distinto error
noexiste
/binn/ls                            ------- distinto error
wc -l | noexiste                    ------- distinto error, funcionamiento igual
ls archivonoexiste
ls archivonoexiste -la





********* error al eliminar el path