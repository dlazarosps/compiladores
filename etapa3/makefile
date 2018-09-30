# MAKEFILE ETAPA 3
all: etapa3

etapa3: parser.tab.o lex.yy.o main.o ast.o
	gcc parser.tab.o lex.yy.o main.o -o etapa3

# etapa3: y.tab.o lex.yy.o main.o
# 	gcc y.tab.o lex.yy.o main.o -o etapa3

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

# AST
ast.o: ast.c ast.h
	gcc -c ast.c

# Testes
teste1: etapa3
	clear
	cat teste1.txt | ./etapa3

# Compacta para envio
targz:
	tar cvzf etapa3.tgz main.c parser.y makefile scanner.l
	# scp etapa3.tgz dlspsilva@html.inf.ufrgs.br:./public_html/

# Limpeza de arquivos exec
clean:
	rm -rf *.o lex.yy.c y.tab.c y.tab.h y.output parser.output parser.tab.c parser.tab.h etapa3
	sleep 1
	clear
