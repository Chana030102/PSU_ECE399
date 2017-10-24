// Aaron Chan
// ECE399 Winter 2017
// Assignment 5
//
// This program will sort an array massive
// array using two methods:
// (1) Single Thread
// (2) Multiple Threads (4 threads)
//
// We will time each method to compare and see
// which method is faster at sorting mass amounts
// of data

#include "header.h"

int main()
{
    int* to_sort = malloc(sizeof(int)* SIZE);
    int* to_sort2 = malloc(sizeof(int)* SIZE);
    struct timeval st; 
    struct timeval  mt; // Time values for each thread

    // Generate seed for random generator,
    // then fill array with random numbers
    srand(time(NULL));
    for(int i = 0;i<SIZE;++i)
    {
        to_sort[i] = rand() % 20;
        to_sort2[i] = to_sort[i];
    }
/*
    // Show contents of random array
    fprintf(stdout,"\nArray to sort: ");
    for(i=0;i<SIZE;++i)
        fprintf(stdout,"%d ", to_sort[i]);
    fprintf(stdout,"\n\n");
*/
    // Sorting
    fprintf(stdout,"Sorting Arrays...\n");
    st = single_thread(to_sort); 
    mt = multi_thread(to_sort2);

    // Report how long each method took to sort data
    fprintf(stdout,"\nHere is the time it took for "
            "each method to sort:\n");
    fprintf(stdout,"(Single): %d s %d us\n",(int)st.tv_sec, (int)st.tv_usec);
    fprintf(stdout,"(MultiT): %d s %d us\n",(int)mt.tv_sec, (int)mt.tv_usec);

    return 1;
}
