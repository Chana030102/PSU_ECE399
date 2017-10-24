/* ECE399 Winter 2017
 * Assignment 1 - Signaler
 * Aaron Chan
 *
 * This program will write "HELLO"
 * on the screen every two seconds 
 * and exits after 10 seconds. The
 * Ctrl-C command shouldn't stop
 * the program and it should print
 * out how many times the user 
 * pressed Ctrl-C.
 */
#include "apue_custom.h"

int count = 0; // to count quit attempts

// Used in signal handler to increment count
void sigint(int sig){ ++count; }

int main(void)
{
    int i = 0;
    
    signal(SIGINT,sigint);
    
    for(i=0;i<5;++i)
    {
        write(STDOUT_FILENO,"HELLO\n",6);
        sleep(2);
    }

    printf("You attempted to quit %d times."
            "\n",count);
          
    exit(0);
}
