# Test Info Answers

1. (Need precedence graph)

2. The _critical section problem_ is to design a protocol such that n many processes, each with a segment of code called a _critical section_. A critical section may be changing command variables, updating a table, writing a file, and so on. The important part of the critical section is that _NO_ other process is to be allowed to execute in its critical section at the same time. A solution _MUST_ satisfy these three requirements.

  1. _Mutual Exclusion_. If a process is executing in its critical section, then no other processes can be executing in their critical sections.

  2. _Progress_. If no process is executing in its critical section and some processes wish to enter their critical sections, then only those processes that are not executing in their remainder sections can participate in the decision on which will enter its critical section next, and this selection cannot be postponed indefinitely.

  3. _Bounded Waiting_. There exists a bound, or limit, on the number of times that other processes are allowed to enter their critical sections after a process has made a request to enter its critical section and before that request is granted.

Solution for two processes:

[Peterson's Solution](http://en.wikipedia.org/wiki/Peterson's_algorithm)

Processes are numbered P_0 and P_1. When presenting a process P_i, we use P_j to denote the other process: j = 1 - i

We need two variables to share between the processes:

    int turn;
    boolean flag[2];

The variable `turn` indicates whose turn it is to enter the critical section. If `turn == i` then process P_i is allowed to execute.

`flag` is used to indicate if a process is ready to enter its critical 

if `flag[i]` is `true` then process i is ready to enter its critical section.

To enter the critical section, P_i sets `flag[i]` to `true` and then sets `turn` to the value of `j`.

If both processes try to enter at the same time, `turn` will be set to both `i` and `j` at roughly the same time. One of these assignments will last; the other will occur but will be overwritten immediately.

do {
   flag[i] = TRUE;
   turn = j;
   while (flag[j] && turn == j);

   // Critical section //


   flag[i] = FALSE;
   // Remainder section
} while (TRUE);


3. A _semaphore_ `S` is an integer value that is only accessed through commands `wait` and `signal`. Traditionally wait is defined as `P` and signal is defined as `V`. The operations are defined as follows:

    wait(S) {
      while (S <= 0)
        ; no-op
      S--;


    signal(S) {
      S++;
    }

Modifying the semaphore must be executed `atomically`, without interruption.

A `counting semaphore` can range over an unrestricted domain, while a `binary semaphore` can range only between 0 and 1. Binary semaphores are also know as `mutex locks` because they provide _mut_ual _ex_clusion.

The implementation using the entry and exit sections of the algorithmic solution of the critical section:

    do {
       wait(mutex);
       // critical section
       signal(mutex);
       // remainder section;   
    } while (TRUE);


