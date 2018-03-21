;;===============================
;; CS 2110 Spring 2017
;; Homework 7 - Functions
;; Name: Vamshi Adimulam
;;===============================

; DO NOT REMOVE THIS LINE
;@plugin filename=lc3_udiv vector=x80

.orig x3000
    		LD R6, STACK

    		; TODO: Setup Collatz call with argument N

    		ADD R6, R6, -1		; Make room for arguments
    		LD R0, N 			; Load into R0
    		LDR R0, R6, 0		; Put n into stack

    		JSR COLLATZ     	; call Collatz

    		; TODO: Store return value in ANSWER

    		LDR R0, R6, 0		; Load return value
    		ADD R6, R6, 2		; pop arguments and rv
    		ST R0, ANSWER 

    		HALT


N       .fill 8
ANSWER  .fill 0
STACK   .fill xF000


COLLATZ
    		; TODO: Implement Collatz here!

    		ADD R6, R6, -3		; Allocate 3 spots for OFP, RA, RV
    		STR R7, R6, 1		; Store R7 address to RA
    		STR R5, R6, 0		; Store R5 address to OFP
    		ADD R5, R6, -1		; Store new frame pointer
    		LDR R0, R5, 4		; R0 = n

    		AND R1, R1, 0		; Clear R1
    		ADD R1, R0, -1		; n - 1 = 0
    		BRz FIRST

    		LDR R0, R5, 4		; Load arg n
    		AND R1, R1, 0		; Clear R1
    		ADD R1, R1, 2		; R1 = 2

    		UDIV 				; UDIV()

    		ADD R1, R1, 0		; Call back R0
    		BRz IF
    		BRnp ELSE	

FIRST		AND R3, R3, 0		; 0
			STR R3, R5, 3		; Store return value into stack
			LDR R7, R5, 2		; Load R7 with Return Address
			ADD R6, R5, 3		; R6 = return value
			LDR R5, R5, 1		; Return to OFP
			RET

IF			ADD R6, R6, -1		; Allocate memory for new stack
			STR R0, R6, 0		; Load R0 into new argument of stack

			JSR COLLATZ

			LDR R3, R6, 0		; var c
			ADD R3, R3, 1		; C + 1
			STR R3, R5, 3		; Store return value into stack
			LDR R7, R5, 2		; Load R7 with return address
			ADD R6, R5, 3		; R6 = return
			LDR R5, R5, 1		; Return to OFP
			RET

ELSE		AND R2, R2, 0		; Clear R2
			LDR R1, R5, 4		; R1 = n
			ADD R2, R1, R1		; 2n
			ADD R2, R2, R1		; 3n
			ADD R2, R2, 1		; m = 3n + 1
			ADD R6, R6, -1		; Allocate memory for new stack

			STR R2, R6, 0		; Store m as new argument into stack
			JSR COLLATZ

			LDR R3, R6, 0		; var c
			ADD R3, R3, 1		; c + 1
			STR R3, R5, 3		; Store return value into stack
			LDR R7, R5, 2		; Load R7 with return address
			ADD R6, R5, 3		; R6 = return
			LDR R5, R5, 1		; Return to OFP
			RET

.end
