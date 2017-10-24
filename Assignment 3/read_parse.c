// Aaron Chan
// ECE399 Winter 2017
// Assignment 3
//
// These functions will be used to read
// stdin for user input and parse the
// input for command and arguments.
#include "header.h"

// Read stdin for user input
char* read_input(void)
{
    char* buff = malloc(sizeof(char)*LENGTH);
    size_t buflength = 0;
    
    printf("shell >> "); // shell prompt
    
    if(getline(&buff,&buflength,stdin)==1)
        buff = NULL;
    return buff;
}


// Take buffer and parse into command and arguments
char** parse(char* buff)
{
    char* local;
    char* token;
    char** args = malloc(100 * sizeof(char*));
    int index = 0, len;

    // In case nothing is passed in, return
    // Also clean command and params if needed
    if(buff == NULL)
    {
        printf("NULL passed in\n");
        return 0;
    }
    
    len = strlen(buff)+1;
    local = malloc(sizeof(char)*len);
    strcpy(local,buff);
    token = strtok(local," \t\n");
    while(token != NULL)
    {
        args[index] = token;
        token = strtok(NULL," \t\n");
        index++;
    }
    args[index] = '\0'; // end array with null
    return args;   
}

// Count the number of arguments in this commandline
int count_args(char** command)
{
    int count = 0;
    while(command[count] != NULL)
        count++;
    return count;

}

// Update a flag based off finding redirection, piping,
// or the & symbols in the commandline.
// This is only assuming that there will only be one
// redirection or pipe command used in the commandline
int update_flag(char** command, int param)
{
    int i = 0;
    if(param == 1) // No symbols to look for
        return 0;
//    printf("Param passed in: %d\n",param);
//    printf("Char: %s, %d\n",command[param-1],strlen(command[param-1]));
    for(i=0;i<param;i++)
    {
        if(strcmp(command[i],"&")==0)
            return 1;
        else if(strcmp(command[i],">")==0)
            return 2;
        else if(strcmp(command[i],"<")==0)
            return 3;
        else if(strcmp(command[i],"|")==0)
            return 4;
    }
    return 0;
}

// Parsing especially for daemon process
// We ignore all arguments after the '&'
char** parse_d(char** command, char* delim)
{
    char** temp;
    int count=0, i=0;
    
    while(strcmp(command[i],"&")!=0)
    {
        count++;
        i++;
    }
    temp = malloc(sizeof(char*)*(count+1));
    for(i=0;i<count;i++)
        temp[i] = command[i];
    temp[count] = '\0';
    return temp;
}
