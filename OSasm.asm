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
        .global TimerA_contextSwitchTicks

TimerA2CounterAddr  .field 0x40000810,32		; 0x40000810 is the address of the TIMER_A2 count register
TimerAResultAddr    .field TimerA_contextSwitchTicks,32


; ARM Cortex m3-v7 B4.4.1
OS_DisableInterrupts:  .asmfunc			; Complete this
	CPSID i		; Change Processor Sate Instruction Interrupt Disable i
	bx lr

       .endasmfunc


OS_EnableInterrupts:  .asmfunc			; Complete this
	CPSIE i		; Change Processor Sate Instruction Interrupt Enable i
	bx lr
		
       .endasmfunc


RunPtAddr .field RunPt,32		; Tells us that RunPt is a 32 bit value

SysTick_Handler:  .asmfunc		; 1) Handler automatically saves R0-R3,R12,LR,PC,PSR on stack upon entry
	CPSID i					    ; 2) Disable interrupt mechanism to prevent interrupts from happening during switch

	LDR  R2, TimerA2CounterAddr	; Load address of Timer_A2 count register
	LDRH R3, [R2]				; Record starting 16-bit timer count in R3

	PUSH {R4-R11}			    ; 3) Save remaining regs r4-11 on stack (of current thread)
	LDR R0, RunPtAddr		    ; 4) Load R0 with the address of RunPt, current thread
	LDR R1, [R0]			    ; 5) Load R1 with the value of RunPt
	STR SP, [R1]			    ; 6) Save current SP into TCB structure
	LDR R1, [R1, #0x4]			; 7) Load R1 with the value of RunPt->next
	STR	R1, [R0]				; 8) Store it in RunPt (so it points to next thread)
	LDR SP, [R1]				; 9) Load new thread SP; SP = RunPt->sp;
	POP {R4-R11}			    ; 10) Restore regs r4-11 (next thread)
	LDRH R0, [R2]				; END CONTEXT SWITCH MEAUREMENT; LOAD R2 INTO R0

	LDRH R0, [R2]				; Record ending 16-bit timer count in R0
	SUB  R0, R0, R3				; Calculate elapsed ticks: end - start
	UXTH R0, R0					; Keep 16-bit result and compensate for one rollover
	LDR  R1, TimerAResultAddr	; Load address of context-switch result variable
	STRH R0, [R1]				; Store elapsed context-switch ticks

	CPSIE i						; 11) Enable interrupt mechanism
	bx lr	   					; 12) Return to calling function (R0-R3,R12,LR,PC,PSR are automatically restored upon exit
    .endasmfunc


StartOS:  .asmfunc			    ; 1) Kickstarts the process with 1st thread
	LDR R0, RunPtAddr		    ; 2) Load R0 with the address of RunPt, current thread
	LDR R2, [R0]			    ; 3) Load R2 with the value of RunPt
	LDR SP, [R2]			    ; 4) Load SP with new thread SP; SP = RunPt->stackPointer;
	POP {R4-R11}			    ; 5) Restore regs r4-11
	POP {R0-R3}				    ; 6) Restore regs r0-3
	POP {R12}			  	    ; 7) Restore reg r12
	ADD SP, SP, #4		 	    ; 8) Restore LR and discard LR from initial stack
	POP {LR}			 	    ; 9) Restore return address and store it in LR (start location)
	POP {R1}				    ;10) Restore PSR into R1 and discard PSR
	CPSIE i						;11) Enable interrupt mechanism at processor level
	BX LR					    ;12) Return to calling function whcih would start the first thread
    .endasmfunc

    .end
