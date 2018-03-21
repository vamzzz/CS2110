;;===============================
;; Name: Vamshi Adimulam
;;===============================
;; Write a program that divides two non-negative numbers A and B.

.orig x3000

		AND R0, R0, 0 		; set QUOTIENT to 0
		AND R1, R1, 0 		; Set Remainder to 0
		LD R2, A 		; initialize A
		LD R3, B 		; initialize B
		BRz isZero		; if b = 0
		AND R4, R4, 0		; clear to make room for 2's comp
		NOT R4, R3		; inverse of B
		ADD R4, R4, 1		; add 1 to make 2's complement
		AND R5, R5, 0		; setting up new reg to determine if A >= B
		ADD R5, R2, R4		; check A >= B (A - B)
		BRzp WHILE		; else
		BRn NEGATIVE		; If b > A

isZero		ADD R0, R0, -1		; setting R0 to -1
		ST R0, QUOTIENT		; making r0 into quotient
		ST R1, REMAINDER	
	
WHILE		ADD R0, R0, 1		; Quotient = quotient + 1
		AND R4, R4, 0		; clear to make room for 2's comp
		NOT R4, R3		; inverse of B
		ADD R4, R4, 1		; add 1 to make 2's complement
		ADD R2, R2, R4		; A = A - B
		AND R5, R5, 0		; setting up new reg to determine if A >= B
		ADD R5, R2, R4		; check A >= B (A - B)
		BRzp WHILE		; repeat while
		ADD R1, R1, R2		; Remainer = remainder + A
		ST R1, REMAINDER	; storing remainder
		ST R0, QUOTIENT		; storing quotient

NEGATIVE	ST R0, QUOTIENT		; storing quotient
		AND R1, R1, 0		; clearing remainder
		ADD R1, R1, R2		; adding A to remainder
		ST R1, REMAINDER	; storing remainder

	HALT

A	.fill 5
B	.fill 2
QUOTIENT	.fill 2
REMAINDER	.fill 2
.end
