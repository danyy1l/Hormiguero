EXE=anthill
CFLAGS=-g -c -Wall -pedantic
CC=gcc
CLIB=-lscreen -L./lib/
OBJDIR=obj
DOXDIR=doc
LOG=logFile
vpath %.c src
vpath %.h include

######################################################################
# $@ es el item que aparece a la izquierda de ':'
# $< es el primer item en la lista de dependencias
# $^ son todos los archivos que se encuentran a la derecha de ':' (dependencias)
########################################################################

all: $(EXE)

objects = $(addprefix $(OBJDIR)/, player.o object.o space.o command.o character.o set.o link.o inventory.o\
	game_actions.o game_reader.o game.o graphic_engine.o game_loop.o)

$(EXE): $(objects)
	$(CC) -o $@ $^ $(CLIB)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

#CLEAN .o AND EXE
clean: 
	rm -rf $(OBJDIR) $(DOXDIR) $(EXE) $(LOG).dat

#COMPILE AND RUN PROGRAM
run: 
	@$(MAKE) && ./$(EXE) $(EXE).dat

#RUN WITH VALGRIND TO CHECK MEMLEAKS
runv:
	@$(MAKE) && valgrind --leak-check=full --show-leak-kinds=all ./$(EXE) $(EXE).dat

#RUN WITH LOG
runlog:
	@$(MAKE) && ./$(EXE) $(EXE).dat -l $(LOG).dat

#RUN WITH CMD1
runcmd1:
	@$(MAKE) && ./$(EXE) $(EXE).dat -l $(LOG).dat < game1.cmd

#RUN WITH CMD2
runcmd2:
	@$(MAKE) && ./$(EXE) $(EXE).dat -l $(LOG).dat < game2.cmd

#RUN WITH SEED
runseed: 
	@$(MAKE) && ./$(EXE) $(EXE).dat	-d

#RUN WITH SEED AND LOG
runseedlog: 
	@$(MAKE) && ./$(EXE) $(EXE).dat -l $(LOG).dat -d

#DOXYGEN
doc:
	doxygen Doxyfile