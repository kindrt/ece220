; this program uses two subroutines, SUBTR and MULT, to compute (a-b)*c
; limitation: it only works when (a-b) is positive! 

.ORIG x3000

LD R1, a  ; R1 <- some value for a
LD R2, b  ; R2 <- some value for b

ST R7, SaveR7     ; save R7 in memory
JSR SUBTR         ; call SUBTR subroutine, result is in R0

ADD R1, R0, #0    ; move result from R0 to R1
LD R2, c          ; R2 <- some value for c

JSR MULT          ; call MULT subroutine, result is in R0

; at this point, R0 contains (a-b)*c value

LD R7, SaveR7     ; restore R7 from memory
HALT

a .FILL #3
b .FILL #1
c .FILL #-2

SaveR7  .BLKW 1   ; memory for saving R7


; SUBTR subroutine computes difference of two 2s’ complement numbers
; IN: R1, R2
; OUT: R0 <- R1-R2
SUBTR   ST R2, SaveR2 ; save R2 in memory
        NOT R2, R2
        ADD R2, R2, #1 ; do not use R7 since it is needed to return
        ADD R0, R1, R2
        LD R2, SaveR2 ; restore R2 from memory
        RET
SaveR2  .BLKW 1 ; memory for saving R2


; MULT subroutine multiplies two 2s' complement numbers
; IN: R1, R2 (assume R1 > 0)
; OUT R0 <- R1 x R2
MULT    ST R1, MULTSaveR1      ; store R1
        AND R0, R0, #0         ; R0 = 0
LOOPADD ADD R0, R0, R2         ; R0 = R0 + R2
        ADD R1, R1, #-1        ; decrease counter
        BRp LOOPADD
        LD R1, MULTSaveR1      ; restore R1
        RET
MULTSaveR1   .BLKW 1

.END


