CC=gcc
EXE=player_test
CFLAGS=-g -c -Wall -ansi -pedantic

###########################################################################

$(EXE): player_test.o player.o object.o set.o inventory.o
	$(CC) -o $(EXE) *.o

player_test.o: player_test.c
	$(CC) $(CFLAGS) player_test.c
player.o: player.c
	$(CC) $(CFLAGS) player.c
object.o: object.c
	$(CC) $(CFLAGS) object.c
set.o: set.c
	$(CC) $(CFLAGS) set.c
inventory.o: inventory.c
	$(CC) $(CFLAGS) inventory.c

run:
	$(MAKE); valgrind --leak-check=full ./$(EXE)

clean:
	rm -rf *.o $(EXE)