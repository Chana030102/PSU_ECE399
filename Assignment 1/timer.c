/* ECE399 Winter 2017
 * Assignment 1 - Timer
 * Aaron Chan
 *
 * This program will execute a
 * separate program and print out
 * the amount of time that the 
 * executed program was active
 * for.
 */
#include "apue_custom.h"
#include <sys/time.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    char* args[argc];
    struct timeval tv;
    pid_t pid;

    // Get start time
    gettimeofday(&tv,NULL);
    time_t starts = tv.tv_sec;
    suseconds_t startus = tv.tv_usec;

    // Quit timer if no program was provided.
    // Otherwise, store given arguments for use
    if(argc == 1)
    {
        printf("No program provided.\n");
        exit(0);
    }
    else 
    {
        for(int i=1;i<argc;++i)
            args[i-1] = argv[i];
    }

    // Start fork. Child will run separate
    // program and parent will wait until
    // it finishes before calculating total
    // time run.
    if ((pid = fork()) < 0) // fork failed
    {
        err_sys("fork failed");
        exit(1);
    }
    else if (pid == 0) // run by child
    {
       if(execv(args[0], args) < 0)
           err_sys("execv error");
    }
    else
    {
        wait(NULL); // Wait for child to finish
        gettimeofday(&tv,NULL); // get final time
        time_t finishs = tv.tv_sec;
        suseconds_t finishus = tv.tv_usec;

        // Calculate total time run and print
        int seconds = finishs - starts;
        int useconds = finishus - startus;
        printf("Program ran for %d seconds"
            " and %d microseconds\n", seconds, useconds);
    }
    
    return 1;
}
