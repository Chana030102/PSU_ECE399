// Aaron Chan
// ECE399 Winter2017
// Assignment 5
//
// Sorting functions implemented with a
// single thread and multiple threads.

#include "header.h"

// Sort an array of integers within a 
// single thread
struct timeval single_thread(int* to_sort)
{
    int i, j, temp;
    struct timeval tv_start, tv_final, tv_total; 
    
    // get start time
    gettimeofday(&tv_start,NULL);

    // Bubble Sorting Algorithm
    for(i=0;i<SIZE-1;i++)
    {
       for(j=0;j<SIZE-1-i;j++)
       {
          if(to_sort[j]> to_sort[j+1])
          {
             temp = to_sort[j];
             to_sort[j] = to_sort[j+1];
             to_sort[j+1] = temp;
          }
       }
    } 
    // get finish time
    gettimeofday(&tv_final,NULL);

/*    
    // Print out contents of sorted array
    fprintf(stdout,"(Single): ");
    for(int i=0;i<SIZE;++i)
        fprintf(stdout,"%d ", to_sort[i]);
    fprintf(stdout,"\n\n");
*/

    // Calculate time it took to sort, then
    // return it back to main.
    tv_total.tv_sec = tv_final.tv_sec - tv_start.tv_sec;
    tv_total.tv_usec = tv_final.tv_usec - tv_start.tv_usec;

    check_sort(to_sort);
    return tv_total;
}

// Sort an array of integers within
// multiple threads
struct timeval multi_thread(int* to_sort)
{
    pthread_t tid[6]; // Six thread IDs to work with

    // Quarters of array
    int sectionA[QUARTER]; 
    int sectionB[QUARTER];
    int sectionC[QUARTER]; 
    int sectionD[QUARTER]; 

    int* halfA, *halfB; //Merged quarters of array
    int* whole; // Merged halves array to make whole again
    int* to_mergeA[2], *to_mergeB[2];
    void *marray1, *marray2; 
    
    struct timeval tv_start, tv_final, tv_total; 
    
    // get start time
    gettimeofday(&tv_start,NULL);
 
    split(to_sort,sectionA,sectionB,sectionC,sectionD); // split contents
    
    // Start four threads and sort quarters
    pthread_create(&tid[0],NULL,&sort_quarter,&sectionA);
    pthread_create(&tid[1],NULL,&sort_quarter,&sectionB);
    pthread_create(&tid[2],NULL,&sort_quarter,&sectionC);
    pthread_create(&tid[3],NULL,&sort_quarter,&sectionD);

    // Wait for threads to finish
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    pthread_join(tid[3],NULL);

    // Store pointers for quarter arrays
    // into another array so that we can
    // pass two arrays into one thread
    to_mergeA[0] = sectionA;
    to_mergeA[1] = sectionB;
    to_mergeB[0] = sectionC;
    to_mergeB[1] = sectionD;

    pthread_create(&tid[4],NULL,&merge_sort_q,&to_mergeA);
    pthread_create(&tid[5],NULL,&merge_sort_q,&to_mergeB);
    pthread_join(tid[4],&marray1);
    pthread_join(tid[5],&marray2);

    halfA = (int*) marray1;
    halfB = (int*) marray2;

    whole = merge_sort_h(halfA,halfB);

    // get finish time
    gettimeofday(&tv_final,NULL);

 /*   
    // Print contents of sorted array
    fprintf(stdout,"(MultiT): ");
    for(i=0;i<SIZE;i++)
        printf("%d ",whole[i]);
    printf("\n\n");
*/

    // Clean up before leaving
    free(halfA);
    free(halfB);

    // Calculate time it took to sort, then
    // return it back to main.
    tv_total.tv_sec = tv_final.tv_sec - tv_start.tv_sec;
    tv_total.tv_usec = tv_final.tv_usec - tv_start.tv_usec;
   
    check_sort(whole);
    return tv_total;
}

// Function to split array into four partitions
void split(int* to_split, int* quarterA, int* quarterB, int* quarterC, int* quarterD)
{
    int i; // for looping

    // Split contents of arrays    
    for(i=0;i<QUARTER;i++)
    {
        quarterA[i] = to_split[i];
        quarterB[i] = to_split[QUARTER+i];
        quarterC[i] = to_split[(QUARTER*2)+i];
        quarterD[i] = to_split[(QUARTER*3)+i];
    }
    return;
}

// Sorting quarter arrays with threads
void *sort_quarter(void *array)
{
    int i,j; // Looping variables
    int temp; //used for sorting
    
    // Casting of passed in array back into int
    int* sort = (int*)array;

    // Sort contents of quarter arrays
    for(i=0;i<QUARTER-1;i++)
    {
        for(j=0;j<QUARTER-1-i;j++)
        {
            if(sort[j]>sort[j+1])
            {
                temp = sort[j];
                sort[j] = sort[j+1];
                sort[j+1] = temp;
            }
        }
    }
    // re-assign passed in pointer to the
    // desired sorted array
    array = sort;    
    return NULL;
}

// Merge-sort two quarter arrays to make 
// a sorted half array
void *merge_sort_q(void *two_arrays)
{
    int** to_merge = (int**)two_arrays;
    int* quartA = to_merge[0];
    int* quartB = to_merge[1];
    int* merged = malloc(sizeof(int)* HALF);
    int indexA=0, indexB=0;

    for(int i=0; i<HALF; i++)
    {
        if(quartA[indexA] < quartB[indexB] && indexA <QUARTER && indexB < QUARTER)
        {
            merged[i] = quartA[indexA];
            indexA++;
        }
        else if(quartA[indexA] > quartB[indexB] && indexA <QUARTER && indexB < QUARTER)            
        {                
            merged[i] = quartB[indexB];
            indexB++;
        }    
        else
        {
            if(indexA < indexB)
            {
                merged[i] = quartA[indexA];
                indexA++;
            }
            else // indexB < indexA
            {
                merged[i] = quartB[indexB];
                indexB++;
            }        
        }
    }
    return (void*) merged;
}

// Merge-sort two halves and get the
// entire sorted array.
int* merge_sort_h(int *halfA, int *halfB)
{
    int* merged = malloc(sizeof(int)* SIZE);
    int indexA=0, indexB=0;

    for(int i=0; i<SIZE; i++)
    {
        if(halfA[indexA] < halfB[indexB] && indexA < HALF && indexB < HALF)
        {
            merged[i] = halfA[indexA];
            indexA++;
        }
        else if(halfA[indexA] > halfB[indexB] && indexA < HALF && indexB < HALF)            
        {                
            merged[i] = halfB[indexB];
            indexB++;
        }    
        else
        {
            if(indexA < indexB)
            {
                merged[i] = halfA[indexA];
                indexA++;
            }
            else // indexB < indexA
            {
                merged[i] = halfB[indexB];
                indexB++;
            }        
        }
    }
    return merged;
}

// Check if the array was sorted properly
// Test that it is sorted from least to greatest
void check_sort(int* sorted)
{
    int count_err = 0, i;
    for(i=0;i<SIZE-1;i++)
    {
        if(sorted[i] > sorted[i+1])
            count_err++;
    }
    if(count_err !=0)
        fprintf(stdout,"Total Sort Errors Found: %d\n",count_err);
    else
        fprintf(stdout,"Sort Complete.\n");
 
    return;
    
}

