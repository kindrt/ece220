/*
 * ECE220 Spring 2018
 *
 * Program name: translate.c, a number translator
 *
 * Description: This program asks for a decimal number, then prints out
 *              the absolute value of the number in hexadecimal form.
 *
 * History: adapted from 2005 ECE190 code
 */

/* 
 * DISCLAIMER: In this file, we use 'int32_t' for clarity on integer
 * sizes in C code.  However, when we think about the LC-3 stack frames 
 * and code corresponding to these functions, we will instead treat all 
 * integers as 16-bit for simplicity.
 */

#include <stdint.h>       /* Include C's ISA-independent integer type file. */
#include <stdio.h>        /* Include C's standard I/O header file.          */

static int32_t the_number;   /* the number -- no good reason to be a global 
			        variable other than to serve the purpose of 
			        the example */

/* 
 * Function: find_abs
 * Description: convert an integer to its absolute value
 * Parameters: the number to convert
 * Return Value: the absolute value of the number passed
 */

int32_t
find_abs (int32_t num)
{
    int32_t abs_value;

    // Let's use a conditional operator.  For non-negative values,
    // the absolute value is the number itself.  For negative values,
    // we negate to find the absolute value.
    abs_value = (0 <= num ? num : -num);

    return abs_value;
}

/* 
 * Function: main
 * Description: prompt user for a decimal number, then print absolute value 
 *              in hexadecimal
 * Parameters: none (we're ignoring the standard ones to main for now)
 * Return Value: 0, which by convention indicates success
 */

int
main ()
{
    /* no local variable declarations */

    /* Prompt the human user for a number. */
    printf ("Please enter a decimal number: ");

    /* 
     * Read in a number.  Give up (and return a non-zero value for failure)
     * if the human can't type a number.
     */
    if (1 != scanf ("%d", &the_number)) {
        printf ("I don't think that word means what you think it means.\n");
	return 3;
    }

    /* Find the absolute value. */
    the_number = find_abs (the_number);

    /* Print the answer. */
    printf ("The absolute value in hexadecimal is %x.\n", the_number);

    /* Program finished successfully. */
    return 0;
}

