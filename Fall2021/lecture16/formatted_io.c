/* to compile: gcc formatted_io.c -o formatted_io
   to run:  ./formatted_io
   to see results: cat transposed_array.txt
   to see original input: cat array.txt
   */

#include <stdio.h>

#define N 100
#define M 100

int main()
{
    FILE *inf;
    FILE *outf;
    int n, m;
    int i, j;
    int array[N][M];

    /* read from file */
    if ((inf = fopen("array.txt", "r")) == NULL)
    {
        printf("Unable to open file array.txt for reading\n");
        return -1;
    }

    fscanf(inf, "%i %i", &n, &m);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            fscanf(inf, "%i", &array[i][j]);

    fclose(inf);

    /* write to file */
    if ((outf = fopen("transposed_array.txt", "w")) == NULL)
    {
        printf("Unable to open file outputfile.txt for writing\n");
        return -1;
    }

    fprintf(outf, "%i %i\n", m, n);
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
            fprintf(outf, "%i ", array[j][i]);
        fprintf(outf, "\n");
    }

    fclose(outf);

    return 0;
}