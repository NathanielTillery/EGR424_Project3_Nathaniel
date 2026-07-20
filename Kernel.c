/* ****************************************************************
 * Author: Nathaniel C. Tillery
 * Class: EGR424 Project 3
 * Description: MSP432 pre-emptive multi-threaded Kernel
 * Date: 2, July 2026
 *
 * ****************************************************************/


// ===== Include appropriate header files =====
#include "msp.h"
#include <string.h>
#include <stdio.h>

#include "UART.h"
#include "OS.h"
#include "Threads.h"

#include "TimerA.h"



// ===== This is the kernel that will setup everything and run the scheduler ======


// number of 333.33ms clock cycles that corresponds to 2 ms
#define TIMESLICE 6000      // Thread context switch time in system time units

unsigned threadlock;                    // Variable Lock


// Code below is the interface to the C standard I/O library
// All the I/O are directed to the console which is UART0
struct __FILE { int handle; };
FILE __stdin = {0};
FILE __stdout = {1};
FILE __stderr = {2};

// ====== Called by C library console / file output =======
int fputc(int c, FILE *f){
	UART_Send(c);			// Write character to console using UART_Send()
    return c;		// Return the character sent
}

// ====== For using printf() with format specifiers ======
int fputs(const char *_ptr, register FILE *_fp){
    unsigned int len;
    len = UART_MSend((char *)_ptr);     // Send a string using UART_MSend()
    return len;                         // Return the length of the string
}


// ====== GPIO_Init() =======
void GPIO_Init(void){
    //Set up RGB LED output (P2.0, P2.1, P2.2 as output)
    P2->SEL0 = 0;
    P2->SEL1 = 0;

    P2->DIR &= ~(BIT3 | BIT4 | BIT5 | BIT6 | BIT7); //Clear all bits we're not using to input
    P2->DIR = (BIT0 | BIT1 | BIT2); //Set the RGB bits as output

    //Turn off RGB to start
    P2->OUT &= ~(BIT0 | BIT1 | BIT2);
				// Initialize GPIO periperals needed in this project
  
}


// ======== Function to initialize LOCK (you need to modify) =============
void Lock_Init(unsigned *lock){
    *lock = 1;
}

// ======= Function to acquire the lock to be written in LockAcquire.asm ======
//unsigned Lock_Acquire(unsigned *lock){
//  return 1; // always succeeds
//}

// ======== Function to release LOCK (you need to modify) ===========
//void Lock_Release(unsigned *lock){
//	;
//}


// ======= MAIN =========
int main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    Lock_Init(&threadlock);							// Initialize the global thread lock
    OS_Init();                                      // Initialize OS
    TimerA_init();                                   // Timer A will be used to measure context switch time
    UART0_Init();                                   // Initialize UART0 peripheral
    GPIO_Init();                                    // Initialize GPIO peripheral

    OS_AddThreads(&Thread0, &Thread1, &Thread2);                      // Add Threads to the list
    OS_Launch(TIMESLICE);                 // Launch OS

  return 0;            // This never executes

}




