# pruebas-bash

** probar con env -i ./minishell
** probar leaks
** probar fsanitize
** probar ps -a

procesos -> while true; do lsof -p {nº proceso} | grep CHR; sleep 0.5 ; clear; done

leaks -> while true
do
clear; leaks -q minishell; sleep 0.4
done


brew info readline

PRUEBAS COMANDOS:
cat Makefile
cat -e Makefile
cat Makefile | grep -i make
cat Makefile | grep -i make | wc   
sort Makefile -r
sort Makefile -r | wc -l
cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | ls -l -a
cat | top | ls
cat Makefile | sort | grep -i make | wc -w -l

/bin/ls -l -a
/bin/ls -la | wc
/bin/cat Makefile
cat | /bin/cat | cat | cat | cat | /bin/cat | cat | cat | cat | /bin/cat | ls -l -a

cat Makefile | noexiste | ls      
noexiste | ls                      
noexiste
/binn/ls                            
wc -l | noexiste                    ------- funcionamiento distinto, potencialmente leaks
ls archivonoexiste
ls archivonoexiste -la
cd -                                ------- es un builtin¿? -> da segfault

sort << eof -r
sort << eof > salida -r





********* al eliminar el path -> da error de execve de bad address -> comprobar si ese tiene que ser el resultado
********* comprobar si el guardado de path se aplica solo a tipo comando o es estandar para todo
********* (cmd + D) + (flecha parriba) => segfault
********* no funciona el borrado del env correctamente -> devuelve un size del nuevo environ que no es, y eso hace segfault. función -> get_struct_env



PRUEBAS REDIRECCIONES:
> salida0
>> salida1
ls | > salida2
cat Makefile | > salida3 | ls
> salida4 > salida5 > salida6 > salida7
ls | > salida8 >> salida9 > salida10 > salida11
> salida12 > salida13 > salida14 >> salida15 | ls

< Makefile ls
< Makefile ls | wc -l
< Makefile cat
< Makefile cat -e | sort -r
cat | sort < Makefile -r | grep -i make
cat | sort < Makefile -r

< noexiste cat
ls | < noexiste cat
cat Makefile | < noexiste cat | ls
ls -l < Makefile -a > salida16 
ls -l < Makefile -a > salida17 | wc
ls /dev > salida18 | grep urandom
cat Makefile | < noexiste cat > salida19 | ls
cat Makefile | sort -r | grep -i name > salida20 > salida21
cat | ls >> salida21
< Makefile top > salida22 >> salida23 | ls
< /dev/urandom > salida24 | cat salida21 | wc -l > salida25

#saber explicar este comando con redirecciones
cat < salida24 >> salida26 > salida27 | cat Makefile > salida26 | wc -l > salida26 >> salida27
#para eliminar los archivos
rm -rf salida*




PRUEBAS HEREDOC:
cat | cat | cat << eof | cat | ls
<< eof
ls | << eof cat -e
cat Makefile << eof << eof | ls
<< eof << eof << eof | << eof | cat << eof << eof
cat << eof | grep -i hola | wc
ls | wc | grep hola << eof
sort << eof -r
cat << ls -e











ERRORES:

<< eof << eof2 | cat Makefile | << eof3 wc