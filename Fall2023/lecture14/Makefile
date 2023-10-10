CC := gcc
CFLAGS :=-Wall -g
LDFLAGS := -g
EXE := one_char one_string formatted_io binary_io print_log

all: ${EXE}

%.o: %.c 
	${CC} -c ${CFLAGS} -o $@ $<

one_char: one_char.c
	$(CC) one_char.c -o one_char ${LDFLAGS}

one_string: one_string.c
	$(CC) one_string.c -o one_string ${LDFLAGS}

formatted_io: formatted_io.c
	$(CC) formatted_io.c -o formatted_io ${LDFLAGS}

binary_io: binary_io.c
	$(CC) binary_io.c -o binary_io ${LDFLAGS}

print_log: print_log.c
	$(CC) print_log.c -o print_log ${LDFLAGS}

clean::
	rm -f *.o
	rm -f ${EXE} a.out
	rm -f binary_array.dat out.txt outputfile.txt transposed_array.txt logfile.txt
