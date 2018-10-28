CC := g++
DOCDIR := doc
INCDIR := include
SRCDIR := src
BUILDDIR := build
TESTDIR := tests
SCRIPTDIR := scripts
LOGSDIR := logs
TARGET := bin/etapa4

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall
LIB := $() # -pthread -lmongoclient -L lib -lboost_thread-mt -lboost_filesystem-mt -lboost_system-mt
INC := -I include

$(TARGET): $(BUILDDIR)/parser.tab.o $(BUILDDIR)/lex.yy.o $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

# Regras do Flex
$(BUILDDIR)/lex.yy.o: $(BUILDDIR)/lex.yy.c
	$(CC) -c $(SRCDIR)/lex.yy.c -o $(BUILDDIR)/lex.yy.o

$(BUILDDIR)/lex.yy.c: $(SRCDIR)/scanner.l
	flex -o $(SRCDIR)/lex.yy.c $(SRCDIR)/scanner.l

# Regras do Bison
$(BUILDDIR)/parser.tab.o: $(BUILDDIR)/parser.tab.c
	$(CC) -c $(SRCDIR)/parser.tab.c -o $(BUILDDIR)/parser.tab.o

$(BUILDDIR)/parser.tab.c: $(SRCDIR)/parser.y
	bison -o $(SRCDIR)/parser.tab.c -d -v $(SRCDIR)/parser.y
	mv $(SRCDIR)/parser.output $(LOGSDIR)/parser.output
	mv $(SRCDIR)/parser.tab.h $(INCDIR)/parser.tab.h

# Limpa todos os arquivos que podem ser buildados
clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)


# Compacta para envio
targz: clean
	tar cvzf etapa4.tgz $(DOCDIR) $(INCDIR) $(SCRIPTDIR) $(SRCDIR) $(TESTDIR) makefile
	#scp etapa4.tgz dlspsilva@html.inf.ufrgs.br:./public_html/

# Roda o Valgrind
#valgrind: etapa4
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=leak.txt -v ./etapa4 < ../etapa2/testes/asl49

# Tests
tester:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester
