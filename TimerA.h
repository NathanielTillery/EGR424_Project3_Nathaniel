/* ****************************************************************
 * TimerA.h
 *
 * Original lab-exam Timer_A code author: Chirag Parikh
 * Project 3 adaptation: Nathaniel C. Tillery
 *
 * Public API for the Timer_A2 context-switch measurement timer.
 * Adapted from the EGR424 lab exam Timer_A implementation.
 * ****************************************************************/

#ifndef TIMERA_H_
#define TIMERA_H_

#include <stdint.h>


/* Timer_A2 uses the default 3 MHz SMCLK with no divider. */
#define TIMERA_CLOCK_HZ                  3000000u
#define TIMERA_TICKS_PER_MICROSECOND     3u


/* Initialize Timer_A2 as a free-running timestamp source. */
void TimerA_init(void);

/* Read the current 16-bit Timer_A2 count. */
uint16_t TimerA_getTimestamp(void);

/* Calculate elapsed ticks for an interval shorter than 65,536 ticks. */
uint16_t TimerA_getElapsedTicks(uint16_t startTime, uint16_t endTime);

/* Return the most recently recorded context-switch duration. */
uint16_t TimerA_getLastContextSwitchTicks(void);

/* Convert a measured tick count to nanoseconds. */
uint32_t TimerA_ticksToNanoseconds(uint16_t ticks);


#endif /* TIMERA_H_ */
