CC := g++
DOCDIR := doc
INCDIR := include
SRCDIR := src
BUILDDIR := build
TESTDIR := tests
SCRIPTDIR := scripts
LOGSDIR := logs
BINDIR := bin
TARGET := etapa6

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall -std=c++11

LIB := $() # -pthread -lmongoclient -L lib -lboost_thread-mt -lboost_filesystem-mt -lboost_system-mt
INC := -I include

$(BINDIR)/$(TARGET): $(BUILDDIR)/parser.tab.o $(BUILDDIR)/lex.yy.o $(OBJECTS)
	@echo " Linking..."
	@mkdir -p $(BINDIR)
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(BINDIR)/$(TARGET) $(LIB)
	@cp $(BINDIR)/$(TARGET) $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

# Regras do Flex
$(BUILDDIR)/lex.yy.o: $(SRCDIR)/lex.yy.c
	@mkdir -p $(BUILDDIR)
	$(CC) -c $(SRCDIR)/lex.yy.c -o $(BUILDDIR)/lex.yy.o

$(SRCDIR)/lex.yy.c: $(SRCDIR)/scanner.l
	flex -o $(SRCDIR)/lex.yy.c $(SRCDIR)/scanner.l

# Regras do Bison
$(BUILDDIR)/parser.tab.o: $(SRCDIR)/parser.tab.c
	@mkdir -p $(BUILDDIR)
	$(CC) -c $(SRCDIR)/parser.tab.c -o $(BUILDDIR)/parser.tab.o

$(SRCDIR)/parser.tab.c: $(SRCDIR)/parser.y
	@mkdir -p $(LOGSDIR)
	bison -o $(SRCDIR)/parser.tab.c -d -v $(SRCDIR)/parser.y
	mv $(SRCDIR)/parser.output $(LOGSDIR)/parser.output
	mv $(SRCDIR)/parser.tab.h $(INCDIR)/parser.tab.h

# Limpa todos os arquivos que podem ser buildados
clean:
	@echo "> Cleaning...";
	@echo "> Removing objects...";
	$(RM) -r $(BUILDDIR)
	@echo "> Removing flex and bison generated files...";
	$(RM) $(SRCDIR)/lex.yy.c
	$(RM) $(SRCDIR)/parser.tab.c
	$(RM) $(INCDIR)/parser.tab.h
	@echo "> Removing logs...";
	$(RM) -r $(LOGSDIR)/*
	@echo "> Removing test leftovers...";
	$(RM) -r $(TESTDIR)/CMakeFiles
	$(RM) $(TESTDIR)/cmake_install.cmake
	$(RM) $(TESTDIR)/CMakeCache.txt
	$(RM) $(TESTDIR)/Makefile
	@echo "> Removing binaries...";
	$(RM) -r $(BINDIR)
	$(RM) $(TARGET)

# Compacta para envio
targz: clean
	tar cvzf etapa6.tgz $(INCDIR) $(SRCDIR) $(TESTDIR) makefile README.md
	#scp etapa6.tgz dlspsilva@html.inf.ufrgs.br:./public_html/

# Roda o Valgrind
#valgrind: etapa6
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=leak.txt -v ./etapa6 < ../etapa2/testes/asl49

# Tests
test: $(TARGET)
	cmake $(TESTDIR)/CMakeLists.txt
	make -C $(TESTDIR)
	$(TESTDIR)/runTests
