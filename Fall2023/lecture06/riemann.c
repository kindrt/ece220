/* Compute integral of f(x) = x*x+2x+3 on [a,b].
   Adapted from V. Kindratenko's notes on 30 August 2016.
*/

/* to compile: gcc riemann.c -o riemann
 * to run: ./riemann
*/

#include <stdio.h>

int main()
{
    int   n =   100; /* hardcoded number of Riemann sum terms */
    float a = -1.0f; /* hardcoded [a,b] */
    float b =  1.0f;
    float s =  0.0f; /* computed integral value */
    int   i;         /* loop counter */
    float x;         /* x and y=f(x) */
    float y;
    float dx = (b - a) / n; /* width of rectangles */

    /* Sum n rectangles. */
    for (i = 0; n > i; i = i + 1) 
    {
        /* x values are equally spaced from a to b. */
        x = a + dx * i;

        /* y values are f(x). */
        y = x * x + 2 * x + 3;

        /* Rectangle is y high and dx wide. */
        s = s + y * dx;
    }

    printf ("%f\n", s);

    return 0;
}
