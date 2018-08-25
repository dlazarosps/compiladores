# MAKEFILE ETAPA 1
all: etapa1

etapa1: lex.yy.o main.o
	gcc -o etapa1 lex.yy.o main.o

# com hash table
#etapa1: lex.yy.o main.o hash.o
#	gcc -o etapa1 lex.yy.o main.o hash.o

main.o: main.c
	gcc -c main.c

# TODO hash table (etapa 1?)
# hash.o: hash.c 
#	gcc -c hash.c

# FLEX
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l
	flex scanner.l

# Testes
teste1: etapa1
	clear
	cat exemplo.txt | ./etapa1

teste2: etapa1
	clear
	cat exemplo2.txt | ./etapa1

clean:
	rm -rf *.o lex.yy.c etapa1
	sleep 1
	clear