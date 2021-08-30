.ORIG x3000 

; R2 <- some value
; R3 <- another value
;
; store R3 and R2 in the stack

; push one value onto the stack
ADD R0, R3, #0 ; prepare argument
JSR PUSH

; push another value onto the stack
ADD R0, R2, #0 ; prepare argument
JSR PUSH

; pop from the stack
JSR POP

HALT


STACK_TOP   .FILL x4000
STACK_START .FILL x4000
STACK_END   .FILL x3FF0


; IN: R0 (value)
; OUT: R5 (0  success, 1  fail)
; R3: STACK_END
; R4: STACK_TOP
;
PUSH
;
; prepare registers
;
     ST R3, PUSH_SaveR3  ; save R3
     ST R4, PUSH_SaveR4  ; save R4
     AND R5, R5, #0 ; clear R5, indicates success
     LD R3, STACK_END
     LD R4, STACK_TOP
;
; check for overflow (when stack is full)
;
     ADD R3, R3, #-1
     NOT R3, R3
     ADD R3, R3, #1
     ADD R3, R3, R4
     BRz OVERFLOW ; stack is full
;
; store value in the stack
;
     STR R0, R4, #0   ; push onto the stack
     ADD R4, R4, #-1  ; move top of the stack
     ST R4, STACK_TOP ; store top of stack pointer
     BRnzp DONE_PUSH
;
; indicate the overflow condition on return
;
OVERFLOW ADD R5, R5, #1
;
; restore modified registers and return
;
DONE_PUSH
     LD R3, PUSH_SaveR3
     LD R4, PUSH_SaveR4
     RET
;
PUSH_SaveR3 .BLKW #1
PUSH_SaveR4 .BLKW #1



; OUT: R0 (value)
; OUT: R5 (0  success, 1  fail)
; R3: STACK_START
; R4: STACK_TOP
;
POP
;
; prepare registers
;
     ST R3, POP_SaveR3  ; save R3
     ST R4, POP_SaveR4  ; save R4
     AND R5, R5, #0 ; clear R5, indicates success
     LD R3, STACK_START
     LD R4, STACK_TOP
;
; check for underflow (when stack is empty)
;
     NOT R3, R3
     ADD R3, R3, #1
     ADD R3, R3, R4
     BRz UNDERFLOW ; stack is empty, nothing to pop
;
; remove value from the stack
;
     ADD R4, R4, #1  ; move top of the stack
     LDR R0, R4, #0   ; read value from the stack
     ST R4, STACK_TOP ; store top of stack pointer
     BRnzp DONE_POP
;
; indicate the underflow condition on return
;
UNDERFLOW ADD R5, R5, #1
;
; restore modified registers and return
;
DONE_POP
     LD R3, POP_SaveR3
     LD R4, POP_SaveR4
     RET
;
POP_SaveR3 .BLKW #1
POP_SaveR4 .BLKW #1


.END

