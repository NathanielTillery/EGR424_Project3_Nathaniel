#ifndef UART_H_
#define UART_H_


/* Includes */
#include "msp.h"
#include <string.h>

/* Function prototypes*/
void UART0_Init(void);
int UART_Send(char a);
char UART_Receive(void);
int UART_MSend(char*);


#endif 
