CFLAGS= -ggdb -O0 -Wall -Werror -std=c++11 -fsanitize=address
CC = g++

all: exec

exec: esercizio.cpp
	$(CC) $(CFLAGS) -o exec esercizio.cpp -I.

clean:
	rm -f *.o exec
	rm -r exec.dSYM


