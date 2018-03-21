;;===============================
;; Name: Vamshi Adimulam
;;===============================
;; Write a program to print out a pyramid to the console.

.orig x3000

		AND R1, R1, 0		; clear r1
		ADD R1, R1, 1		; CURRENT = 1
		LD R2, LEVELS		; LEVELS
		AND R7, R7, 0		; clear r7
		NOT R7, R1		; not r1
		ADD R7, R7, 1		; NEG CURRENT
		AND R4, R4, 0		; LEVELS - CURRENT
		ADD R4, R2, R7		; SPACES
		AND R3, R3, 0		; STARS
		ADD R3, R3, 1		; STARS
		AND R5, R5, 0		; COUNTER
		AND R7, R7, 0		
		NOT R7, R2		; NEG LEVELS
		ADD R7, R7, 1		; -LEVELS
		AND R6, R6, 0		
		ADD R6, R1, R7		; CURRENT <= LEVELS
		BRnz WHILEONE
		HALT

WHILEONE	AND R7, R7, 0
		NOT R7, R4
		ADD R7, R7, 1		; NEG SPACES
		AND R6, R6, 0
		ADD R6, R5, R7		; COUNTER < SPACES
		BRn WHILETWO
		AND R5, R5, 0		; COUNTER = 0
		ADD R4, R4, -1		; SPACES-1
		AND R7, R7, 0	
		NOT R7, R3
		ADD R7, R7, 1		; NEG STARS
		AND R6, R6, 0		
		ADD R6, R5, R7		; COUNT < STARS
		BRn WHILETHREE
		AND R0, R0, 0
		ADD R0, R0, 10	
		OUT			; PRINT("\N")
		AND R5, R5, 0		; COUNTER = 0
		ADD R3, R3, 2		; STARS + 2
		ADD R1, R1, 1		; CURRENT++
		AND R7, R7, 0		
		NOT R7, R2		; NEG LEVELS
		ADD R7, R7, 1		; -LEVELS
		AND R6, R6, 0		
		ADD R6, R1, R7		; CURRENT <= LEVELS
		BRnz WHILEONE
		HALT

WHILETWO	AND R0, R0, 0
		ADD R0, R0, 15
		ADD R0, R0, 15
		ADD R0, R0, 2
		OUT			; PRINT(" ")
		ADD R5, R5, 1		; COUNTER++
		AND R7, R7, 0
		NOT R7, R4
		ADD R7, R7, 1		; NEG SPACES
		AND R6, R6, 0
		ADD R6, R5, R7		; COUNTER < SPACES
		BRn WHILETWO
		AND R5, R5, 0		; COUNTER = 0
		ADD R4, R4, -1		; SPACES - 1
		AND R7, R7, 0	
		NOT R7, R3
		ADD R7, R7, 1		; NEG STARS
		AND R6, R6, 0		
		ADD R6, R5, R7		; COUNT < STARS
		BRn WHILETHREE
		AND R0, R0, 0
		ADD R0, R0, 10	
		OUT			; PRINT("\N")
		AND R5, R5, 0		; COUNTER = 0
		ADD R3, R3, 2		; STARS + 2
		ADD R1, R1, 1		; CURRENT++
		AND R7, R7, 0		
		NOT R7, R2		; NEG LEVELS
		ADD R7, R7, 1		; -LEVELS
		AND R6, R6, 0		
		ADD R6, R1, R7		; CURRENT <= LEVELS
		BRnz WHILEONE
		HALT

WHILETHREE	AND R0, R0, 0
		ADD R0, R0, 15
		ADD R0, R0, 15
		ADD R0, R0, 12
		OUT			; PRINT (*)
		ADD R5, R5, 1		; COUNTER = COUNTER + 1
		AND R7, R7, 0	
		NOT R7, R3
		ADD R7, R7, 1		; NEG STARS
		AND R6, R6, 0		
		ADD R6, R5, R7		; COUNTER < STARS
		BRn WHILETHREE
		
		AND R0, R0, 0
		ADD R0, R0, 10	
		OUT			; PRINT("\N")
		AND R5, R5, 0		; COUNTER = 0
		ADD R3, R3, 2		; STARS + 2
		ADD R1, R1, 1		; CURRENT++
		AND R7, R7, 0		
		NOT R7, R2		; NEG LEVELS
		ADD R7, R7, 1		; -LEVELS
		AND R6, R6, 0		
		ADD R6, R1, R7		; CURRENT <= LEVELS
		BRnz WHILEONE
		HALT

LEVELS	.fill 2
.end
