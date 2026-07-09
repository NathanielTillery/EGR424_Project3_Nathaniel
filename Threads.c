// ===== Include appropriate header files =====

#include "Threads.h"

// These are the user-space threads. Note that they are completely oblivious
// to the technical concerns of the scheduler. The only interface to the
// scheduler is the single function yield() 


/* Bit banding definition */
// On-board green RGB is P2.1; 0x40004C03 in msp432p401r_classic.h
// 0x40004C03 - 0x4000000 -> 0x00004C03
// 0x00004C03 * 32 + ( 1 * 4) -> 0x00098064
// 0x42000000 + 0x00098064 -> 0x42098064
/* Bit-Banding in Lecture 7 EGR424 Lecture Slides & notes 7 part 1 and 2*/
#define LED_GREEN (*((volatile unsigned char *) 0x42098064))

// ===== Thread 0 =====
// ===== Responsible for toggling on-board GREEN RGB LED infinitely ====
// ===== Use BIT-BANDING approach to reference the LED =====
// ===== Control taken away preemptively by the KERNEL =====
void Thread0(void){
  while(1){
      LED_GREEN ^= 0x01;    //Toggle on-board LED's Green light
  }
}


// ===== Thread 1 =====
// ===== Responsible for printing message to the terminal window =====
// ===== Locks need to be implemented for this thread =====
// ===== Control needs to be given up voluntarily by this thread using yield() =====
void Thread1(void){
  
  while(1){
   if(Lock_Acquire(&threadlock)){		// Try to acquire lock and if successful

    
    printf("\n\rEntered");
    yield();					// Give up control voluntarily (context switch "interrupt")

    printf(" Thread 1 -- pass %d", count);
	Lock_Release(&threadlock);					// Release lock
   }
   yield();                		// Give up control voluntarily (context switch "interrupt")
  }
}


// ===== Thread 2 =====
// ===== Responsible for printing message to the terminal window =====
// ===== Locks need to be implemented for this thread =====
// ===== Control needs to be given up voluntarily by this thread using yield() =====
void Thread2(void){
  while(1){
   if(Lock_Acquire(&threadlock)){		// Try to acquire lock and if successful

    printf("\n\rEntered");
    yield();					// Give up control voluntarily (context switch "interrupt")

    printf(" Thread 2");
    Lock_Release(&threadlock);			// Release lock
   }
   yield();                		// Give up control voluntarily (context switch "interrupt")
  }
}

