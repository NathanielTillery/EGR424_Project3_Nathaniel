// ===== Include all the appropriate HEADER FILES =====




// ===== This function configures UART0 =====
void UART0_Init(void)
{

    EUSCI_A0->CTLW0 = 0x0001;       // Put in RESET mode for config
	EUSCI_A0->MCTLW &= ~0x0001;     // Disable oversampling
	EUSCI_A0->BRW = 312;			// 3 MHz / 9600 = 312 (BAUD RATE)
	EUSCI_A0->CTLW0 = 0x00C1;		// 1 stop bit, no parity, SMCLK, 8-bit data
	P1SEL0 |= 0x0C;
    P1SEL1 &= ~0x0C; 				// P1.3 and P1.2 for UART
  
	EUSCI_A0->CTLW0 &= ~0x0001;		// Take UART out of RESET mode
}


// ===== This function sends a character to UART terminal =====
int UART_Send(char a)
{
								// Wait for transmit buffer empty
								// Send a character


								// Return the character sent
}


// ===== This function transmits a string =====
int UART_MSend(char *a)
{
		  
								// Loop until all the characters sent
									// Wait for transmit buffer empty
									// Send a character
  }

								// Return number of characters sent
}


// ===== This function receives a character =====
char UART_Receive(void)
{
	
								// Wait for receive buffer full
								// Receive a character

								// Return the character received
}
