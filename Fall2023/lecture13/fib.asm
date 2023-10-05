.ORIG x3000

; main() {
;   fib(5);
; }

LD R6, STACK_START

; push #5 onto the stack
AND R0, R0, #0 
ADD R0, R0, 5
STR R0, R6, #0 

; call subroutine
JSR FIB

; pop return value to R0
LDR R0, R6, #0
ADD R6, R6, #1

; free stack
ADD R6, R6, #1 ; pop argument

HALT


; int fib(unsigned int n) {
;   int x;
;
;   if (n < 2) return 1;
;   x = fib(n-1);
;   return x + fib(n-2);
; }

FIB
	ADD R6, R6, #-4		; callee setup
	STR R5, R6, #1
	ADD R5, R6, #0
	STR R7, R5, #2

	; Check for n == 0 and n == 1
	LDR R0, R5, #4		; Load n into R0
	BRz FIB_BASE
	ADD R0, R0, #-1
	BRz FIB_BASE

	; Compute fib(n-1). Optimization: R0 is n-1
	ADD R6, R6, #-1		; push n-1 on the stack
	STR R0, R6, #0
	JSR FIB
	LDR R0, R6, #0		; put the return value in x (R5+0)
	STR R0, R5, #0
	ADD R6, R6, #2

	; Compute fib(n-2)
	LDR R0, R5, #4		; Load n into R0
	ADD R0, R0, #-2
	ADD R6, R6, #-1		; push n-2 on the stack
	STR R0, R6, #0
	JSR FIB
	LDR R0, R6, #0		; add x to the return value and return
	LDR R1, R5, #0
	ADD R0, R0, R1		; we want to return R0
	ADD R6, R6, #2

FIB_RET	STR R0, R5, #3		; put the return value on the stack
	LDR R7, R5, #2
	LDR R5, R5, #1
	ADD R6, R6, #3
	RET

FIB_BASE
	AND R0, R0, #0
	ADD R0, R0, #1
	BRnzp FIB_RET





STACK_START .FILL x4000

.END

; x                <- R5, R6
; save R5
; save R7
; return value
; n
