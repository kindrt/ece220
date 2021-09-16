/*
 * ECE190 Fall 2005
 *
 * Program name: dump_memory.c, a procedure to print the contents of memory
 *
 * Description: This function uses the LC-3 simulator's read_memory function
 *              to print the contents of memory from a starting address to
 *              an ending address (both given as parameters).
 */

#include <stdio.h>        /* Include C's standard I/O header file.           */

#include "lc3sim.h"       /* Include the header file for the LC-3 simulator. */

/* 
 * Function: dump_memory
 * Description: print a range of LC-3 memory in hexadecimal
 * Parameters: the starting and ending addresses; the range printed does
 *             not include the ending address, but stops at the previous
 *             location
 * Return Value: nothing
 */

void
dump_memory (int addr_s, int addr_e)
{
    int start;    /* First address of line being printed.                   */
    int addr;     /* Address being printed.                                 */
    int index;    /* Index of address being printed on current line (0-11). */

    /* Simplify code by not using modular arithmetic for address range.
       If given range wraps around 0, replace the ending address with
       one that is larger than the starting address, but equivalent 
       modulo the size of the memory space. */
    if (addr_s >= addr_e)
        addr_e += 0x10000;

    /* Loop 12 addresses at a time.  Starting addresses for lines must
       be multiples of 12. */
    for (start = (addr_s / 12) * 12; start < addr_e; start = start + 12) {

	/* Print an address at the start of each line.  Since start
	   is not necessarily in the valid range 0 to 0xFFFF, we first
	   AND it with 0xFFFF. */
        printf ("%04X: ", start & 0xFFFF);

	/* This loop goes over all 12 addresses in the current line. 
	   The index variable runs from 0 to 11 (counts to 12), while
	   the addr variable tracks the address currently being printed. */
        for (index = 0, addr = start; index < 12; index++, addr++) {

	    /* We only print an address if it lies within the requested
	       range.  The value in memory is returned by the call to
	       read_memory.  If an address is not within the requested
	       range, we print blank space for printing alignment purposes. */
            if (addr >= addr_s && addr < addr_e)
                printf ("%04X ", read_memory (addr & 0xFFFF));
            else
                printf ("     ");
        }

	/* End the printed line. */
        puts ("");
    }
}

/* a sample of the output
 * 01F8:                                         E002 F022 F025 000A
 * 0204: 0057 0065 006C 0063 006F 006D 0065 0020 0074 006F 0020 0074
 * 0210: 0068 0065 0020 004C 0043 002D 0033 0020 0073 0069 006D 0075
 * 021C: 006C 0061 0074 006F 0072                                   
*/