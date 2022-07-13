#!/bin/bash
#Colors
RED="\033[00;31m"
BRED="\033[01;31m"
GREEN='\033[00;32m'
BGREEN='\033[01;32m'
YELLOW="\033[00;33m"
BYELLOW="\033[01;33m"
BLUE="\033[00;34m"
MAGENTA="\033[00;35m"
CYAN="\033[00;36m"
GREY="\033[00;37m"
WHITE="\033[00;0m"
#Variables
ARGV=$@

#intro
echo $YELLOW"---------------------------------------------------------"
echo "|	${MAGENTA}Tester de la Minishell en honor a Pdel-pin${YELLOW}	|"
echo "---------------------------------------------------------"$WHITE

#functions
manual()
{
	echo "Comando introducido: $ARGV";
	rm -rf your_out my_out
	touch my_out
	echo "$ARGV" | ./minishell > your_out
	bash -c "$ARGV" > my_out 2>&1
	# echo "$ARGV" | bash > my_out 2>&1
	sed '$ d' your_out > tmp2
	tail -n +2 tmp2 > your_out
	rm -rf  tmp2

	if [ $(diff my_out your_out | wc -l) -eq 0 ]; then
		echo $BGREEN"OK!"$WHITE;
	else
		if [ $(< my_out wc -l) -eq $(< your_out wc -l) ]; then
			echo $BGREEN"OK!"$WHITE;
		else
			echo $BRED"KO!"$WHITE;
		fi
	fi
}

if [ $# -eq 0 ];then
	echo "En construccion";
elif [ $# -eq 1 ];then
	manual
else
	echo "Wrong arguments";
fi
# cat Makefile
# cat -e Makefile
# cat Makefile | grep -i make
# cat Makefile | grep -i make | wc
# sort Makefile -r
# sort Makefile -r | wc -l
# cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | ls -l -a
# cat | top | ls
# cat Makefile | sort | grep -i make | wc -w -l

# /bin/ls -l -a
# /bin/ls -la | wc
# /bin/cat Makefile
# cat | /bin/cat | cat | cat | cat | /bin/cat | cat | cat | cat | /bin/cat | ls -l -a

# cat Makefile | noexiste | ls
# noexiste | ls
# noexiste
# /binn/ls
# wc -l | noexiste
# ls archivonoexiste
# ls archivonoexiste -la

# touch ejemplo.txt
# yes | rm -i ejemplo.txt &> /dev/null
# echo ls -l -a | ./minishell > foo.txt
# cp foo.txt foo.txt.tmp
# sed '$ d' foo.txt.tmp > foo.txt
# tail -n +2 foo.txt > lol
# rm -f foo.txt.tmp foo.txt

# echo "cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | ls -l -a" | ./minishell > foo.txt
# cp foo.txt foo.txt.tmp
# sed '$ d' foo.txt.tmp > foo.txt
# tail -n +2 foo.txt > lol
# rm -f foo.txt.tmp foo.txt
# echo "ls -l -a" | bash > my_out.txt

# diff lol my_out.txt

#https://www.baeldung.com/linux/bash-interactive-prompts
# https://stackoverflow.com/questions/3448468/is-it-possible-to-make-a-bash-shell-script-interact-with-another-command-line-pr
# https://ryanstutorials.net/bash-scripting-tutorial/bash-input.php
#https://www.unix.com/shell-programming-and-scripting/122935-how-make-shell-script-interact-program.html


# > salida0
# >> salida1
# ls | > salida2
# cat Makefile | > salida3 | ls
# > salida4 > salida5 > salida6 > salida7
# ls | > salida8 >> salida9 > salida10 > salida11
# > salida12 > salida13 > salida14 >> salida15 | ls

# < Makefile ls
# < Makefile ls | wc -l
# < Makefile cat -e | sort -r
# cat | sort < Makefile -r | grep -i make
# cat | sort < Makefile -r

# < noexiste cat
# ls | < noexiste cat
# cat Makefile | < noexiste cat | ls
# ls -l < Makefile -a > salida16 
# ls -l < Makefile -a > salida17 | wc
# ls /dev > salida18 | grep urandom
# cat Makefile | < noexiste cat > salida19 | ls
# cat Makefile | sort -r | grep -i name > salida20 > salida21
# cat | ls >> salida21
# < Makefile top > salida22 >> salida23 | ls
# < /dev/urandom > salida24 | cat salida21 | wc -l > salida25

# #saber explicar este comando con redirecciones
# cat < salida24 >> salida26 > salida27 | cat Makefile > salida26 | wc -l > salida26 >> salida27
# #para eliminar los archivos
# rm -rf salida*