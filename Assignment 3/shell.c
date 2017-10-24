// Aaron Chan
// ECE399 Winter 2017
// Assignment 3
//
// This the custom shell program,
// which will have similar capabilities
// of a shell except with a few
// custom commands.

#include "header.h"

// Main shell program
int main()
{
    char** command; // command and args to run
    char* buff;    // read in stdin to parse
    char* history[5];   // history of commands
    int count=0, param=0;   
    int i;  // used for loops    
    int flag, status;

    // Initialize history buffer
    for(i=0;i<5;++i)
        history[i] = NULL;

while(1)
{   
    buff = read_input(); // read input

    // If only newline was entered (no signiicant input),
    // then we won't save it or do anything and just have
    // the custom shell read from input again.
    if(buff != NULL)
    {
        // Save into history record. Shift over
        // by one if all five spots are full
        if(count == 5)
        {
            for(i=0;i<4;++i)
                history[i] = history[i+1];
            history[count-1] = buff;
        }
        else
        {
            history[count] = buff;
            ++count;
        }
        command = parse(buff); // parse input
        param = count_args(command);
        
        // Compare command to find what we want to do
        if(strcmp(command[0],"exit")==0)
        {
            // Deallocate and exit shell
            free(buff);
            free(command);
            for(i=1;i<=count;++i)
                free(history[i-1]);
            return 0;
        }
        else if(command[0][0] == '!') // display specific history
            display_nhistory(history,command[0],count);
        else if(strcmp(command[0],"history")==0)
            display_all_history(history,count); // display all history
        else
        {
            flag = update_flag(command,param);

            if(flag == 1) // &
                status = daemon_exe(command,buff);
            else if (flag == 2)  // >
                status = directA2B(command,param);
            else if(flag == 3) // <
                status = directB2A(command,param);
            else if(flag == 4) // |
                status = piper(command,param);
            else
                status = execute(command);  
        }
          
   
//        else if(strcmp(command[param-1],"&")==0) // run in background
//            status = daemon_exe(command,buff);
//        else
//            status = execute(command);
    }
}
}
