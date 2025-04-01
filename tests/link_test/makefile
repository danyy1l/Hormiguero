CC=gcc
EXE=link-test
CFLAGS=-g -c -Wall -ansi -pedantic

###########################################################################

$(EXE): link_test.o link.o set.o
	$(CC) -o $(EXE) *.o

link_test.o: link_test.c
	$(CC) $(CFLAGS) link_test.c

link.o: link.c
	$(CC) $(CFLAGS) link.c

run:
	$(MAKE); valgrind --leak-check=full ./$(EXE)

clean:
	rm -rf *.o $(EXE)