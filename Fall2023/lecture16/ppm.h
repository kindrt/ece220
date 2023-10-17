#ifndef _PPM_H_
#define _PPM_H_

#include <stdint.h>

typedef struct {
    int32_t r, g, b;  // pixel values
} pixel;

typedef struct {
    char type[3];    // PPM type
    int32_t rows, cols;  // image size
    int32_t max_val; // max color value
    pixel *image;    // pixel array
} ppm;

/* read PPM file from disk, 
   return pointer to image in memory */
ppm* ppm_load(char *name);

/* save image from memory to disk */
int ppm_save(ppm *image, char *name);

/* allocate memory for image */
ppm* ppm_new(int32_t r, int32_t c, int32_t m);

/* deallocate memory for image */
void ppm_free(ppm *image);

#endif
