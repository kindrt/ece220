.ORIG x3000

; fill R0 with something
LD R0, VALUE ; see VALUE .FILL

; initialize registers
AND R1, R1, #0
ADD R1, R1, #15
LD R3, ZERO

; main loop
BITLOOP
ADD R2, R3, #0
ADD R0, R0, #0
BRzp ZEROBIT
ADD R2, R2, #1

; print loop
ZEROBIT
LDI R4, DSR
BRzp ZEROBIT
STI R2, DDR

; move to the next bit
ADD R0, R0, R0
ADD R1, R1, #-1
BRzp BITLOOP

HALT

VALUE .FILL #-8  ; value to be printed
ZERO  .FILL x30
DSR   .FILL xFE04
DDR   .FILL xFE06

.END
