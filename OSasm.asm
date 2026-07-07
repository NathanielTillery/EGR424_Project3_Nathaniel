; ============================================================================
;   OSasm.asm: low-level OS commands, written in assembly
;   Runs on MSP432
;   A very simple real time operating system with minimal features.
; ============================================================================

        .thumb
        .text
        .align 2


        .global  RunPt            		; currently running thread
        .global  OS_DisableInterrupts
        .global  OS_EnableInterrupts
        .global  StartOS
        .global  SysTick_Handler


OS_DisableInterrupts:  .asmfunc			; Complete this
        
		
       .endasmfunc


OS_EnableInterrupts:  .asmfunc			; Complete this
        
		
       .endasmfunc


RunPtAddr .field RunPt,32

SysTick_Handler:  .asmfunc     ; 1) Handler automatically saves R0-R3,R12,LR,PC,PSR on stack upon entry
							   ; 2) Disable interrupt mechanism to prevent interrupts from happening during switch
							   ; 3) Save remaining regs r4-11 on stack (of current thread)
							   ; 4) Load R0 with the address of RunPt, current thread
							   ; 5) Load R1 with the value of RunPt
							   ; 6) Save current SP into TCB structure
							   ; 7) Load R1 with the value of RunPt->next
							   ; 8) Store it in RunPt (so it points to next thread)
							   ; 9) Load new thread SP; SP = RunPt->sp;
							   ;10) Restore regs r4-11 (next thread)
							   ;11) Enable interrupt mechanism
							   ;12) Return to calling function (R0-R3,R12,LR,PC,PSR are automatically restored upon exit
    .endasmfunc


StartOS:  .asmfunc			   ; 1) Kickstarts the process with 1st thread
							   ; 2) Load R0 with the address of RunPt, current thread
							   ; 3) Load R2 with the value of RunPt
							   ; 4) Load SP with new thread SP; SP = RunPt->stackPointer;
							   ; 5) Restore regs r4-11
							   ; 6) Restore regs r0-3
							   ; 7) Restore reg r12
							   ; 8) Restore LR and discard LR from initial stack
							   ; 9) Restore return address and store it in LR (start location)
							   ;10) Restore PSR into R1 and discard PSR
							   ;11) Enable interrupt mechanism at processor level
							   ;12) Return to calling function whcih would start the first thread
    .endasmfunc

    .end
