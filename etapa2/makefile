# MAKEFILE ETAPA 2
all: etapa2

etapa2: parser.tab.o lex.yy.o main.o
	gcc parser.tab.o lex.yy.o main.o -o etapa2

# etapa2: y.tab.o lex.yy.o main.o
# 	gcc y.tab.o lex.yy.o main.o -o etapa2

main.o: main.c
	gcc -c main.c

# FLEX
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l
	flex scanner.l

# BISON
parser.tab.o: parser.tab.c
		gcc -c parser.tab.c
parser.tab.c: parser.y
	bison -d -v parser.y

# y.tab.o: y.tab.c
# 		gcc -c y.tab.c
# y.tab.c: parser.y
# 	bison -d -v parser.y -o y.tab.c


# Testes
teste1: etapa2
	clear
	cat teste1.txt | ./etapa2

# Teste
teste: etapa2
	clear
	cat $(FILE) | ./etapa2

# Compacta para envio
targz: 
	tar cvzf etapa2.tgz main.c parser.y makefile scanner.l
	# scp etapa2.tgz dlspsilva@html.inf.ufrgs.br:./public_html/

# Limpeza de arquivos exec
clean:
	rm -rf *.o lex.yy.c y.tab.c y.tab.h y.output parser.output parser.tab.c parser.tab.h etapa2
	sleep 1
	clear
