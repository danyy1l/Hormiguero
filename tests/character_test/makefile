CC=gcc
EXE=character_test
CFLAGS=-g -c -Wall -ansi -pedantic

###########################################################################

$(EXE): character_test.o character.o
	$(CC) -o $(EXE) *.o

character_test.o: character_test.c
	$(CC) $(CFLAGS) character_test.c

character.o: character.c
	$(CC) $(CFLAGS) character.c

run:
	$(MAKE); valgrind --leak-check=full ./$(EXE)

clean:
	rm -rf *.o $(EXE)