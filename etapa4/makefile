# MAKEFILE ETAPA 4
all: etapa4

etapa4: clean parser.tab.o lex.yy.o valor_lexico.o ast.o list.o main.o
	gcc parser.tab.o lex.yy.o valor_lexico.o ast.o list.o main.o -o etapa4
# etapa4: y.tab.o lex.yy.o main.o
# 	gcc y.tab.o lex.yy.o main.o -o etapa4

main.o: main.c
	gcc -c main.c

valor_lexico.o: valor_lexico.c
	gcc -c valor_lexico.c

list.o: list.c
	gcc -c list.c

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

# AST
ast.o: ast.c
	gcc -c ast.c

# Testes
teste1: etapa4
	clear
	cat teste2.txt | ./etapa4

# Compacta para envio
targz: clean
	tar cvzf etapa4.tgz main.c parser.y makefile scanner.l ast.* valor_lexico.* list.*
	#scp etapa4.tgz dlspsilva@html.inf.ufrgs.br:./public_html/

# VALGRIND
valgrind: etapa4
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=leak.txt -v ./etapa4 < ../etapa2/testes/asl49

# Limpeza de arquivos exec
clean:
	rm -rf *.o lex.yy.c parser.output parser.tab.c parser.tab.h etapa4 leak.txt
