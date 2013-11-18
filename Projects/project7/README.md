# Project 7: [The Sleeping Barber](http://en.wikipedia.org/wiki/Sleeping_barber_problem)

## Assignment 

Write a program in C to simulate the Sleeping Barder problem as outlined below, followed by an algorithm for its solution in pseudo-code. Your may use the `pipe()` function to implement the semaphores (or create your own semaphores by either using one of the Eisenberg & McGuire's, Lamport's, or Szymanski's solutions for the critical section problem.) Use pseudo-time and a random number generator to determine the arrival of the customers and how long "time" the Barber spends with each one, making sure that the Barber is "reasonably" busy. Your program should display on the screen information regarding the state of the Barber and the customers.

## Description

   The problem of the "Sleep Barber" is a classic synchronization problem between multiple system processes. Traditionally, it is based upon a hypothetical barber shop with one barber. The barber has one barber chair and a waiting room with a number of chairs in it. When the barber finishes cutting a customer's hair, he dismisses the customer and then goes to the waiting room to see if there are other customers waiting. If there are, he brings one of them back to the chair and cuts his or her hair. If there are no other customers waiting, he returns to his chair and sleeps in it. Each customer, when he arrives, looks to see what the barber is doing. If the barber is sleeping, then he wakes him up and sits in the char. If the barber is cutting hair, then he goes to the waiting room. If there is a free chair in the waiting room, he sits in it and waits his turn. If there is no free chair, then the customer leaves. 

## Issues

There are numerous issues related to the timing of theses activities. For example, a customer may arrive and observe that the barber is cutting hair, so he goes to the waiting room. While he is on his way, the barber finishes the haircut he is doing and goes to check the waiting room. Since there is no-one there, (the customer hasn't arrived yet) he goes back to his chair and sleeps. The barber is now waiting for a customer and the customer is waiting for the barber. In another example, two customers may arrive at the same time, observe that the barber is cutting hair and there is a single seat in the waiting room, and go to the waiting room. They will both then attempt to occupy the single chair.

## Solution Description

   In the following solution, the semaphore mutex ensures that only one of the participants can change state at once. The barber must acquire this mutex exclusion before checking for customers (releasing it when he either begins to sleep or begins to cut hair), and a customer must acquire it before entering the shop (releasing it when he has sat in either a waiting room chair or the barber chair). This eliminates both of the problems mentioned above. A number of semaphores are also necessary to indicate the state of the system, for example, storing the number of people in the waiting room and the number of people the barber is cutting the hair of (the multiple sleeping barbers problem is similar in the nature of implementation and pitfalls, but has the additional complexity of coordinating several barbers among the waiting customers).

## Pseudo Code

The following solution in pseudo-code guarantees synchronization between barber and customer and is deadlock free.

    Semaphore customer = 0
    Semaphore barber = 0
    Semaphore access_seats (mutex) = 1
    int number_of_free_seats = N	// N is the total number of seats

The Barber Process:


    // runs in an infinite loop
    while (true) {
        // tries to acquire a customer      
        P(customers)
        // modify the number of available seats
        P(access_seats)
        // one chair gets free
        number_of_free_seats++;
        // the barber is ready to cut
        V(barber)
        // we don't need the lock on the chairs
        V(access_seats)
        // here the barber is cutting chair
    }

The Customer Process:

    
    // runs in an infinite loop
    while (true) {
        // tries to get access to the chairs
        P(access_seats)
        // if there are any free seats
        if (number_of_free_seats > 0) {
           // sitting down on a chair
           number_of_free_seats--;
           // notifiy the barber, about a customer
           V(customers)
           // don't need to lock the chairs anymore
           V(access_seats)
           // customer wait if the barber is busy
           P(barber)
        }
        // there are no free seats
        else {
        	 // but don't forget to release the seats
        	 V(access_seats)
    	 // customer leaves without haircut
        }
    }   

