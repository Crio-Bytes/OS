## Introduction
Round Robin is a CPU scheduling algorithm where each process is assigned a fixed time slot in a cyclic way.
  - It is simple, easy to implement, and starvation-free as all processes get fair share of CPU.
  - One of the most commonly used technique in CPU scheduling as a core.
  - It is preemptive as processes are assigned CPU only for a fixed slice of time at most.

Completion Time: Time at which process completes its execution.
Turn Around Time: Time Difference between completion time and arrival time. Turn Around Time = Completion Time – Arrival Time
Waiting Time(W.T): Time Difference between turn around time and burst time.
Waiting Time = Turn Around Time – Burst Time

## Implementation
- Create an array rem_bt[] to keep track of remaining
   burst time of processes. This array is initially a 
   copy of bt[] (burst times array)
- Create another array wt[] to store waiting times
   of processes. Initialize this array as 0.
- Initialize time : t = 0
- Keep traversing the all processes while all processes
   are not done.
   Do following for i'th process if it is
   not done yet.
    - If rem_bt[i] > quantum
       (i)  t = t + quantum
       (ii) bt_rem[i] -= quantum;
    - Else // Last cycle for this process
       (i)  t = t + bt_rem[i];
       (ii) wt[i] = t - bt[i]
       (ii) bt_rem[i] = 0; // This process is over
 - turn around time tat[i] of a process as sum of waiting and burst times, i.e., wt[i] + bt[i]
