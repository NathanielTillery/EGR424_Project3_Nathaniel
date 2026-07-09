#ifndef OS_H_
#define OS_H_

// fill these depending on your clock
#define TIME_1MS  
#define TIME_2MS  						// This is what you should pass as the Timeslice value

#include "msp.h"

/* Function protypes */
void OS_Init(void);
void SetInitialStack(int i);
int OS_AddThreads(void(*Thread0)(void), void(*Thread1)(void), void(*Thread2)(void));
void OS_Launch(uint32_t theTimeSlice);


/* variable declarations */


#endif
