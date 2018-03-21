;;===============================
;; Name: Vamshi Adimulam
;;===============================
;; Write a program to search for a certain value in an array.

.orig x3000
		AND R5, R5, 0		; CLEAR R5
		LD R5, ARRAY		; ARRAY	
		LD R0, LENGTH		; LENGTH
		LD R2, NUMBER		; NUMBER
		LD R4, RESULT		; RESULT
		AND R3, R3, 0		; COUNTER
		AND R7, R7, 0		; CLEAR R7
		NOT R7, R0		; 1'S COMPL OF LENGTH
		ADD R7, R7, 1		; 2'S COMPL OF LENGTH
		AND R6, R6, 0		; CLEAR R6
		ADD R6, R3, R7		; COUNT < LENGTH
		BRn WHILE1
		HALT

WHILE1		AND R7, R7, 0		; CLEAR R7
		ADD R7, R5, R3		; ARRAY ADDRESS + COUNTER
		AND R1, R1, 0		; CLEAR R1
		LDR R1, R7, 0		; ARRAY MEM ADDRESS
		AND R7, R7, 0		; CLEAR R7
		NOT R7, R2		; 1'S COMPL OF NUMBER
		ADD R7, R7, 1		; 2'S COMPL OF NUMBER
		AND R6, R6, 0		; CLEAR R6
		ADD R6, R1, R7		; ARRAY[COUNTER] == NUMBER
		BRz EXIT
		ADD R3, R3, 1
		AND R7, R7, 0		; CLEAR R7
		NOT R7, R0		; 1'S COMPL OF LENGTH
		ADD R7, R7, 1		; 2'S COMPL OF LENGTH
		AND R6, R6, 0		; CLEAR R6
		ADD R6, R3, R7		; COUNT < LENGTH
		BRn WHILE1
		AND R4, R4, 0		; CLEAR R4
		ST R4, RESULT		; RETURN 0 FOR R4
		HALT

EXIT		AND R4, R4, 0		
		ADD R4, R4, 1		; IF FOUND
		ST R4, RESULT
		HALT		
			


ARRAY	.fill x6000
LENGTH	.fill 6
NUMBER	.fill 0
RESULT	.fill 0
.end

.orig x6000
.fill 1
.fill 2
.fill 3
.fill 4
.fill 5
.fill 6
.end
