# Review Questions

1. Give a solution in pseudo-code for the critical section problem for n-many processes (n > 2), and justify its correctness.

2. Give a detailed definition of the notion semaphore, and explain why the associated functions have to be executed atomically.

3. Give a detailed defintion of the notion pipe.

4. Define the readers/writers problem.

5. Is it true that the following code is a solution of the critical section problem for the processes P_0 and P_1, where c_0 and c_1 are initialized to FALSE? Justify your answer.

The code for process P_i (the other process is P_j):

    while TRUE
    {
      c_i = TRUE;
      if(c_j)
      {
        c_i = FALSE;
        continue;
      }
    -- CRITICAL SECTION --
    c_i = FALSE;
    -- NON-CRITICAL SECTION --
    }

