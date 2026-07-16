    .text
    .align 2
    .thumb


    .global Lock_Release
    .thumbfunc Lock_Release


Lock_Release:	.asmfunc

    MOV     r1, #1
	STR		r1, [r0]		; Set *lock to 1, marking it available / unlocked

    MOV     r0, #1      ; Indicate success
    BX      LR

    .endasmfunc
