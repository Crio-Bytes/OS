# Do you know
- FCFS can cause long waiting times, especially when the first job takes too much CPU time.

- Both SJF and Shortest Remaining time first algorithms may cause starvation. Consider a situation when the long process is there in the ready queue and shorter processes keep coming.

- If time quantum for Round Robin scheduling is very large, then it behaves same as FCFS scheduling.

- SJF is optimal in terms of average waiting time for a given set of processes,i.e., average waiting time is minimum with this scheduling, but problems are, how to know/predict the time of next job.
- SJF is a greedy algorithm
- The disadvantage of Round Robin is more overhead of context switching and large waiting time & Response time.
