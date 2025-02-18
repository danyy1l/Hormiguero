EXE=anthill
CFLAGS=-g -c -Wall -ansi -pedantic
CC=gcc
CLIB=-lscreen -L./lib/

##############################################################################################################

anthill: player.o object.o space.o command.o character.o game_actions.o game_reader.o game.o graphic_engine.o game_loop.o
	$(CC) -o $(EXE) *.o $(CLIB)

player.o: src/player.c
	$(CC) $(CFLAGS) src/player.c

object.o: src/object.c
	$(CC) $(CFLAGS) src/object.c

space.o: src/space.c
	$(CC) $(CFLAGS) src/space.c

command.o: src/command.c
	$(CC) $(CFLAGS) src/command.c

character.o: src/character.c
	$(CC) $(CFLAGS) src/character.c

game_actions.o: src/game_actions.c
	$(CC) $(CFLAGS) src/game_actions.c

game_reader.o: src/game_reader.c
	$(CC) $(CFLAGS) src/game_reader.c

game.o: src/game.c
	$(CC) $(CFLAGS) src/game.c

graphic_engine.o: src/graphic_engine.c
	$(CC) $(CFLAGS) src/graphic_engine.c

game_loop.o: src/game_loop.c
	$(CC) $(CFLAGS) src/game_loop.c

#CLEAN .o AND EXE
clean: 
	rm -f *.o $(EXE) 

#COMPILE AND RUN PROGRAM
run: 
	@$(MAKE) && ./$(EXE) $(EXE).dat

#RUN WITH VALGRIND TO CHECK MEMLEAKS
runv:
	@$(MAKE) && valgrind --leak-check=full ./$(EXE) $(EXE).dat