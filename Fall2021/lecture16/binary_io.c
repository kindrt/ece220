/* to compile: gcc binary_io.c -o binary_io
   to run:  ./binary_io
   to see results: hexdump -C -v binary_array.dat
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

    /* read from file in ASCII */
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

    /* write to file in binary */
    if ((outf = fopen("binary_array.dat", "w")) == NULL)
    {
        printf("Unable to open file outputfile.txt for writing\n");
        return -1;
    }

    for (i = 0; i < n; i++)
        fwrite(array[i], sizeof(int), m, outf);

    fclose(outf);

    return 0;
}