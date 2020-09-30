//
// Created by Nir on 3/19/2020.
//

#include <sys/time.h>
#include "osm.h"

#define NUM_UNROLLING 5
#define MICRO_SEC_TO_NANO 1000
#define SECONDS_TO_NANO 1000000000L

/*
 * This function creates a round up unrolling for the iterations.
 */
unsigned int round_up_unrolling(unsigned int iterations) {
    unsigned int reminder = iterations % NUM_UNROLLING;
    if (reminder == 0) return iterations;
    return iterations + NUM_UNROLLING - reminder;
}

/*
 * This function calculates time in nano seconds.
 */
double calculate_time(time_t diff_sec, double diff_suseconds) {
    return diff_sec * SECONDS_TO_NANO + diff_suseconds * MICRO_SEC_TO_NANO;
}


double osm_operation_time(unsigned int iterations) {
    if (iterations == 0) return -1;
    struct timeval start{}, end{};
    double time_taken = 0;
    int x = 0;
    if (gettimeofday(&start, nullptr) == -1) return -1;
    for (unsigned int i = 0; i < iterations; i += NUM_UNROLLING) {
        x = x + 1;
        x = x + 2;
        x = x + 3;
        x = x + 4;
        x = x + 5;
    }
    if (gettimeofday(&end, nullptr) == -1) return -1;
    time_taken = calculate_time(end.tv_sec - start.tv_sec,
                                end.tv_usec - start.tv_usec);
    iterations = round_up_unrolling(iterations);
    return time_taken / (double) iterations;
}


void empty_func() {}

double osm_function_time(unsigned int iterations) {
    if (iterations == 0) return -1;
    struct timeval start{}, end{};
    double time_taken = 0;
    if (gettimeofday(&start, nullptr) == -1) return -1;
    for (unsigned int i = 0; i < iterations; i += NUM_UNROLLING) {
        empty_func();
        empty_func();
        empty_func();
        empty_func();
        empty_func();
    }
    if (gettimeofday(&end, nullptr) == -1) return -1;
    time_taken = calculate_time(end.tv_sec - start.tv_sec,
                                end.tv_usec - start.tv_usec);
    iterations = round_up_unrolling(iterations);
    return time_taken / (double) iterations;
}

double osm_syscall_time(unsigned int iterations) {
    if (iterations == 0) return -1;
    struct timeval start{}, end{};
    double time_taken = 0;
    if (gettimeofday(&start, nullptr) == -1) return -1;
    for (unsigned int i = 0; i < iterations; i += NUM_UNROLLING) {
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
    }
    if (gettimeofday(&end, nullptr) == -1) return -1;
    time_taken = calculate_time(end.tv_sec - start.tv_sec,
                                end.tv_usec - start.tv_usec);
    iterations = round_up_unrolling(iterations);
    return time_taken / (double) iterations;
}


