;;===============================
;; CS 2110 Spring 2017
;; Homework 7 - Functions
;; Name: Vamshi Adimulam
;;===============================

; DO NOT REMOVE THIS LINE
;@plugin filename=lc3_udiv vector=x80

.orig x3000
    		LD R6, STACK

    		; TODO: Setup GCD call with arguments A and B

    		LD R0, A 			; Load A into R0
    		LD R1, B 			; Load B into R1
    		ADD R6, R6, -2
    		STR R1, R6, 1		; Put B onto stack
    		STR R0, R6, 0		; Push A onto stack
    		JSR GCD

    		; TODO: Store the return value in ANSWER

    		LDR R0, R6, 0		; Load return value
    		ADD R6, R6, 3		; pop off arguments and rv
    		ST R0, ANSWER

    		HALT


A       .fill 20
B       .fill 16
ANSWER  .blkw 1
STACK   .fill xF000



GCD
    ; TODO: Implement GCD here

    		ADD R6, R6, -3		; Allocate 3 spots for OFP, RA, RV
    		STR R7, R6, 1		; Store R7 address to RA
    		STR R5, R6, 0		; Store R5 address to OFR
    		ADD R5, R6, -1		; Store new frame pointer

    		LDR R0, R5, 4		; Load arg a
    		LDR R1, R5, 5		; Load arg b

    		UDIV 				; UDIV()

    		ADD R1, R1, 0		; Call R1
    		BRz BASE			; R1 (a % b) = 0
    		BRnp ELSE			; else


BASE		LDR R2, R5, 5		; Load arg b into R2
			STR R2, R5, 3		; Return b
			LDR R7, R5, 2		; Load return address

			ADD R6, R5, 3		; R6 = return value

			LDR R5, R5, 1		; Return to OFP
			RET

ELSE 		LDR R0, R5, 5		; Load arg b into R0

			ADD R6, R6, -2		
			STR R1, R6, 1		; Push R1 onto stack
			STR R0, R6, 0		; Push A onto stack

			JSR GCD

			LDR R3, R6, 0		; Load GCD(b, R1)
			STR R3, R5, 3		; Store R3 in return value
			LDR R7, R5, 2		; Load return address into R7

			ADD R6, R5, 3		; R6 holds return value

			LDR R5, R5, 1		; Return to OFP
			RET


.end

