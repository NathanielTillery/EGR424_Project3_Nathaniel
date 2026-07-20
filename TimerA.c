/* ****************************************************************
 * TimerA.c
 *
 * Original lab-exam Timer_A code author: Chirag Parikh
 * Project 3 adaptation: Nathaniel C. Tillery
 *
 * Adapted from the EGR424 lab exam Timer_A code for Project 3
 * context-switch timing. Timer_A2 runs continuously as a hardware
 * timestamp source and does not generate interrupts.
 * ****************************************************************/

#include "TimerA.h"
#include "msp.h"


/* Written by OSasm.asm after each measured context switch. */
volatile uint16_t TimerA_contextSwitchTicks = 0u;


/* Initialize Timer_A2 as a free-running 3 MHz measurement timer. */
void TimerA_init(void)
{
    TIMER_A2->EX0 = TIMER_A_EX0_IDEX__1;
    TIMER_A2->CTL = TIMER_A_CTL_SSEL__SMCLK |
                    TIMER_A_CTL_ID__1 |
                    TIMER_A_CTL_MC__CONTINUOUS |
                    TIMER_A_CTL_CLR;
}


/* Return the current 16-bit Timer_A2 timestamp. */
uint16_t TimerA_getTimestamp(void)
{
    return TIMER_A2->R;
}


/*
 * Return elapsed timer ticks. Unsigned subtraction compensates for one
 * Timer_A2 rollover when the measured interval is less than 65,536 ticks.
 */
uint16_t TimerA_getElapsedTicks(uint16_t startTime, uint16_t endTime)
{
    return (uint16_t)(endTime - startTime);
}


/* Return the most recently recorded context-switch duration. */
uint16_t TimerA_getLastContextSwitchTicks(void)
{
    return TimerA_contextSwitchTicks;
}


/* Convert 3 MHz timer ticks to nanoseconds, rounded to the nearest ns. */
uint32_t TimerA_ticksToNanoseconds(uint16_t ticks)
{
    return (((uint32_t)ticks * 1000u) + 1u) / TIMERA_TICKS_PER_MICROSECOND;
}
