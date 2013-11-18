# [Readers-Writers Problem](http://en.wikipedia.org/wiki/Readers%E2%80%93writers_problem)

A database is to be shared among several concurrent processes. *Reader* process want to read from the database and *writer* processes want to writer to the database. The *Readers-Writers* problem is that writers must have exclusive access to the shared database. That is, only one writer can be writing to the database at one time.

> *First Readers-Writers Problem*: No reader will be kept waiting unless a writer has already obtained permission to use the shared object. That is, no reader should wait for other readers to finish simply because a writer is waiting.

> *Second Readers-Writers Problem*: Once a writer is ready, that writer performs its write as soon as possible. In other words, if a writer is waiting to access the object, no new readers may start reading.

## First Readers Solution(s)

## Solution (Using Semaphores)

...