
.ORIG x3000

; main()
; {
;     factorial(4);
; }

; setup stack
LD R5, STACKTOP;  ; R5 - frame pointer for main()
LD R6, STACKTOP;  ; R6 - ToS pointer
ADD R6 , R6 , #1  ; stack is initially empty

; push 4 onto the stack
AND R0, R0, #0
ADD R0, R0, #4
ADD R6, R6, #-1
STR R0, R6, #0  ; push #4

; call FACTORIAL
JSR FACTORIAL

; pop return value to R0
LDR R0, R6, #0
ADD R6, R6, #1

; free stack
ADD R6, R6, #1 ; pop argument

HALT


STACKTOP .FILL x30FF


; int factorial(int n)
; {
;     int fn;
;
;     if (n > 1) 
;          fn = n * factorial(n-1);
;     else 
;          fn = 1;
;          
;     return fn;
; }
FACTORIAL
; push bk info
ADD R6, R6, #-1 ; ret val
ADD R6, R6, #-1
STR R7, R6, #0
ADD R6, R6, #-1
STR R5, R6, #0

; create space for fn
ADD R6, R6, #-1
ADD R5, R6, #0 ; update R5

; if (n > 1)
LDR R1, R5, #4
ADD R2, R1, #-1
BRnz ELSE

; fn = n * factorial(n-1);
ADD R6, R6, #-1
STR R2, R6, #0 ; push n-1

JSR FACTORIAL

; get ret val
LDR R0, R6, #0 ; R0 <- factorial(n-1)
ADD R6, R6, #1

; pop arg
ADD R6, R6, #1

LDR R1, R5, #4  ; R1 <- n

MULT R0, R0, R1 ; magic, assuming such a thing exists :)

; fn = R0
STR R0, R5, #0

BR RETURN

ELSE
; fn = 1;
AND R0, R0, #0
ADD R0, R0, #1
STR R0, R5, #0 ; fn <- 1

RETURN
; return fn;
LDR R0, R5, #0 ; R0 <- fn
STR R0, R5, #3 ; store ret val

ADD R6, R6, #1 ; pop fn

LDR R5, R6, #0
ADD R6, R6, #1 ; pop R5

LDR R7, R6, #0
ADD R6, R6, #1 ; pop R7

RET


.END



