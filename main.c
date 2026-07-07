/* ****************************************************************
 * Author: Nathaniel C. Tillery
 * Class: EGR424 Project 3
 * Description: MSP432 pre-emptive multi-threaded Kernel
 * Date: 2, July 2026
 *
 * ****************************************************************/



#include "msp.h"

#include "UART.h"


/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
}
