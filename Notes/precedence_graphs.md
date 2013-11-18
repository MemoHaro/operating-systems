# Precedence Graphs

Precedence graphs are represented as a [directed acyclic graph](http://en.wikipedia.org/wiki/Directed_acyclic_graph)

The [verticies](http://en.wikipedia.org/wiki/Vertex_(graph_theory) are a program segment.

The [edges](http://en.wikipedia.org/wiki/Edge_(graph_theory) are a precendence relation.

Insert picture of vertex A --> vertex B

B can be executed only after A has completed.

All the verticies in a precendence graph correspond to a single program.

Example:

    A := X + Y;
    B := Z + 1;
    C := A - B;
    W := C + 1;

Put in a nice graph form..

A -> C;

B -> C;

C -> W;

## When can segments execute concurrently?

First we need to identify inputs and outputs:

1. Input(s) -- The set of all variables which were at least read as result of the exeution of a program segment

2. Output(s) -- The set of variables which were modifiesd as a result of the execution of a program segment

Example | Inputs | Outputs
:--- | :---: | ---:
X := 1 | - | X
Y := Z + A | A,Z | Y
W := Z + 1 | Z | W
Z := Z + 1 | Z | Z
X := W + Y | W, Y | X

3. Bernstein's Conditions

Two program segments P_i and P_j can execute concurrently if:

1. The outputs are different

2. No Input is an output

or more formally:

For P_i let I_i be the input variables, and O_i be the output variable. Similarly, I_j and O_j for P_j$. The segments can execute concurrently if:

1. I_j ^ O_i = {}

2. I_i ^ O_j = {}

3. O_i ^ O_j = {}

For more information see: [Parallel Computing Dependencies](http://en.wikipedia.org/wiki/Parallel_computing#Dependencies)

## Constructs

Can represent a precedence relation in a few ways:

1. Fork/Join construct

2. Concurrent statement
  * PARBEGIN/PAREND
  * Semaphores

### Fork and Join

A fork allows a single execution to split into several concurrent executions.

(FORK) -> (S_1)
(FORK) -> (S_2)

A join statement allows the merging of several concurrent executions into a single execution

(S_1) -> (JOIN)
...   -> (JOIN)
(S_N) -> (JOIN)

#### Fork

A fork results in two concurrent executions of a program.

1. One execution starts at the statement labeled after the fork. Much like a GOTO.

2. The other execution continues at the statement following the fork statement.

Example Program

        S1;
        FORK L1;
        S2;
        ...
    L1: S3;

S1 is performed, then execution is split. One process continues to execute S2 and the other jumps to L1 to execute S3.

See precedence graph:

(Insert graph here)


#### Join

A join provides the means for an execution to be temporarily delayed. Joins are called with a counter denoted as "C".

1. C is a non negative integer

2. The effects of executing the join instruction is as follows:

    C := C - 1;
    If C == 0 THEN QUIT;

The `quit` statement results in the termination of the execution.

The join instruction must be executed [atomically](http://en.wikipedia.org/wiki/Atomicity_(programming)). That is, the parallel execution of two join statements is equivalent to the serial execution of these two statements, in some arbitrary order.

(Example of precedence graph... to be inserted. Fork/join is below)

       	S1;
       	C := 3;
       	FORK L1;
       	S2;
       	S4;
       	FORK L2;
       	S5;
       	GOTO L3;
    L2: S6;
    	GOTO L3;
    L1: S3;
    L3: JOIN C;
    	S7;

ANY precedence graph can be represented with forks and joins.

### The Concurrent Statement

...
