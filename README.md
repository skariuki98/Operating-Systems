# Operating Systems UNIX
 Operating systems projects run on Linux servers in C

## Forking.c
Forking.c demonstrates the creation and use of child processes which access the shared memory and each increment the value stored there by 100,000 before terminating. It is important to note that the total value at the termination of all processes varies because there is no precedent set for the child processes. This means that they could run concurrently hence the varying results. This all depends on how the CPU schedules the processes to access the shared memory.

![](/images/4.jpg)

## Semaphores.c
Semaphores.c is a modified version of Forking.c with semaphores placed to control access to the shared memory. This time we use POV() wait and VOV() signal functions to wait for a resource to be released before accessing the critical section (shared memory) and signal a release of a resource after the process is done. This ensures that there is only one process accessing the shared memory at any one time. The CPU oversees the scheduling of requests and grants them until no more requests are in the queue. As a result, the shared memory stops at a constant number 11000000. 

![](/images/f2.jpg)
