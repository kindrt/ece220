; run this with https://courses.grainger.illinois.edu/ece220/fa2019/lc3web_old/index.html
; based on https://wchargin.github.io/lc3web

        .ORIG x3000

        ; setup Interrupt 
        LEA R0, ISRKB
        STI R0, KBINTV ; load ISR address to INTV
        LD R3, ENIE
        STI R3, KBSR ; enable IE bit of KBSR

        ; our "compute" code
AGAIN   LD R0, DATA
        ADD R0, R0, #1 ; M[DATA] = M[DATA] + 1  
        ST R0, DATA
        BRnzp AGAIN

        HALT
DATA    .FILL x0000

        ; Interrupt Service Routine
ISRKB  ST R0, SaveR0 ; callee-save
        LDI R0, KBDR ; read a character from keyboard and clear ready bit
        ST R0, KBDATA
        LD R0,SaveR0
        RTI
SaveR0  .BLKW #1
KBDATA  .BLKW #1

ENIE   .FILL x4000 ; enable IE 0100_0000_0000_0000
KBSR    .FILL xFE00
KBDR    .FILL xFE02
KBINTV  .FILL x0180 ; INT vector table address for keyboard

        .END
