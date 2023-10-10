/* to compile: gcc one_char.c -o one_char
   to run:  ./one_char
   to see results: cat out.txt
   */

#include <stdio.h>

int main()
{
    int c;
    FILE *f;

    /* write to file */
    f = fopen("out.txt", "w");
    if (f == NULL)
    {
        printf("Unable to open file out.txt for writing\n");
        return -1;
    }

    c = getchar();
    while (c != '\n')
    {
        fputc(c, f);
        c = getchar();
    }

    fclose(f);

    /* read from file */
    if ((f = fopen("out.txt", "r")) == NULL)
    {
        printf("Unable to open file out.txt for reading\n");
        return -1;
    }

    c = fgetc(f);
    while (c != EOF) /* EOF is a macro defined in stdio.h */
    {
        putchar(c);
        c = fgetc(f);
    }

    putchar('\n');

    fclose(f);

    return 0;
}