CC = gcc
CFLAGS =-Wall -g
DEPS = player.h
OBJ = player.o main.o 

all: llink

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

llink: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o
	rm -f llink a.out
