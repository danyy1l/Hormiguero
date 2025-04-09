CC=gcc
EXE=set_test
CFLAGS=-g -c -Wall -ansi -pedantic

###########################################################################

$(EXE): set_test.o set.o
	$(CC) -o $(EXE) *.o

character_test.o: set_test.c
	$(CC) $(CFLAGS) set_test.c

character.o: set.c
	$(CC) $(CFLAGS) set.c

run:
	$(MAKE); valgrind --leak-check=full ./$(EXE)

clean:
	rm -rf *.o $(EXE)