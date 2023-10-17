#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "ppm.h"

ppm* ppm_new(int32_t r, int32_t c, int32_t m) 
{
    ppm* img = (ppm *)malloc(sizeof(ppm));
    if (img != NULL) {
        strcpy(img->type, "P3");
        img->rows = r;  
        img->cols = c;
        img->max_val = m;
        img->image = (pixel *)calloc(r * c, sizeof(pixel));
        if (img->image == NULL) {
            free(img); 
            img = NULL;
        }
    }
    return img;
}


void ppm_free(ppm *image)
{
    if (image != NULL){
        if (image->image != NULL)
            free(image->image);
        free(image);
    }
}

ppm* ppm_load(char *name)
{
    FILE *f;
    char buf[8];
    int32_t r, m, c;
    ppm *img;

    if ((f = fopen(name, "r")) == NULL) {
        fprintf(stderr, "Cannot open file %s\n", name);
        return NULL;
    }

    fgets(buf, 3, f);

    if (strcmp(buf, "P3") != 0) {
        fprintf(stderr, "Wrong file format in %s\n", name);
        fclose(f);
        return NULL;
    }

    fscanf(f, "%d %d %d", &c, &r, &m);

    img = ppm_new(r, c, m);
    if (img == NULL) {
        fprintf(stderr, "Cannot allocate memory for %s\n", name);
        fclose(f);
        return NULL;
    }

    for (r = 0; r < img->rows; r++)
        for (c = 0; c < img->cols; c++) {
            int64_t addr = (int64_t) img->cols * r + c;    
            fscanf(f, "%d %d %d", &img->image[addr].r, &img->image[addr].g, &img->image[addr].b);
        }

    fclose(f);
    return img;
}

int ppm_save(ppm *image, char *name) 
{
    FILE *f;
    int32_t r, c;

    if (image == NULL) return 0;

    if ((f = fopen(name, "w")) == NULL) {
        fprintf(stderr, "Cannot open file %s\n", name);
        return 0;
    }

    fprintf(f, "%s\n", image->type);
    fprintf(f, "%d %d\n%d\n", image->cols, image->rows, image->max_val);

    for (r = 0; r < image->rows; r++)
        for (c = 0; c < image->cols; c++) {
            int64_t addr = (int64_t)image->cols * r + c;    
            fprintf(f, "%d %d %d\n", image->image[addr].r, image->image[addr].g, image->image[addr].b);
        } 

    fclose(f);
    return 1;
}
