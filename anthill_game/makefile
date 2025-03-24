EXE=anthill
CFLAGS=-g -c -Wall -pedantic
CC=gcc
CLIB=-lscreen -L./lib/
OBJDIR=obj
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
	rm -rf $(OBJDIR) $(EXE)

#COMPILE AND RUN PROGRAM
run: 
	@$(MAKE) && ./$(EXE) $(EXE).dat

#RUN WITH VALGRIND TO CHECK MEMLEAKS
runv:
	@$(MAKE) && valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(EXE) $(EXE).dat
