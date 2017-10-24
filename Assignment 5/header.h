// Aaron Chan
// ECE399 Winter2017
// Assignment 5
//
// Header file for program mass data
// sorting program using threads.

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>

#define SIZE 64000
#define HALF SIZE/2
#define QUARTER SIZE/4

// Prototypes.
// ====================================================
struct timeval single_thread(int* to_sort);
struct timeval multi_thread(int* to_sort);

void check_sort(int* sorted); // check if sorted correctly

// Splits whole array into four parts
void split(int* to_split, int* quarterA, int* quarterB, int* quarterC, int* quarterD);

// Sorting used by multi-thread method
void *sort_quarter(void *array);
int* merge_sort_h(int *halfA, int *halfB); // merge-sort halves into whole
void *merge_sort_q(void *two_arrays); // merge-sort quarters into halves
// ====================================================
