#include "timing_utils.h"

void start_timer(Timer* timer) {
    clock_gettime(CLOCK_MONOTONIC, &timer->start);
}

void stop_timer(Timer* timer) {
    clock_gettime(CLOCK_MONOTONIC, &timer->end);
}

double get_elapsed_time(Timer* timer) {
    double start = timer->start.tv_sec + timer->start.tv_nsec * 1e-9;
    double end = timer->end.tv_sec + timer->end.tv_nsec * 1e-9;
    return end - start;
}
