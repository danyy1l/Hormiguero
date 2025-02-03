anthill: command.o game_actions.o game.o graphic_engine.o space.o game_loop.o 
	gcc -o anthill *.c -lscreen -L. 

command.o: command.c command.h types.h
	gcc -g -c -Wall command.c

game_actions.o: game_actions.c game_actions.h
	gcc -g -c -Wall game_actions.c

game.o: game.c game.h
	gcc -g -c -Wall game.c

graphic_engine.o: graphic_engine.c graphic_engine.h
	gcc -g -c -Wall graphic_engine.c

space.o: space.c space.h
	gcc -g -c -Wall space.c

game_loop.o: game_loop.c
	gcc -g -c -Wall game_loop.c
