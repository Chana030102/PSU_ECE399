/* ECE399 Winter 2017
 * Assignment 1 - Header 
 * Aaron Chan
 *
 * This program will take two arguments.
 * The first argument will be a file name, 
 * and the second will be some number, n.
 * This program will read the first n lines
 * of the provided filename and display it
 * on the screen.
 *
 */
// libaries being used are in this file.
#include "apue_custom.h"

#define MAX 10 //number of char to read at a time

int main(int argc, char* argv[])
{
    int fd, lines, i, j;
    i = j = 0;
    char buff[MAX];
    
    // Checking if file name was provided or
    // if we could open the file. 
    if(argc == 1)
    {
        printf("No file name provided.\n");
        return 0;
    }
    else if((fd = open(argv[1],O_RDONLY)) == -1)
    {
        err_sys("error opening file");
        return -1;
    }
    
    // Number of lines to read from file.
    if(argc == 2)
        lines = 1; // if no number given, read one line
    else
        lines = atoi(argv[2]);
    
    // Read up to lines given or until EOF and
    // write to STDOUT.
    while(read(fd,buff,MAX) && i < lines)
    {
        for(j=0;j<MAX;++j)
        {
            if(buff[j]=='\n' && i == lines-1)
            {
                write(STDOUT_FILENO,buff,j);
                printf("\n\n");
                return 1;
            }
            else if(buff[j]=='\n')
                ++i;
        }
        write(STDOUT_FILENO,buff,MAX);

    }        
    
    // Newline after the program has finished 
    // printing out contents of file.
    printf("\n");
    return 1;
    

}
