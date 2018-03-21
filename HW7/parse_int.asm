;;===============================
;; CS 2110 Spring 2017
;; Homework 7 - Functions
;; Name: Vamshi Adimulam
;;===============================

.orig x3000
    LD R6, STACK

    ; You can test your functions individually here
    ; Alternatively, if you are confident in your own code,
    ; you can run the tester directly without anything here


    ; This part has been done for you
    ; When ParseInt is ready, you can uncomment the below lines

    JSR PARSE_INT   ; call PARSE_INT with no arguments
    LDR R0, R6, 0   ; load return value
    ADD R6, R6, 1   ; pop return value of stack
    ST R0, ANSWER   ; store answer

    HALT


ANSWER              .blkw 1
STACK               .fill xF000


; ======================== PARSE_INT ========================
PARSE_INT

    ; TODO: Your ParseInt code here!
    ; Remember: GETC stores in R0, so do not use it for other variables!

			ADD R6, R6, -3			; Allocate 3 spots for OFP, RA, RV
    		STR R7, R6, 1			; Store R7 address to RA
    		STR R5, R6, 0			; Store R5 address to OFP
    		ADD R5, R6, -1			; Store new frame pointer

    		AND R0, R0, 0			; Clear R0
    		AND R1, R1, 0			; Clear R1

    		ADD R6, R6, -2			; Allocate 2 spots for local variable
    		STR R0, R6, 1			; result
    		STR R1, R6, 0			; isHex

    		GETC
    		OUT

    		ADD R2, R0, -15
    		ADD R2, R2, -15
    		ADD R2, R2, -15
    		ADD R2, R2, -15
    		ADD R2, R2, -15
    		ADD R2, R2, -15
    		ADD R2, R2, -15
    		ADD R2, R2, -15

			BRz IF
			BRnp REG

IF 			LDR R1, R5, -1			; isHex
			ADD R1, R1, 1			; isHex = 1
			STR R1, R5, -1			; Store isHex back

			GETC
			OUT

			BRnzp REG

REG			LDR R1, R5, -1			; isHex
			ADD R1, R1, 0			
			BRz IF2

			LDR R2, R5, 0

			ADD R6, R6, -2			; Allocate space for 2 arguments
			STR R2, R6, 0			; First arg = result
			STR R0, R6, 1			; Second arg = R0

			LD R4, PARSE_HEX_ADDR
    		JSRR R4

    		BRnzp CONT


IF2			LDR R2, R5, 0			; result
			
			ADD R6, R6, -2			; Allocate space for 2 arguments
			STR R2, R6, 0			; First arg = result
			STR R0, R6, 1			; Second arg = R0

			LD R4, PARSE_DECIMAL_ADDR
    		JSRR R4

			BRnzp CONT

CONT 		LDR R3, R6, 0			; parsed
			AND R4, R4, 0			; Clear R4
			ADD R4, R3, 1			; parsed + 1
			BRz IF3

			STR R3, R5, 0			; result = parsed
			GETC
			OUT
			BRnzp REG

IF3			LDR R2, R5, 0			; result
			STR R2, R5, 3			; Store return value into stack
			LDR R7, R5, 2			; Load R7 with return address
			ADD R6, R5, 3			; R6 = return
			LDR R5, R5, 1			; Return to OFP
			RET


PARSE_DECIMAL_ADDR  .fill x5000     ; the address of the ParseDecimal function
PARSE_HEX_ADDR      .fill x6000     ; the address of the ParseHex function
.end


; =========================== MULT ==========================
.orig x4000
MULT

    		; TODO: Your Mult code here!

    		ADD R6, R6, -3			; Allocate 3 spots for OFP, RA, RV
    		STR R7, R6, 1			; Store R7 address to RA
    		STR R5, R6, 0			; Store R5 address to OFP
    		ADD R5, R6, -1			; Store new frame pointer

    		LDR R0, R5, 4			; a
    		LDR R1, R5, 5			; b
    		AND R2, R2, 0			; Result


    		ADD R1, R1, 0			; Bring back b
    		BRp WHILE

    		STR R2, R5, 3			; Store return value into stack
			LDR R7, R5, 2			; Load R7 with return address
			ADD R6, R5, 3			; R6 = return value
			LDR R5, R5, 1			; Return to OFP
			RET

WHILE		ADD R2, R2, R0			; Result += a
			ADD R1, R1, -1			; b--
			BRp WHILE				; While

			STR R2, R5, 3			; Store return value into stack
			LDR R7, R5, 2			; Load R7 with return address
			ADD R6, R5, 3			; R6 = return value
			LDR R5, R5, 1			; Return to OFP
			RET


.end


; ====================== PARSE_DECIMAL ======================
.orig x5000
PARSE_DECIMAL

    		; TODO: Your ParseDecimal code here!

    		ADD R6, R6, -3			; Allocate 3 spots for OFP, RA, RV
    		STR R7, R6, 1			; Store R7 address to RA
    		STR R5, R6, 0			; Store R5 address to OFP
    		ADD R5, R6, -1			; Store new frame pointer

    		LDR R0, R5, 5			; c

    		ADD R0, R0, -15
    		ADD R0, R0, -15
    		ADD R0, R0, -15
    		ADD R0, R0, -2			; C -47
    		BRnz LESS

    		LDR R0, R5, 5			; c

    		ADD R0, R0, -15
    		ADD R0, R0, -15
    		ADD R0, R0, -15
    		ADD R0, R0, -13			; c -58
    		BRp LESS

    		LDR R1, R5, 4			; acc
    		AND R2, R2, 0			; Clear R2
    		ADD R2, R2, 10			; 10

			ADD R6, R6, -2			; Allocate space for acc and c
    		STR R1, R6, 0			; put acc into stack
    		STR R2, R6, 1			; Put 16 as second argument

			LD R3, PD_MULT_ADDR
    		JSRR R3

    		LDR R4, R6, 0			; var m = Mult(acc, 10)
    		LDR R0, R5, 5			; c
    		ADD R4, R4, R0			; m + c
    		ADD R4, R4, -15
    		ADD R4, R4, -15
    		ADD R4, R4, -15
    		ADD R4, R4, -3			; m + c - '0'

    		STR R4, R5, 3		; Store return value into stack
			LDR R7, R5, 2		; Load R7 with return address
			ADD R6, R5, 3		; R6 = return
			LDR R5, R5, 1		; Return to OFP
			RET	

LESS		AND R1, R1, 0			; Clear R1
			ADD R1, R1, -1			; -1
			STR R1, R5, 3		; Store return value into stack
			LDR R7, R5, 2		; Load R7 with return address
			ADD R6, R5, 3		; R6 = return
			LDR R5, R5, 1		; Return to OFP
			RET




PD_MULT_ADDR    .fill x4000         ; the address of the Mult function
.end


; ======================== PARSE_HEX ========================
.orig x6000
PARSE_HEX

    		; TODO: Your ParseHex code here!

    		ADD R6, R6, -3			; Allocate 3 spots for OFP, RA, RV
    		STR R7, R6, 1			; Store R7 address to RA
    		STR R5, R6, 0			; Store R5 address to OFP
    		ADD R5, R6, -1			; Store new frame pointer

    		LDR R0, R5, 4			; acc

    		ADD R6, R6, -2			; Allocate space for acc and c
    		STR R0, R6, 0			; put acc into stack
    		AND R3, R3, 0			; Clear R3
    		ADD R3, R3, 15			; 15
    		ADD R3, R3, 1			; 16
    		STR R3, R6, 1			; Put 16 as second argument

    		LD R2, PH_MULT_ADDR
    		JSRR R2

    		LDR R2, R6, 0			; var m = Mult(acc, 16)
    		LDR R1, R5, 5			; c

    		ADD R1, R1, -15
    		ADD R1, R1, -15
    		ADD R1, R1, -15
    		ADD R1, R1, -3

    		BRzp POSITIVE

    		AND R3, R3, 0			; Clear R3
			ADD R3, R3, -1			; -1

			STR R3, R5, 3			; Store return value into stack
			LDR R7, R5, 2			; Load R7 with return address
			ADD R6, R5, 3			; R6 = return
			LDR R5, R5, 1			; Return to OFP
			RET

POSITIVE	AND R4, R4, 0			; Clear R4
			ADD R4, R1, -9			; c - 9 <= 0
			BRnz NEG

			LDR R1, R5, 5			; c
			ADD R1, R1, -15
			ADD R1, R1, -15
			ADD R1, R1, -15
			ADD R1, R1, -15
			ADD R1, R1, -10			; c - 70 (char from A - F)
			BRnz LETTER

			AND R3, R3, 0			; Clear R3
			ADD R3, R3, -1			; -1

			STR R3, R5, 3			; Store return value into stack
			LDR R7, R5, 2			; Load R7 with return address
			ADD R6, R5, 3			; R6 = return
			LDR R5, R5, 1			; Return to OFP
			RET

NEG			AND R4, R4, 0			; Clear R4
			LDR R1, R5, 5			; C
			ADD R4, R4, R1			; c
			ADD R4, R4, R2			; m + c

			ADD R4, R4, -15
    		ADD R4, R4, -15
    		ADD R4, R4, -15
    		ADD R4, R4, -3

			STR R4, R5, 3			; Store return value into stack
			LDR R7, R5, 2			; Load R7 with return address
			ADD R6, R5, 3			; R6 = return
			LDR R5, R5, 1			; Return to OFP
			RET

LETTER		AND R4, R4, 0			; Clear R4
			LDR R1, R5, 5			; C
			ADD R4, R4, R1			; c
			ADD R4, R4, R2			; c + m

			ADD R4, R4, -15
			ADD R4, R4, -15
			ADD R4, R4, -15
			ADD R4, R4, -15			
			ADD R4, R4, -5
			ADD R4, R4, 10			; c + m - 65 + 10

			STR R4, R5, 3			; Store return value into stack
			LDR R7, R5, 2			; Load R7 with return address
			ADD R6, R5, 3			; R6 = return
			LDR R5, R5, 1			; Return to OFP
			RET

PH_MULT_ADDR    .fill x4000         ; the address of the Mult function
.end
