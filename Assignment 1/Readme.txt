ECE999 Assignment 1
Aaron Chan

This text file provides a brief description
of what was done for this assignment's programs


(1) header
This program performs similarly to cat, reading
the contents of a file and writing it to STDOUT
for the user to read on the screen. It requires 
the user to include a filename and some number
of lines the want to read 'n' as arguments upon
starting the program. If no argument 'n' is 
provided, it will only read the first line of 
the text file. It will read and write 10
characters at a time. 

The current version written has problems when
requesting more lines than what is actually in
the file and writes the last read-in buffer a 
second time, replacing the head of the 10 
characters with a new line.

About 6 hours were spent to write this code
and attempting to troubleshoot it as much as
possible.


(2) timer
This program runs a separate program and reports how
long it ran for. It requires the user to pass in the
path to the program and any arguments if necessary.
First, timer will keep track of the time the program
starts by gettimeofday. Then it starts a fork and will
have the child process run the separate program using
execv. The parent will wait for the child to finish,
then call gettimeofday for a second time value. Taking
the difference of the finish and start time values,
timer reports how long the separate program ran in
seconds and microseconds.

The current version still reports some time value even 
if timer fails to call the separate program.

About 3 hours were spent to write this code and
attempting to troubleshoot.


(3) piper
This program filters user input by prompting
the user for input from the parent and passing
that through a pipe to the child to remove the
letter q and print that result. It requires a 
pipe to be setup with an integer array to 
communicate between the two processes. The parent
will write to the dedicated fd[0] and the child
will read from the dedicated fd[1] to receive what
the parent sends. 

The current version does not filter all sizes of input
and maxes out at 99 characters. It also only accepts
one line of input and does not detect Ctrl-D for 
termination.

(4)signaler
This program prints out the message "HELLO" every
two seconds for a total of ten seonds. This is 
accomplished with a for loop that prints out the message,
then uses the sytem call sleep() for two seconds. 
This program also keeps track of Ctrl-C presses. It
increments a counter every time the user attemps to 
quit the program. 

The current version's signal catching ends up speeding
the sleep process when uesr attemps to quit. When attempting
to quit, it interrupts the sleep process and the program
ends in less than 10 seconds. The count will also max out
at five attempts if the user pushes the Ctrl-C fast enough.
Program does not build Ctrl-C count during the two second sleep
and terminate when that sleep instance ends.

About 2 hours were spent workingon this code.
