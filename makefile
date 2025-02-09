EXE=anthill
CFLAGS=-g -c -Wall -ansi -pedantic
CC=gcc
CLIB=-lscreen -L.

anthill: command.o game_actions.o game_reader.o player.o object.o game.o graphic_engine.o space.o game_loop.o
	$(CC) -o $(EXE) *.o $(CLIB)

command.o: command.c
	$(CC) $(CFLAGS) command.c

game_actions.o: game_actions.c
	$(CC) $(CFLAGS) game_actions.c

game_reader.o: game_reader.c
	$(CC) $(CFLAGS) game_reader.c

player.o: player.c
	$(CC) $(CFLAGS) player.c

object.o: object.c
	$(CC) $(CFLAGS) object.c

game.o: game.c
	$(CC) $(CFLAGS) game.c

graphic_engine.o: graphic_engine.c
	$(CC) $(CFLAGS) graphic_engine.c

space.o: space.c
	$(CC) $(CFLAGS) space.c

game_loop.o: game_loop.c
	$(CC) $(CFLAGS) game_loop.c

clean: 
	rm *.o -f $(EXE) 

run: 
	@$(MAKE) && ./$(EXE) $(EXE).dat