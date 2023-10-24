CC = gcc
CFLAGS =-Wall -g
DEPS = llist.h
OBJ = llist.o main.o 

all: llist

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

llist: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o
	rm -f llist a.out
