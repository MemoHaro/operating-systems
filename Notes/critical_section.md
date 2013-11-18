# [Critical Section Problem](http://en.wikipedia.org/wiki/Critical_section)

Consider a set of n processes {P_0, P_1, ..., P_n}. 

> A *critical section* is a section in a process in which shared resources are accessed that may not be accessed by more than one process at a time.

> An *entry section* is a section of code implementing the request to enter the crical section (appears before the critical section)

> An *exit section* is what may follow a critical section where a process may alert that is done with its critical section.

> The *remainder section* is completed after all entry section, critical section, and exit section

The code will look like this:

    do {
       <Entry Section>
         -- CRITICAL SECTION --
       <Exit Section>
       	 <Remainder Section>
    } while (TRUE);

> The *critical section problem* is to design a protocol that the processes can use to cooperate.

The solution to the critical section problem must satisfy the following three requirements:

1. *Mutual exclusion*: If process P_i is executing in its critical section, then no other process can be executing in their critical sections.

2. *Progress*: If no process is executing in its critical section and some processes wish to enter their critical sections, then only those processes that are not executing in their remainder sections can participate in the decision on which will enter its critical section next, and this selection cannot be postposned indefinitely.

3. *Bounded waiting*: There exist a bound, or limit, on the number of times that other processes are allowed to enter their critical sections after a process has made a request to enter its critical section and before that request is granted.

## Solutions

### Peterson's Solution

### Locks

### Semaphores