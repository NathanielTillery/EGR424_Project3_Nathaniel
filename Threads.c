// ===== Include appropriate header files =====

// These are the user-space threads. Note that they are completely oblivious
// to the technical concerns of the scheduler. The only interface to the
// scheduler is the single function yield() 

// ===== Thread 0 =====
// ===== Responsible for toggling on-board GREEN RGB LED infinitely ====
// ===== Use BIT-BANDING approach to reference the LED =====
// ===== Control taken away pre-emtively by the KERNEL =====
void Thread0(void)
{
  while(1)
  {
	  
  }
  
}


// ===== Thread 1 =====
// ===== Responsible for printing message to the terminal window =====
// ===== Locks need to be implemented for this thread =====
// ===== Control needs to be given up voluntarily by this thread using yield() =====
void Thread1(void)
{
  
  while(1)
  {
   if(Lock_Acquire(&threadlock))		// Try to acquire lock and if successful
   {
    
    printf("\n\rEntered");
    yield();					// Give up control voluntarily (context switch "interrupt")

    printf(" Thread 1 -- pass %d", count);
	Lock_Release(&threadlock);					// Release lock
   }
   yield();                		// Give up control voluntarily (context switch "interrupt")
  }
}


// ===== Thread 2 =====
// ===== Responsible for printing message to the terminal window =====
// ===== Locks need to be implemented for this thread =====
// ===== Control needs to be given up voluntarily by this thread using yield() =====
void Thread2(void)
{
  while(1)
  {
   if(Lock_Acquire(&threadlock))		// Try to acquire lock and if successful
   {
    printf("\n\rEntered");
    yield();					// Give up control voluntarily (context switch "interrupt")

    printf(" Thread 2");
    Lock_Release(&threadlock);			// Release lock
   }
   yield();                		// Give up control voluntarily (context switch "interrupt")
  }
}

