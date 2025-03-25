CC=gcc
EXE=inventory-test
CFLAGS=-g -c -Wall -ansi -pedantic

###########################################################################

$(EXE): inventory_test.o inventory.o set.o
	$(CC) -o $(EXE) *.o

inventory_test.o: inventory_test.c
	$(CC) $(CFLAGS) inventory_test.c

inventory.o: inventory.c
	$(CC) $(CFLAGS) inventory.c

set.o: set.c
	$(CC) $(CFLAGS) set.c	

run:
	$(MAKE); valgrind --leak-check=full ./$(EXE)

clean:
	rm -rf *.o $(EXE)