CC= gcc
CFLAGS= -c -Wvla -Wall
CODEFILES= ex2.tar  battleships.c battleships_game.c battleships.h Makefile


# make ex2.exe
ex2: battleships.o battleships_game.o
	$(CC) battleships.o battleships_game.o -o ex2

# make battleships file
battleships.o: battleships.c battleships.h
	$(CC) $(CFLAGS) battleships.c

# make battleships_game file
battleships_game.o: battleships_game.c battleships.h battleships.c
	$(CC) $(CFLAGS) battleships_game.c

# make clean
clean:
	-rm -f *.o  ex2

# Things that aren't really build targets
.PHONY: clean
