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

## Activity 3 - Observe How Linux Handles OOM Traps

When we dynamically allocate memory, the heap expands if enough memory is available. What if the operating system runs out of free memory altogether? Note that this case is different than `malloc` not able to allocate memory of a certain size, smaller chunks can still be allocated in those cases.

Study the code and observe the output (by printing the address returned by `malloc` ) as you repeatedly allocate (or try to allocate) memory from the heap.

> Refer `src/activity-3/activity-3.c` in this folder.

Observe that the process gets 'killed' by the operating system after a while. Check the system log in `/var/log/syslog` if a diagnostic message was written to the logs. Use `grep` to find the relevant messages (You may need root privileges).

> Refer `images/activity-3/activity-3.gif` in this folder.

### MicroChallenge

Modify the program to iteratively allocate a total of 1 GB worth of memory to the same pointer. Observe whether eventually the process gets killed or `malloc` returns `NULL` by changing the size of requested allocation (in bytes) and playing around with how the iteration takes place. Read the system log to confirm the case if the process was actually killed.

## Activity 4 - Tame the Almighty OOM Killer

## Activity 5 - Reclaim Sanity with `free()`

# Summary

# References

* [malloc](https://man7.org/linux/man-pages/man3/malloc.3.html) in Linux Kernel Manual Pages
* [_Understanding the Linux Virtual Memory Manager_](https://www.kernel.org/doc/gorman/html/understand/understand016.html) by M Gorman
