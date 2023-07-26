CC = gcc
CFLAGS = -Wall -Wextra -g

all: main

main: main.o functions.o readFile_randWord.c
	$(CC) $(CFLAGS) main.o functions.o readFile_randWord.c -o main

main.o: main.c functions.h
	$(CC) $(CFLAGS) -c main.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

clean:
	rm -f main *.o