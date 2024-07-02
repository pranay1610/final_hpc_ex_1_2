#include <stdio.h>
#include <stdlib.h>
#include "image_utils.h"

void write_pgm_image(const char *filename, const unsigned char *matrix, int width, int height, int max_val) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Unable to open file for writing");
        return;
    }
    fprintf(fp, "P5\n%d %d\n%d\n", width, height, max_val);
    fwrite(matrix, sizeof(unsigned char), width * height, fp);
    fclose(fp);
}
