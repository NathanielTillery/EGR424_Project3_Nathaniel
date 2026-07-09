// ===== Include appropriate header files =====

// ===== Function prototypes of functions written in OSasm.asm =====

#include "OS.h"


#define NUMTHREADS  3             // Maximum number of threads
#define STACKSIZE   100           // Number of 32-bit words in stack (You will have to keep increasing intelligently if code does not work)

// ===== Structure to store state of thread =====
struct tcb
{
  int32_t *sp;                      // Pointer to stack (valid for threads not running)
  struct tcb *next;                 // Linked-list pointer
};
typedef struct tcb tcbType;

tcbType tcbs[NUMTHREADS];			// Thread table
tcbType *RunPt;						// Pointer to pointto the next thread
int32_t Stacks[NUMTHREADS][STACKSIZE];	// 2-dimensional arry implemented as STACK


// ===== OS_Init =====
// Initialize operating system, disable interrupts until OS_Launch
// Initialize OS controlled I/O: SysTick, 3 MHz crystal
void OS_Init(void){
    OS_DisableInterrupts();
    SysTick -> CTRL = 0;    	// Disable SysTick during setup (register approach)
    SysTick -> VAL = 0; 		// Any write to current clears it (register approach)
    SCB -> SHP[1] = (SCB -> SHP[1] & 0x00FFFFFF)|0xE0000000;          // Set priority 7 so that it allows threads to run
}


// ===== Sets default values in STACK ======
// Inputs: i is the threadnumber
void SetInitialStack(int i){
  tcbs[i].sp = &Stacks[i][STACKSIZE-16]; // thread stack pointer
  Stacks[i][STACKSIZE-1] = 0x010D0D0D;   // XPSR (store appropriate initial value) 	-- Saved by Exception
  Stacks[i][STACKSIZE-3] = 0x0E0E0E0E;   // R14 (store appropriate initial value)
  Stacks[i][STACKSIZE-4] = 0x0C0C0C0C;   // R12 (store appropriate initial value)
  Stacks[i][STACKSIZE-5] = 0x03030303;   // R3 (store appropriate initial value)
  Stacks[i][STACKSIZE-6] = 0x02020202;   // R2 (store appropriate initial value)
  Stacks[i][STACKSIZE-7] = 0x01010101;   // R1 (store appropriate initial value)
  Stacks[i][STACKSIZE-8] = 0x00000000;   // R0 (store appropriate initial value)	-- Saved by Exception
  Stacks[i][STACKSIZE-9] = 0X0B0B0B0B;   // R11 (store appropriate initial value)	-- Saved by you
  Stacks[i][STACKSIZE-10] = 0x0A0A0A0A;   // R10 (store appropriate initial value)
  Stacks[i][STACKSIZE-11] = 0x09090909;   // R9 (store appropriate initial value)
  Stacks[i][STACKSIZE-12] = 0x08080808;   // R8 (store appropriate initial value)
  Stacks[i][STACKSIZE-13] = 0x07070707;   // R7 (store appropriate initial value)
  Stacks[i][STACKSIZE-14] = 0x06060606;   // R6 (store appropriate initial value)
  Stacks[i][STACKSIZE-15] = 0x05050505;   // R5 (store appropriate initial value)
  Stacks[i][STACKSIZE-16] = 0x04040404;   // R4 (store appropriate initial value)	-- Saved by you
}


// ====== OS_AddThread ======
// Add three foreground threads to the scheduler in a Round-Robin fashion
// Inputs: three pointers to a void/void foreground tasks
// Outputs: 1 if successful, 0 if this thread can not be added
int OS_AddThreads(void(*Thread0)(void), void(*Thread1)(void), void(*Thread2)(void)){
  int32_t status;

									// Function call to start the critical section
						   // next pointer of Thread 0 points to Thread 1 structure
						   // next pointer of Thread 1 points to Thread 2 structure
						   // next pointer of Thread 2 points to Thread 0 structure
									// For Thread 0: 
										// 1: Set the default values in stack
										// 2: Make ReturnAddress stored on stack to point to Thread 0
									// For Thread 1: 
										// 1: Set the default values in stack
										// 2: Make ReturnAddress stored on stack to point to Thread 1
									// For Thread 2: 
										// 1: Set the default values in stack
										// 2: Make ReturnAddress stored on stack to point to Thread 2
  
  RunPt = &tcbs[0];       // Make RunPt point to Thread 0 so it will run first
									// Function call to end the critical section

  return 1;               // successful
}


// ===== OS_Launch ======
// Start the scheduler, Enable interrupts
// Inputs: number of 333.33ms clock cycles that corresponds to 2 ms
//         (maximum of 24 bits)
void OS_Launch(uint32_t theTimeSlice){
    SysTick -> LOAD = (theTimeSlice - 1);    // Load the reload value for Systick Timer
	SysTick -> CTRL = 0x00000007;			 // Enable the Timer, Use core clock and arm interrupt
    StartOS();                     // start on the first task
}


// ====== StartCritical ======
// Make a copy of previous I bit, disable interrupts
// Outputs: previous I bit
extern int32_t StartCritical(void) __attribute__((naked));
int32_t StartCritical(void){
								// Save old status
								// Disable interrupt mechanism in assembly
								// Return to the calling function  
}


// ====== EndCritical ======
// Using the copy of previous I bit, restore I bit to previous value
// Inputs:  previous I bit
extern void EndCritical(int32_t primask) __attribute__((naked));
void EndCritical(int32_t primask){
								// Enable interrupt mechanism in assembly
								// Return to the calling function  
}


// ====== This function (written in assembly) switches to handler mode. (privileged access) =======
extern void yield(void) __attribute__((naked));
void yield(void){
						// Gain privileged access
}
