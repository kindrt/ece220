.ORIG x3000

; read first
POLL1 LDI  R0, KBSR
BRzp POLL1
LDI  R0, KBDR

; write to display
POLL2 LDI  R1, DSR
BRzp POLL2
STI  R0, DDR

HALT

KBSR .FILL xFE00
KBDR .FILL xFE02
DSR  .FILL xFE04
DDR  .FILL xFE06

.END