CC = gcc
CFLAGS =-Wall -g
DEPS = tree.h
OBJ = tree.o main.o 

all: tree

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tree: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o
	rm -f tree a.out
