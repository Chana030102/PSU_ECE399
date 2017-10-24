#PSU_399 Assignment 3

The following is needed for this assignment:
- description of code program design and documentation
- unique C code and a Makefile

Make a basic shell program with the provided code and then modify it to support
bash-like history capability, I/O redirection, background processes, and a 
collection of built-in commands described below.

** Details of history/built-in commands:** Have the shell assign numbers, starting at 1,
to each command executed; print the command number as part of the prompt. Also, have the
shell record the 5 most recent commands and interpret three additional commands:
- !x means repeat the (absolute) command numbered x (but only if it is one of the saved
  commands -- there may be less than 5). Print an error message if the argument x is
  invalid.
- exit means terimate the "shell"
- history means print the saved commands (again, there may be less than 5)

**I/O redirection:** Your program should support the construction of simple pipeline 
(using the | character as a constructor), redirection of the standard input (<), and
redirection of standard output (>).

**Background processes:** If a user command ends with the '&' character, the command 
should run in the background. When the program terminates, the shell should print out
the message "DONE: <commandLine>" where <commandLine> is the user command that's been
completed.
