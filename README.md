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







> salida0
>> salida1
ls | > salida2
cat Makefile | > salida3 | ls
> salida4 > salida5 > salida6 > salida7
ls | > salida8 >> salida9 > salida10 > salida11
> salida12 > salida13 > salida14 >> salida15 | ls

< Makefile ls
< Makefile ls | wc -l
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