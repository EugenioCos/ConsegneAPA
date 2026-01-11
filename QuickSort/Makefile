#CFLAGS= -ggdb -Wall -fsanitize=address
CFLAGS= -Wall
CC = gcc
DIR = LIB

all: exec

math.o: $(DIR)/math.c
	$(CC) $(CFLAGS) -c $(DIR)/math.c

quicksort.o: $(DIR)/quicksort.c
	$(CC) $(CFLAGS) -c $(DIR)/quicksort.c

exec: quicksort.o math.o esercizio.c
	$(CC) $(CFLAGS) -o exec quicksort.o math.o esercizio.c
	rm *.o

clean:
	rm -f *.o exec


