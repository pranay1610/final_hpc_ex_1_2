#ifndef TIMING_UTILS_H
#define TIMING_UTILS_H

#include <time.h>

typedef struct {
    struct timespec start;
    struct timespec end;
} Timer;

void start_timer(Timer* timer);
void stop_timer(Timer* timer);
double get_elapsed_time(Timer* timer);

#endif // TIMING_UTILS_H
