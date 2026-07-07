// ===== Include all the appropriate HEADER FILES =====




// ===== This function configures UART0 =====
void UART0_Init(void)
{
								// Put in RESET mode for config
								// Disable oversampling
								// 3 MHz / 9600 = 312
								// 1 stop bit, no parity, SMCLK, 8-bit data
								// P1.3 and P1.2 for UART
  
								// Take UART out of RESET mode
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
