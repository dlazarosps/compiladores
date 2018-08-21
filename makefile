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
 
clean:
	rm *.o lex.yy.c etapa1
