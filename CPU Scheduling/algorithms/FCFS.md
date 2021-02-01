## Short-Introduction
Given n processes with their burst times, the task is to find average waiting time and average turn around time using FCFS scheduling algorithm.
First in, first out (FIFO), also known as first come, first served (FCFS), is the simplest scheduling algorithm. FIFO simply queues processes in the order that they arrive in the ready queue.
In this, the process that comes first will be executed first and next process starts only after the previous gets fully executed.
(Here we are considering that arrival time for all processes is 0)

## Implementation
-  Input the processes along with their burst time (bt).
-  Find waiting time (wt) for all processes.
-  As first process that comes need not to wait so 
    waiting time for process 1 will be 0 i.e. wt[0] = 0.
-  Find waiting time for all other processes i.e. for
     process i -> 
       wt[i] = bt[i-1] + wt[i-1] .
-  Find turnaround time = waiting_time + burst_time 
    for all processes.
-  Find average waiting time = 
                 total_waiting_time / no_of_processes.
-  Similarly, find average turnaround time = 
                 total_turn_around_time / no_of_processes.
