EXE=anthill
CFLAGS=-g -c -Wall -ansi -pedantic
CC=gcc
CLIB=-lscreen -L.

##############################################################################################################

anthill: player.o object.o space.o command.o game_actions.o game_reader.o game.o graphic_engine.o game_loop.o
	$(CC) -o $(EXE) *.o $(CLIB)

player.o: classes/player.c
	$(CC) $(CFLAGS) classes/player.c

object.o: classes/object.c
	$(CC) $(CFLAGS) classes/object.c

space.o: classes/space.c
	$(CC) $(CFLAGS) classes/space.c

command.o: scripts/command.c
	$(CC) $(CFLAGS) scripts/command.c

game_actions.o: scripts/game_actions.c
	$(CC) $(CFLAGS) scripts/game_actions.c

game_reader.o: scripts/game_reader.c
	$(CC) $(CFLAGS) scripts/game_reader.c

game.o: scripts/game.c
	$(CC) $(CFLAGS) scripts/game.c

graphic_engine.o: graphic/graphic_engine.c
	$(CC) $(CFLAGS) graphic/graphic_engine.c

game_loop.o: main/game_loop.c
	$(CC) $(CFLAGS) main/game_loop.c

#CLEAN .o AND EXE
clean: 
	rm -f *.o $(EXE) 

#COMPILE AND RUN PROGRAM
run: 
	@$(MAKE) && ./$(EXE) $(EXE).dat

#RUN WITH VALGRIND TO CHECK MEMLEAKS
runv:
	@$(MAKE) && valgrind --leak-check=full ./$(EXE) $(EXE).dat