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
#include <stdint.h>
#include <stdbool.h>


#include "UART.h"
#include "Threads.h"



// ===== This is the kernel that will setup everything and run the scheduler ======


#define TIMESLICE    		            // Thread context switch time in system time units

unsigned threadlock;                    // Variable Lock
//static int pushed_back_char = -1;       // Decide if we need to push back the character in the case that scanf() destroyed

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
void Lock_Init(unsigned *lock)
{
    ;
}

// ======= Function to acquire the lock to be written in LockAcquire.asm ======
unsigned Lock_Acquire(unsigned *lock)
{
  return 1; // always succeeds
}

// ======== Function to release LOCK (you need to modify) ===========
void Lock_Release(unsigned *lock)
{
	;
}


// ======= MAIN =========
int main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    //Lock_Init();							        // Initialize the global thread lock
                                                    // Initialize OS
    UART0_Init();                                   // Initialize UART0 peripheral
    GPIO_Init();                                    // Initialize GPIO peripheral

                                                    // Add Threads to the list
                                                    // Launch OS

  return 0;            // This never executes

}







//
//
////Called by C library console / file input
////This function echoes the character received
//int fgetc(FILE *f){
//
//    int input = 0;
//
//    /* Push back scanf() read issue */
//    if(pushed_back_char != -1){
//        input = pushed_back_char;
//        pushed_back_char = -1;
//        return input;
//    }
//
//
//    //Read the character from the console then echo the input
//    input = UART_Receive();
//
//    /* Convert the 'enter' key press from the terminal into a newline
//     * for scanf(); echo the newline so that the terminal display moves
//     * to the next line
//     */
//    if (input == '\r'){
//        UART_Send('\r');
//        UART_Send('\n');
//        return '\n';
//    }
//
//    UART_Send((char)input); // Echo the character
//
//    return input;   //Return the character received
//}
//
///* ungetc() is modeled off of getc and the rest of the functions we've made in this exercise.
// * Its function is to modify a global flag variable called pushed_back_char, which tells if
// * the char has been messed up by our unique implementation of this scanf stuff.
// */
//int ungetc(int c, FILE *f)
//{
//    (void)f;
//
//    /* If end of file, nothing needed to push back */
//    if(c == EOF)
//    {
//        return EOF;
//    }
//
//    /* If we don't have exactly one character waiting to be put back into its place, we return
//     * with EOF. If there are two characters for some reason that need to be put back, this
//     * fix will break.
//     */
//    if(pushed_back_char != -1)
//    {
//        return EOF;
//    }
//
//    pushed_back_char = c;   // Save the character so fgetc() can return it on the next read
//
//    return c;              // Return to show that the pushback succeeded
//}
