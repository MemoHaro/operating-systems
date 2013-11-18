# Review Questions

1. Represent the precedence graph pictured below with the following constructs:
  * fork/join
  * parabegin/parend
  * semaphores

2. Define the critical section problem and give in pseudo-code a solution for two processes. Justify your solution.

3. Give a detailed definition of a pipe, and use pseudo-code to show how to implement one using semaphores.

4. Define the readers/writers problem.

5. Consider the following pseudo-code, and state whether or not it is a solution of the critical section problem for the processes P_0 and P_1. Justify your answer.

Initially: c_0 = c_1 = false;

The code for process P_i (the other process is P_j)

    while true
    begin
    c_i = true;
      if c_j then
        begin
	c_i = false;
	  continue;
	  end;
    -- CRITICAL SECTION --

    c_i = false;

    -- NON-CRITICAL SECTION --

    end;
