#PSU_399 Assignment 5

Develop a multithread program to sort an array of integers.

- Program should run 4 threads and use the algorithm discussed in class
  - Break the array into four equally sized partitions
  - Sort the partitions separately in different threads
  - Merge results back together. This is a 2 step process where two threads
    merge the four partitions into two partitions and then with one thread 
    merge the two partitions into one.
  - Each of the worker threads should use a bubble sort algorithm
    (intentionally slow)
  - Use an array size of 64,000 elements that you randomaly initialize using rand()
  - Along with your code, turn in a comparison of how much time the multithread
    program takes versus running the same problem using a 1 threaded bubblesort 
    algorithm. To determine how much time is required, you might use the unix time 
    program (or "timer" from the first programming assignment)

