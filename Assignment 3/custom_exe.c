// Aaron Chan
//  ECE399 Winter 2017
//  Assignment 3
//
//  The execute function will 
//  run commands passed in by our
//  custom shell. We also have custom history
//  functions and background process running
//  in this file.

// Issues with code:
// History also displays the immediate entered commandline input.
// !x does not repeat command, but displays <x> command in history.
// daemon_exe always reports done even if execvp might have failed

#include "header.h"

// Normal execution of commands.
int execute(char** command)
{
   pid_t pid;

   if((pid = fork()) < 0) // fork failed
   {
     fprintf(stderr,"fork failed");
     return 0;
   }
   else if(pid == 0) // child process
   {
     if(execvp(command[0],command) < 0)
     {
       fprintf(stderr,"execvp error\n");
       exit(EXIT_FAILURE);
     }
   }
   else // parent process
       wait(NULL);
   return 1;  
}

// Execute command in background (daemon).
int daemon_exe(char** command, char* commandline)
{
   pid_t pid, sid;
   char** args = parse_d(command,"&");    
  if((pid = fork()) < 0) // fork failed
  {
     fprintf(stderr,"fork failed\n");
     return 0;
  }
  else if(pid==0) // child process
  {
      // Move child process to its own session
      if((sid=setsid()) < 0)
          exit(EXIT_FAILURE);

      umask(0); // Set permissions
      chdir("/"); // Change directory to root

     // Close all streams to prevent output
     close(STDIN_FILENO);
     close(STDOUT_FILENO);
     close(STDERR_FILENO); 

     // Execute command
     if(execvp(args[0],args) < 0)
         exit(EXIT_FAILURE);
  }
  else
      wait(NULL);      
  printf("DONE: %s\n",commandline);
  return 1;
}

// Display a specific old history. History record only stores up
// to 5 entries of commands. Commands don't have to be successful
// commands. "Newline" or just pushing enter does not get stored
// in history of inputs/commands. Entry 1 is the newest, and Entry 5
// is the oldest in the history array.
void display_nhistory(char* history[], char* command, int count)
{
    int j, index, size = strlen(command);
    char number[size]; // Used so that we don't modify the original pointer

    // If only the exlamation mark was entered, output error message
    if(size == 1)
    {
        fprintf(stderr,"No integer of x inputted.\n");
        return;
    }
    
    // Write the number into local array for use
    for(j=0;j<size;++j)
        number[j] = command[j+1];
    
    index = atoi(number); // Convert char numbers into integer

    if(index < 1 || index > 5)
    {
        if(index < 1)
            fprintf(stderr,"Integer 'x' can't be zero or negative.\n");
        else
            fprintf(stderr,"Integer 'x' can't be greater than 5.\n");

        fprintf(stderr,"To view previously entered commands: \n"
                "\t!<x>\t where <x> is integer between 1 and 5.\n"
                "1 is the most recent and 5 is the oldest\n\n");
    }
    else
    {
        if(index > count)
            fprintf(stderr,"That many commands haven't been entered yet.\n");
        else
            fprintf(stdout,"(%d) %s\n",index,history[5-index]);
    }
    return;
}

// Display all command inputs as of now.
void display_all_history(char* history[], int count)
{
   if(count == 0)
   {
       fprintf(stderr,"No previous entries.\n");
       exit(0);
   }
   for(int i=1;i<=count;++i)
       printf("(%d) %s\n",i,history[count-i]);
   return;
}
