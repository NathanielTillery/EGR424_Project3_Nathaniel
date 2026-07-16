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


/* Functions implemented in OSasm.asm */
extern void OS_DisableInterrupts(void);
extern void StartOS(void);

/* Functions defined later in OS.c */
extern int32_t StartCritical(void) __attribute__((naked));
extern void EndCritical(int32_t primask) __attribute__((naked));

/* Private helper functions */
static void unPrivToPriv(void);
static void privToUnpriv(void);

/* Called from SVC_Handler assembly */
void handleSVC(int code);

void yield(void);

/* variable declarations */


#endif
