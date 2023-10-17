#include <stdio.h>
#include "ppm.h"

int main(int argc, char **argv) 
{
    if (argc != 3) {
        printf("Usage: %s <imput image> <output image>\n", argv[0]);
        return -1;
    }

    /* load image from disk to memory */
    ppm * myimage = ppm_load(argv[1]);

    /* save image back to disk */
    ppm_save(myimage, argv[2]);

    /* free memory allocated for the image */
    ppm_free(myimage);

    return 0;
}
