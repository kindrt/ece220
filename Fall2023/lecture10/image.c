#include <stdio.h>

#define HEIGHT 8
#define WIDTH 10

int Match(unsigned char *imgptr, int width, int height, unsigned char *blkptr);
 
int main() 
{
    unsigned char Image[HEIGHT][WIDTH];
    unsigned char *imgptr = (unsigned char *)Image;

    unsigned char Blk[4][4];
    unsigned char *blkptr = (unsigned char *)Blk;

    int i, j, count;

    /* fill in image with some pattern and print it */
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            Image[i][j] = i * j % 4;
            printf("%d ", Image[i][j]);
        }
        printf("\n");
    } 

    /* fill in block with some pattern and print it */
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            Blk[i][j] = i * j % 4;
            printf("%d ", Blk[i][j]);
        }
        printf("\n");
    }

    /* call the Match function */
    count = Match(imgptr, WIDTH, HEIGHT, blkptr);

    printf("Number of matching boxes: %d\n", count);

    return 0;
 }
 
 int Match(unsigned char *imgptr, int width, int height, unsigned char *blkptr) 
 {
    int row, col, i, j;
    int match, count = 0;

    for (row = 0; row < height; row++) {
        for (col = 0; col < width; col++) {
    
        match = 1; /* we initially assume this block will match */

        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (row+i < height && col+j < width) {
                    if (imgptr[(row+i)*width + (col+j)] != blkptr[i*4+j])
                        match = 0;
                }
                else
                    match = 0;
            }
        }
        if (match)
            count++;
    }
  }

  return count;
}


 
