CC = gcc
CFLAGS =-Wall -g
DEPS = ppm.h
OBJ = ppm.o main.o 

all: ppmtest

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ppmtest: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o
	rm -f ppmtest a.out
