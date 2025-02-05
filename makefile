anthill: command.o game_actions.o game_reader.o player.o game.o graphic_engine.o space.o game_loop.o
	gcc -o anthill *.o -lscreen -L. 

command.o: command.c
	gcc -g -c -Wall command.c

game_actions.o: game_actions.c
	gcc -g -c -Wall game_actions.c

game_reader.o: game_reader.c
	gcc -g -c -Wall game_reader.c

player.o: player.c
	gcc -g -c -Wall player.c

game.o: game.c
	gcc -g -c -Wall game.c

graphic_engine.o: graphic_engine.c
	gcc -g -c -Wall graphic_engine.c

space.o: space.c
	gcc -g -c -Wall space.c

game_loop.o: game_loop.c
	gcc -g -c -Wall game_loop.c

clean: 
	rm *.o anthill
