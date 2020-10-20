# Introduction

Memory is hardware that your computer uses to load the operating system and run programs. It consists of one or more [RAM](https://techterms.com/definition/ram) chips that each have several memory modules. The amount of real memory in a computer is limited to the amount of RAM installed. Common memory sizes are 256 MB, 512 MB, and 1 GB.

Because your computer has a finite amount of RAM, it is possible to run out of memory when too many programs are running at one time. This is where virtual memory comes in. Virtual memory increases the available memory your computer has by enlarging the "address space", or places in memory where data can be stored. It does this by using hard disk space for additional memory allocation. However, since the hard drive is much slower than the RAM, data stored in virtual memory must be mapped back to real memory in order to be used. The Memory Management Unit handles the mapping of memory addresses between address spaces.

![memory leak](https://community-assets.home-assistant.io/original/3X/f/f/ff1c7bed6658bd5c8a1fc102ab5209e9615cf1d3.png "Source: home-assistant.io")

But, alas, we're not able to always enjoy the scalability of virtual memory due to the villainous memory leaks!

A memory leak is like a virtual oil leak in your computer. It slowly drains the available [memory](https://techterms.com/definition/memory), reducing the amount of free memory the system can use. Most memory leaks are caused by a [program](https://techterms.com/definition/program) that unintentionally uses up increasing amounts of memory while it is running. This is typically a gradual process that gets worse as the program remains open. If the leak is bad enough, it can cause the program to crash or even make the whole computer freeze.

The most common reason programs have memory leaks is due to a programming error where unused memory is not allocated back to the system. This means the amount of [RAM](https://techterms.com/definition/ram) the program uses is always growing. Therefore, the program is constantly "leaking" memory. A memory leak may also be caused by a program that requests new memory too frequently, instead of using available memory. This means each time more memory is requested, the program takes up additional RAM instead of using memory that has already been made available to the program.

Fortunately, memory leaks are not as messy as oil leaks and can be more easily fixed. Software development applications often include [debuggers](https://techterms.com/definition/debugger) that can check programs for memory leaks. Once the source of the leak is found, the programmer can modify the code so that the program uses memory more efficiently. **If you are using a program that has a memory leak, you can temporarily fix the problem by simply quitting the program and opening it again.** Once the program has been quit, the memory is automatically allocated back to the system. Of course, if the leak continues to be a problem, the best solution is to let the developer know about the issue so it can be fixed.

# Prerequisites

You will need access to a Linux system with root privileges in order to complete certain activities in this MicroByte. You will need the GNU Compiler Collection which contains the standard compiler to compile C programs, the GNU Debugger to debug the programs that you need to complete or run, and Valgrind which is a popular tool used to debug and detect memory leaks.

Install the required tools (and optionally the manual pages) by executing the following commands in a terminal:

``` bash
sudo apt update
sudo apt install -y build-essential gdb valgrind
sudo apt install manpages manpages-dev manpages-posix manpages-posix-dev
```

Make sure the tools are installed correctly by running the following commands and checking if the output is similar to the following:

> Refer `images/tools_version.jpg` in this folder.

You need to have a high-level understanding of how basic C programs are written, compiled and executed on Linux.

# Activities

## Activity 1 - Allocate Memory to a Program

A program in execution is known as a process. A process has to contain information such as the address of variables, the address space it is allowed to access and a stack to save the return addresses and local variables as the program continues its execution. Each process is also assigned a heap which is the address space that can be used to dynamically allocate memory to a process. In the logical address space, a process can be viewed as follows:

> Refer `images/activity-1/activity-1a.jpg` in this folder.

We can allocate memory (in bytes) from the process heap by calling `malloc` present in the standard C library. Read the manual page for `malloc` and determine what arguments have to be supplied and what will be the possible return value of a `malloc` call.

> Refer `images/activity-1/activity-1b.gif` in this folder.

Allocate memory sufficient to accomodate an integer, from the process heap, a finite number of times by calling `malloc` and assigning the new address to a pointer.

> Refer `src/activity-1/activity-1.c` in this folder.

### MicroChallenge

Determine the direction in which the heap grows by printing and comparing the values of the addresses returned on a successful memory allocation.

## Activity 2 - Debug Unwanted Memory Leaks

Whenever `malloc` is called, it starts looking for a free memory block that fits the size for your request. Supposing that such a block of memory is found, it is marked as reserved and a pointer to that location is returned. Scanning the memory for free blocks is an overhead and this is the reason local variables and memory that is allocated statically is stored in the stack and not in the heap.

When you allocate a chunk of memory but the process ends without deallocating that memory to eventually return it back to the operating system, you essentially create a 'hole' and the operating system has to take care of this 'hole' when it needs to allocate memory to another process.

Compile the program in Activity 1 and pass the executable to Valgrind. Observe the output that Valgrind returns.

> Refer `images/activity-2/activity-2a.gif` in this folder.

Compile the program again with the `-g` flag to include debugging symbols in the binary. Run Valgrind again, but this time with the `--leak-check=full` flag. Observe the output.

> Refer `images/activity-2/activity-2b.gif` in this folder.

Pay attention to the heap usage and the leak summary in both of the cases. Note that Valgrind points you to the line numbers in the file that may be causing the memory leak if run with the `--leak-check=full` flag.

As the process keeps on requesting memory again and again after regular intervals without returning unused memory, it results in a memory leak. Consider the situation when a program has to run continuously for extended periods of time, like a year, for instance. The operating system will eventually run out of free memory resulting in a out of memory trap that has to be handled in some way. In the next couple of activities, you will learn more about the steps the operating system can take to handle this issue.

### MicroChallenge

Confirm whether the line numbers reported by Valgrind correspond to the `malloc` calls.

## Activity 3 - Observe How Linux Handles OOM Traps

When we dynamically allocate memory, the heap expands if enough memory is available. What if the operating system runs out of free memory altogether? Note that this case is different than `malloc` not able to allocate memory of a certain size, smaller chunks can still be allocated in those cases.

Study the code and observe the output (by printing the address returned by `malloc` ) as you repeatedly allocate (or try to allocate) memory from the heap.

> Refer `src/activity-3/activity-3.c` in this folder.

Observe that the process gets 'killed' by the operating system after a while. Check the system log in `/var/log/syslog` if a diagnostic message was written to the logs. Use `grep` to find the  messages relevant to the process (You may need root privileges).

> Refer `images/activity-3/activity-3.gif` in this folder.

### MicroChallenge

Modify the program to iteratively allocate a total of 1 GB worth of memory to the same pointer. Observe whether eventually the process gets killed or `malloc` returns `NULL` by changing the size of requested allocation (in bytes) and playing around with how the iteration takes place. Read the system log to confirm the case if the process was actually killed.

## Activity 4 - Tame the Almighty OOM Killer

Had you noticed the messages in the logs when the program was killed in Activity 3? The kernel killed the process and the `oom_reaper` reclaimed the memory allocated to that process.

``` bash
kernel: Out of memory: Killed process <process-id> total-vm:2012904kB ...
kernel: oom_reaper: reaped process <process-id> ...
```

Linux gives a score to each running process ( `oom_score` ) which shows how likely it is to be terminated in case the system runs out of memory. The score is proportional to the amount of memory used by the process. The `oom_score` of a process can be found in the `/proc` file system under the folder corresponding to the process ID of the particular process.

Modify the given program to allocate 100 MB worth of memory every 2 seconds. Run the program.

> Refer `src/activity-4/activity-4.c` in this folder.

Change the `oom_score` of a process manually by writing a large positive value to the `oom_score_adj` file in `/proc/<pid>/oom_score_adj` . Note the value of `oom_score` for the process before and after writing the value to `oom_score_adj` .

> Refer `images/activity-4/activity-4.gif` in this folder.

Whenever the operating system encounters an out of memory situation, it chooses the process with the highest `oom_score` , terminates it and the `oom_reaper` reclaims the memory. You can also call the OOM killer manually by writing `f` to `/proc/sysrq-trigger` (You need to be root). Check the logs if the process was killed.

The practical solution to avoid the OOM killer from killing your proceses, is to optimize the memory management in your programs or add more physical memory to the system.

### MicroChallenge

Find out, from the Linux kernel documentation, how you can bypass the OOM killer from killing a process by setting a special `oom_score` . Hint: The kernel processes are never killed!

## Activity 5 - Reclaim Sanity with `free()`

When you no longer need a block of memory, it can be deallocated and given back to the memory manager by calling `free` on the pointer to the starting of the block of the memory to be deallocated.

Observe that the pointer for the first pointer does not get altered even after calling `malloc` in the subsequent iterations while the second pointer gets altered. Think about it.

> Refer `src/activity-5/activity-5.c` in the folder.

It is important to note that a call to `free()` does not guarantee that the memory will be returned back to the operating system. However, it does guarantee that a subsequent `malloc` will be able to claim the freed memory.

### MicroChallenge

Resolve all the possible memory leaks in the program corresponding to this activity. Use Valgrind to confirm that all blocks of memory that had been allocated dynamically have been freed.

# Summary

At the end of this MicroByte you are now better aware about the merits of good memory management and the possible consequences of memory leaks. You are also able to debug and fix easy-to-fix memory leaks in C programs.

# References

* [proc](https://man7.org/linux/man-pages/man5/proc.5.html) in the Linux Kernel Manual Pages
* [malloc](https://man7.org/linux/man-pages/man3/malloc.3.html) in the Linux Kernel Manual Pages
* [_Using Valgrind to Find Memory Leaks and Invalid Memory Use_](https://www.cprogramming.com/debugging/valgrind.html) by Alex Allain
* [_Understanding the Linux Virtual Memory Manager_](https://www.kernel.org/doc/gorman/html/understand/understand016.html) by M Gorman
* [_Introducing OOM Reaper_](https://lwn.net/Articles/666024/) in the Linux Mailing List
