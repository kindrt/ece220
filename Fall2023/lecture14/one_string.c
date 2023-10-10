/* to compile: gcc one_string.c -o one_string
   to run:  ./one_string
   to see results: cat outputfile.txt
   to compare with the original input: diff example.txt outputfile.txt
   */

#include <stdio.h>

int main()
{
    FILE *inf;
    FILE *outf;
    char buf[32];

    if ((inf = fopen("example.txt", "r")) == NULL)
    {
        printf("Unable to open file inputfile.txt for reading\n");
        return -1;
    }

    if ((outf = fopen("outputfile.txt", "w")) == NULL)
    {
        printf("Unable to open file outoutfile.txt for writing\n");
        fclose(inf);
        return -1;
    }

    fgets(buf, sizeof(buf), inf);
    while (!feof(inf)) /* feof tests the end-of-file indicator */
    {
        fputs(buf, outf);
        fgets(buf, sizeof(buf), inf);
    }

    fclose(inf);
    fclose(outf);

    return 0;
}