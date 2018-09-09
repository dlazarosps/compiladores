# MAKEFILE ETAPA 2
all: etapa2

etapa2: y.tab.o lex.yy.o hash.o main.o
	gcc y.tab.o lex.yy.o hash.o main.o -o etapa2

main.o: main.c
	gcc -c main.c

# HASH
hash.o: hash.c
	gcc hash.c -c

# BISON
y.tab.o: y.tab.c
		gcc -c y.tab.c

y.tab.c: parser.y
	bison -d -v parser.y

# FLEX
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l
	flex scanner.l

# Testes
# teste1: etapa2
# 	clear
# 	cat exemplo.txt | ./etapa2

# teste2: etapa2
# 	clear
# 	cat exemplo2.txt | ./etapa2

clean:
	rm -rf *.o lex.yy.c y.tab.c y.tab.h y.output etapa2
	sleep 1
	clear
