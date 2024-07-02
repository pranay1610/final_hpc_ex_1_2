#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mandelbrot.h"

void compute_mandelbrot(unsigned char *matrix, int start_x, int end_x, int n_y, double x_L, double y_L, double x_R, double y_R, int I_max, int n_x) {
    double delta_x = (x_R - x_L) / n_x;
    double delta_y = (y_R - y_L) / n_y;

    #pragma omp parallel for schedule(dynamic)
    for (int i = start_x; i < end_x; i++) {
        for (int j = 0; j < n_y; j++) {
            double c_re = x_L + i * delta_x;
            double c_im = y_L + j * delta_y;
            double z_re = 0.0, z_im = 0.0;
            int iter;
            for (iter = 0; iter < I_max; iter++) {
                double z_re2 = z_re * z_re, z_im2 = z_im * z_im;
                if (z_re2 + z_im2 > 4.0) break;
                z_im = 2 * z_re * z_im + c_im;
                z_re = z_re2 - z_im2 + c_re;
            }
            matrix[(i - start_x) * n_y + j] = (unsigned char)(iter == I_max ? 0 : iter);
        }
    }
}
