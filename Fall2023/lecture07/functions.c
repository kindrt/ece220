//									tab:8
//
// functions.c - example functions for ECE220 (S18 honors section)
//
// "Copyright (c) 2004-2018 by Steven S. Lumetta."
//
// Permission to use, copy, modify, and distribute this software and its
// documentation for any purpose, without fee, and without written agreement is
// hereby granted, provided that the above copyright notice and the following
// two paragraphs appear in all copies of this software.
// 
// IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO 
// ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL 
// DAMAGES ARISING OUT  OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, 
// EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED 
// OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE 
// PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
// THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE, 
// SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
//
// Author:	    Steve Lumetta
// Version:	    1
// Creation Date:   5 February 2018
// Filename:	    functions.c
// History:
//	SL	1	5 February 2018
//		First written, with some parts based on notes.
///

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>


//
// reverse_bits -- reverse the bits in a 32-bit integer
//
// INPUTS: arg -- the bits to be reversed 
// OUTPUTS: none
// RETURN VALUE: bits of arg in reverse order
// SIDE EFFECTS: none
// COMMENTS: In Spring 2007, students had to write this function 
//           (for 16 bits) in binary LC-3 instructions.
//

uint32_t
reverse_bits (uint32_t arg)
{
    int32_t  i;			// iteration counter for bits
    uint32_t result = 0;	// result to be returned

    // Loop over all bits in arg.
    for (i = 0; 32 > i; i++) {

	// Shift result left and copy a new bit from arg.
        result = ((result << 1) | (arg & 1));

	// Discard the copied bit from arg.
	arg >>= 1;
    }

    // All done.
    return result;
}


//
// convert_octal -- convert a five-digit octal value with a sign from
//                  ASCII into a 16-bit 2's complement integer
//
// INPUTS: sign -- sign of the octal value (assumed to be '+' or '-')
//         dmax -- digit one (most significant), from '0' to '7'
//         d2   -- digit two, from '0' to '7'
//         d3   -- digit three, from '0' to '7'
//         d4   -- digit four, from '0' to '7'
//         dmin -- digit five (least significant), from '0' to '7'
// OUTPUTS: none
// RETURN VALUE: value of octal constant as an int16_t
// SIDE EFFECTS: none
// COMMENTS: In Fall 2006, students had to write this function in
//           binary LC-3 instructions.  The C version is slightly
//           verbose (could be one line) to make the students that
//           semester feel better...
//

int16_t
convert_octal (char sign, char dmax, char d2, char d3, char d4, char dmin)
{
    int16_t total;	// result to be returned

    // Copy three bits at a time from ASCII into the binary version.
    total  = ((dmax - '0') << 12);
    total += ((d2   - '0') <<  9);
    total += ((d3   - '0') <<  6);
    total += ((d4   - '0') <<  3);
    total += ((dmin - '0') <<  0);

    // Check for negative numbers and negate if necessary.
    if ('-' == sign) {
        total = -total;
    }

    // All done.
    return total;
}


//
// print_slot -- print an hour slot for a schedule (for a particular
//               style of schedule defined by an ECE220 MP)
//
// INPUTS: slot -- the slot number from 0 to 15
// OUTPUTS: none
// RETURN VALUE: none
// SIDE EFFECTS: prints a five-character hour followed by a space
// COMMENTS: In Spring 2018, students had to write this function 
//           in LC-3 assembly.
//

void 
print_slot (int32_t slot)
{
    // Let's make it two lines by adding a comment!
    printf ("%02d:00 ", slot + 7);
}


//
// print_slot -- print a string centered (or truncated) in six spaces
//
// INPUTS: s -- the string (using a pointer--you'll see it soon)
// OUTPUTS: none
// RETURN VALUE: none
// SIDE EFFECTS: prints six characters
// COMMENTS: In Spring 2018, students had to write this function 
//           in LC-3 assembly.
//

void
print_centered (char* s)
{
    // strlen is a C library function.
    int32_t len = strlen (s);	// the string length (does not count NUL)

    // Check: center or truncate?
    if (6 >= len) {
	//
	// Center: * indicates that the next argument specifies field 
	// length, and the string is right justified with leading spaces.
	//
        printf ("%*s%*s", (6 + len) / 2, s, (7 - len) / 2, "");
    } else {
	// Truncate: .6 limits the output to six characters.
        printf ("%.6s", s);
    }
}


//
// guessing_game -- play a guessing game with the human user; human is
//                  given a certain number of tries to guess a secret
//                  number from 1 to 10, and is given feedback on each 
//                  guess
//
// INPUTS: number -- the secret number to be guessed, from 1 to 100
//         num_tries -- the number of tries allowed
// OUTPUTS: none
// RETURN VALUE: 1 if the human wins, 0 if the human loses,
//		 2 if the arguments are bad, and 3 if the human types
//               something besides a number
// SIDE EFFECTS: prints to the display, and reads from the keyboard
//

int32_t 
guessing_game (int32_t number, int32_t num_tries)
{
    int32_t guess;	// human's guess
    int32_t difference;	// difference between guess and secret number

    // Check the arguments.
    if (1 > number || 10 < number || 1 > num_tries) {
	// Bad arguments.
        return 2;
    }

    // Loop once for each try allowed.
    while (0 < num_tries--) {

	// Prompt the human.
    	printf ("Enter a number: ");

	// Read one guess.
	if (1 != scanf ("%d", &guess)) {
	    // The human has failed.  Reject it!
	    printf ("That's not a number!\n");
	    return 3;
	}

	// Calculate the difference.
	difference = guess - number;

	// Give feedback based on how close the guess is to the number.
	switch (difference) {
	    case 0: 
	        // The human has won the game!
	        printf ("You win!\n");
		return 1;
	    case 1:
	    case -1:
	        printf ("You're very close now...\n");
		break;
	    case 2:
	    case -2:
	        printf ("You're getting close.\n");
		break;
	    case 3:
	    case -3:
	        printf ("Not a bad guess.\n");
		break;
	    default:
	        printf ("Who are you kidding?  You'll never win.\n");
		break;
	}
    }

    // The human has lost.
    printf ("Tough break!\n");
    return 0;
}


int 
main ()
{
    uint32_t x = 42;		// my favorite number
    uint32_t x_rev;		// my favorite number, with bits reversed

    //
    // C uses call by value for function parameters, so x is
    // not changed (notice that the function DOES change the value
    // of its parameter, but the function's local variable is a
    // COPY of the value of main's variable x; the copy is
    // part of reverse_bits' stack frame, and is discarded when
    // that function finishes and control returns to main).
    //
    x_rev = reverse_bits (x);
    printf ("%08X in reverse\n", x_rev);
    printf ("%08X when not reversed\n", x);

    // The answer...in octal?
    int16_t answer = convert_octal ('+', '0', '0', '0', '5', '2');

    // converts answer implicitly to int when passed
    printf ("The answer is %d.\n", answer);

    // Loop counter for testing print_slot.
    int32_t i;	

    // Test print_slot.
    for (i = 0; 16 > i; i++) {
        printf ("\"");
	print_slot (i);
        printf ("\"\n");
    }

    // Test print_centered.
    printf ("\"");
    print_centered ("");
    printf ("\"\n\"");
    print_centered ("A");
    printf ("\"\n\"");
    print_centered ("AB");
    printf ("\"\n\"");
    print_centered ("ABC");
    printf ("\"\n\"");
    print_centered ("ABCD");
    printf ("\"\n\"");
    print_centered ("ABCDE");
    printf ("\"\n\"");
    print_centered ("ABCDEF");
    printf ("\"\n\"");
    print_centered ("ABCDEFGreally");
    printf ("\"\n");

    // Seed the pseudo-random number generator with the current time.
    srand (time (NULL));

    //
    // Again, even though the name of main's variable and guessing_game's
    // parameter are identical, the bits are not shared.  main's copy
    // is in the local variables portion of main's stack frame, and
    // guessing_game's copy is in the parameters portion of 
    // guessing_game's stack frame.
    //
    int32_t outcome;	// game outcome (needed by loop condition)
    do {
	int32_t number = (rand () % 10) + 1;		// secret from 1 to 10

	// Play the game.
	outcome = guessing_game (number, 3);

	switch (outcome) {
	    case 0:	// human lost
	        printf ("\nTry playing again.\n");
		break;
	    case 1:	// human won
	        printf ("Congratulations!\n");
		break;
    	    case 2:	// bad arguments
	    	printf ("Something went wrong with my code.  Oops!\n");
		break;
    	    case 3:	// human typed something incorrect
	    	printf ("Sorry, I can't reset the input.\n");
		break;
	}
    } while (0 == outcome);

    // 0 means success for a program (by convention).
    return 0;
}
