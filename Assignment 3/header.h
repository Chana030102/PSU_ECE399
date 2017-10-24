// Aaron Chan
// ECE399 Winter 2017
// Assignment 3
//
// This header file declares the libraries used
// in this assignment and the prototype 
// declarations for the shell to reference.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define LENGTH 1024 // Max length for buffer


// Prototypes
//===============================
char* read_input(void);
char** parse(char* buff);
int count_args(char** command);
int update_flag(char** command, int param);
char** parse_d(char** command, char* delim);
 

int execute(char** command);
int daemon_exe(char** command, char* commandline);
void display_nhistory(char* history[], char* command,int count);
void display_all_history(char* history[], int count);

int directA2B(char** command, int param); // A > B, right redirection
int directB2A(char** command, int param); // A < B, left redirection
int piper(char** command, int param); // A | B, piping
int find_delim(char** command, char* delim); 
//==================================


