CC=gcc
EXE=object-test
CFLAGS=-g -c -Wall -ansi -pedantic

###########################################################################

$(EXE): object_test.o object.o
	$(CC) -o $(EXE) *.o

object_test.o: object_test.c
	$(CC) $(CFLAGS) object_test.c

objectr.o: object.c
	$(CC) $(CFLAGS) object.c

run:
	$(MAKE); valgrind --leak-check=full ./$(EXE)

clean:
	rm -rf *.o $(EXE)