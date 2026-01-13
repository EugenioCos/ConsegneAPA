CFLAGS= -std=c++14 -g -O0 -fsanitize=address -fno-omit-frame-pointer
CC = g++
DIR = lib

all: exec

exec: $(DIR)/graph.cpp esercizio.cpp
	$(CC) $(CFLAGS) -o exec $(DIR)/graph.cpp esercizio.cpp
	rm -r exec.dSYM

clean:
	rm exec


