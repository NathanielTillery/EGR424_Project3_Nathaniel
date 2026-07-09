    .syntax unified
    .text
    .align 2
    .thumb
    .thumb_func


 ; Returns 0 if unsuccessful, 1 if successful in acquiring lock
 ; Equivalent to:
 ;
 ; unsigned lock_acquire(unsigned *lockaddr) {
 ;     if (*lockaddr == 0) {        // LDREX instruction instead of LDR
 ;         CLREX;                  // Release exclusive lock
 ;         return 0;               // Failure: lock is already acquired
 ;     } else {
 ;         *lockaddr = 0;          // STREX instruction instead of STR
 ;         if (STREXreturn == 1) { // STREX returns 1 if unsuccessful
 ;             return 0;           // Failure: lock is under exclusive lock
 ;         } else {                // and 0 was NOT written to *lockaddr
 ;             return 1;           // STREX successful, we have the lock,
 ;         }                       // exclusive lock is released, 0 WAS
 ;     }                           // stored in *lockaddr
 ; }

    .type lock_acquire, function
    .global lock_acquire

;lock_acquire:
Lock_Acquire:
    MOV     r1, #0

    LDREX   r2, [r0]        ; R2 <-- lock value
    CMP     r2, r1          ; Is it already 0? (hence locked?)
    ITT     NE
    STREXNE r2, r1, [r0]    ; If not, try to claim it by writing 0
                            ; R2 <-- 0 if successful, 1 if failure
    CMPNE   r2, #1          ; and check success
    BEQ     1f              ; branch taken if lock was already free
                            ; (so the previous two XXXXXX instructions
                            ; did not execute) or STREXNE returned 1.

    MOV     r0, #1          ; Indicate success
    BX      LR

1:                          ; Local label. branch here from above with destination '1f'
    CLREX                   ; We did not get the lock. Clear exclusive access.
    MOV     r0, #0          ; Indicate failure
    BX      LR
