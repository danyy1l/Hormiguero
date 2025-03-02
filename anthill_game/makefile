EXE=anthill
CFLAGS=-g -c -Wall -ansi -pedantic
CC=gcc
CLIB=-lscreen -L./lib/

######################################################################
# $@ es el item que aparece a la izquierda de ':'
# $< es el primer item en la lista de dependencias
# $^ son todos los archivos que se encuentran a la derecha de ':' (dependencias)
########################################################################

all: anthill

anthill: player.o object.o space.o command.o character.o set.o game_actions.o game_reader.o game.o graphic_engine.o game_loop.o
	$(CC) -o $@ $^ $(CLIB)

player.o: src/player.c
	$(CC) $(CFLAGS) $<

object.o: src/object.c
	$(CC) $(CFLAGS) $<

space.o: src/space.c
	$(CC) $(CFLAGS) $<

command.o: src/command.c
	$(CC) $(CFLAGS) $<

character.o: src/character.c
	$(CC) $(CFLAGS) $<

set.o: src/set.c
	$(CC) $(CFLAGS) $<

game_actions.o: src/game_actions.c
	$(CC) $(CFLAGS) $<

game_reader.o: src/game_reader.c
	$(CC) $(CFLAGS) $<

game.o: src/game.c
	$(CC) $(CFLAGS) $<

graphic_engine.o: src/graphic_engine.c
	$(CC) $(CFLAGS) $<

game_loop.o: src/game_loop.c
	$(CC) $(CFLAGS) $<

#CLEAN .o AND EXE
clean: 
	rm -f *.o $(EXE) 

#COMPILE AND RUN PROGRAM
run: 
	@$(MAKE) && ./$(EXE) $(EXE).dat

#RUN WITH VALGRIND TO CHECK MEMLEAKS
runv:
	@$(MAKE) && valgrind --leak-check=full ./$(EXE) $(EXE).dat