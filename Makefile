CFLAGS=-l pthread
CC=gcc $(CFLAGS)
OBJECTS=sync.o main.o

all:
	clang -Wall -lpthread main.c sync.c -o mylocks

mylocks: $(OBJECTS) 
	$(CC) $(OBJECTS) -o mylocks
clean:
	rm -f mylocks main.o
run: mylocks
	./mylocks
