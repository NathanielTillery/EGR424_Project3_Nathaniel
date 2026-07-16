#ifndef THREADS_H_
#define THREADS_H_

#include "msp.h"
#include "UART.h"
//#include "Kernel.c"
//#include "Threads.h"

#include <stdio.h>
#include <string.h>



/* Function prototypes and variable declarations */
void Thread0(void);
void Thread1(void);
void Thread2(void);

// I don't know if this is correct but I moved it here so it could interact with Threads.c
unsigned Lock_Acquire(unsigned *lock);

void Lock_Release(unsigned *lock);


#endif 
