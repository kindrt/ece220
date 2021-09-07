.ORIG x3000

; load R6 with STACK_TOP pointer
LD R6, STACK_TOP

; push two values onto the stack
AND R0, R0, #0
ADD R0, R0, #8 ; R0 <- 8

ADD R6,R6,#-1 ; push #8
STR R0,R6,#0

AND R0, R0, #0
ADD R0, R0, #9 ; R0 <- 8

ADD R6,R6,#-1 ; push #9
STR R0,R6,#0

; call the multiply subroutine
JSR STACKMULT

; result is now on top of the stack
; pop it to R1
LDR R1,R6,#0	; pop product into R1
ADD R6,R6,#1	; remove space

HALT

STACK_TOP .FILL x4000

; Inputs: R6 - Top of the Stack pointer
;         2 values on the stack
; Output: R6
;         product value on the stack
STACKMULT
    ST R7,SM_R7		; save R7
    LDR R1,R6,#0	; pop 9 into R1
    ADD R6,R6,#1	; remove space
    LDR R0,R6,#0	; pop 8 into R0
    ADD R6,R6,#1	; remove space
    JSR MULT	    ; R0 is 72
    ADD R6,R6,#-1	; push R0
    STR R0,R6,#0
    LD R7,SM_R7		; restore R7
RET
SM_R7 .BLKW #1  ; space for R7

; Inputs: R0, R1
; Output: R0 <- R0 × R1
; Caller-saved registers: R1, R2, R7
MULT
    AND R2,R2,#0
    ADD R1,R1,#0
    BRz MULTDONE
  MULTLOOP
    ADD R2,R2,R0
    ADD R1,R1,#-1
    BRnp MULTLOOP
  MULTDONE
    ADD R0,R2,#0
RET

.END