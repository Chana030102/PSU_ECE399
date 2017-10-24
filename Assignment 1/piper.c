/* ECE399 Winter 2017
 * Assignment 1 - Piper
 * Aaron Chan
 *
 * This program will read from
 * stdin and send the output to
 * a child process. The child
 * process will delete the 
 * character 'q' and write the
 * resulting string to stdout.
 */
#include "apue_custom.h"

int main(void)
{
    int fd[2];
    int size;
    int j = 0;
    pid_t pid;
    char input[100];
    char out[100]; 
 
  
    // Setup pipe. fd[0] for reading
    // and fd[1] for writing.
    if(pipe(fd) < 0)
        err_sys("pipe error");

    if((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid > 0) // parent
    {
        close(fd[0]);
        
        printf("Please enter something: ");
        fgets(input,100,stdin);
        write(fd[1],input,strlen(input));
    }
    else // child
    {
        close(fd[1]);
        read(fd[0],input, 100);

        for(int i=0;i<100;++i)
        {
            if(input[i]!='q')
            {
                out[j] = input[i];
                ++j;
            }
        }
        write(STDOUT_FILENO,out, strlen(out));

    }
    exit(0);
}
