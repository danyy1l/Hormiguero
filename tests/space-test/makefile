CC=gcc
EXE=space-test
CFLAGS=-g -c -Wall -ansi -pedantic

###########################################################################

$(EXE): space_test.o space.o
	$(CC) -o $(EXE) *.o

space_test.o: space_test.c
	$(CC) $(CFLAGS) space_test.c

space.o: space.c
	$(CC) $(CFLAGS) space.c

run:
	$(MAKE) && valgrind --leak-check=full --track-origins=yes ./$(EXE)

clean:
	rm -rf *.o $(EXE)