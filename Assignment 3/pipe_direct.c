// Aaron Chan
// ECE399 Witner 2017
// Assignment 3
//
// This file will define the functions for
// redirection and piping. Any other necessary
// functions to support these shell cabailities
// will also be defined here.

// Pipe only works with two commands. Successfuly runs
// commands but exits shell.
#include "header.h"

// Right redirection ">"
int directA2B(char** command, int param)
{
    char** set1;
    char** set2;
    size_t pid;
    int i, size;
    int split = find_delim(command,">");
    if(split < 0)
    {
        fprintf(stderr,"Redirect symbol not found.\n");
        return 0;
    }
    
    size = param - split +1;
    set1 = malloc(sizeof(char*)*split);
    set2 = malloc(sizeof(char*)*size);
    
    // Split the arguments into two arrays
    // First set
    for(i = 0;i<split;i++)
        set1[i] = command[i];
    set1[split] = NULL;

    // Second set
    for(i=0;i<size;i++)
    {
        set2[i] = command[split+1+i];
        printf("Set2[%d]: %s\n",i,set2[i]);
    }

    // Fork and execute command
    if((pid=fork()) < 0)
    {
        fprintf(stderr,"fork error.\n");
        return 0;
    }
    else if(pid == 0) // child
    {
        close(STDOUT_FILENO); // close stdout
        open(set2[0],O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU); 
        if(execvp(set1[0],set1)<0)
        {
            fprintf(stderr,"execvp error\n");
            exit(EXIT_FAILURE);
        }
    }
    else // parent
        wait(NULL);
    return 1;
}

// Left redirection "<"
int directB2A(char** command, int param)
{
    char** set1;
    char** set2;
    size_t pid;
    int i, size;
    int split = find_delim(command,"<");
    if(split < 0)
    {
        fprintf(stderr,"Redirect symbol not found.\n");
        return 0;
    }
    
    size = param - split +1;
    set1 = malloc(sizeof(char*)*split);
    set2 = malloc(sizeof(char*)*size);
    
    // Split the arguments into two arrays
    // First set
    for(i = 0;i<split;i++)
        set1[i] = command[i];
    set1[split] = NULL;

    // Second set
    for(i=0;i<size;i++)
    {
        set2[i] = command[split+1+i];
        printf("Set2[%d]: %s\n",i,set2[i]);
    }

    // Fork and execute command
    if((pid=fork()) < 0)
    {
        fprintf(stderr,"fork error.\n");
        return 0;
    }
    else if(pid == 0) // child
    {
        close(STDIN_FILENO); // close stdin
        open(set2[0],O_RDONLY); // open for reading/input 
        if(execvp(set1[0],set1)<0)
        {
            fprintf(stderr,"execvp error\n");
            exit(EXIT_FAILURE);
        }
    }
    else // parent
        wait(NULL);
    return 1;
}

// Piper "|"
int piper(char** command, int param)
{
    char** set1;
    char** set2;
    int pipefd[2];
    size_t pid;
    int i, size;
    int split = find_delim(command,"|");
    if(split < 0)
    {
        fprintf(stderr,"Redirect symbol not found.\n");
        return 0;
    }
    
    size = param - split +1;
    set1 = malloc(sizeof(char*)*split);
    set2 = malloc(sizeof(char*)*size);
    
    // Split the arguments into two arrays
    // First set
    for(i = 0;i<split;i++)
        set1[i] = command[i];
    set1[split] = NULL;

    // Second set
    for(i=0;i<size;i++)
    {
        set2[i] = command[split+1+i];
        printf("Set2[%d]: %s\n",i,set2[i]);
    }
    
    pipe(pipefd); // create pipe, 0 read, 1 write

    // Fork and execute command
    if((pid=fork()) < 0)
    {
        fprintf(stderr,"fork error.\n");
        return 0;
    }
    else if(pid == 0) // child
    {
        dup2(pipefd[0],0); // replace stdin 
        close(pipefd[1]);  // close writing 
        if(execvp(set2[0],set2)<0)
        {
            fprintf(stderr,"Child execvp error\n");
            exit(EXIT_FAILURE);
        }
    }
    else // parent
    {
        dup2(pipefd[1],1); // replace stdout
        close(pipefd[0]); // close reading
        if(execvp(set1[0],set1)<0)
        {
            fprintf(stderr,"Parent execvp error\n");
            return 0;
        }
    }
    return 1;

}

// Find the location of the delimiter in commandline
int find_delim(char** command, char* delim)
{
    int i = 0, count=0;

    // Compare for delimiter
    while(command[i] != NULL && strcmp(command[i],delim)!=0)
    {
        i++;
        count++;
    }
    // If we didn't find the delimiter, return -1
    if(command[i] == NULL)
        return -1;
    else
        return count;
}

