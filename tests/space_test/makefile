CC=gcc
EXE=space_test
CFLAGS=-g -c -Wall -ansi -pedantic

###########################################################################

$(EXE): space_test.o space.o set.o
	$(CC) -o $(EXE) *.o

space_test.o: space_test.c
	$(CC) $(CFLAGS) space_test.c

space.o: space.c
	$(CC) $(CFLAGS) space.c

set.o: set.c
	$(CC) $(CFLAGS) set.c

run:
	$(MAKE) && valgrind --leak-check=full --track-origins=yes ./$(EXE)

clean:
	rm -rf *.o $(EXE)